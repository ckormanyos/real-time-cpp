#####################################################################################
# 
# Filename    : bin2asm.py
# 
# Author      : Chalandi Amine
#
# Owner       : Chalandi Amine
# 
# Date        : 27.02.2025
# 
# Description : convert a binary image to assembly file
#               2026-01-15: Added path validation to ensure input/output
#               files are within allowed base directory
# 
#####################################################################################
import argparse
import sys
import re
from pathlib import Path

def is_within_directory(path: Path, base: Path) -> bool:
    try:
        path_resolved = path.resolve(strict=False)
        base_resolved = base.resolve(strict=False)
        return base_resolved == path_resolved or base_resolved in path_resolved.parents
    except Exception:
        return False

def validate_path(path_str: str, base: Path, must_exist: bool = False, allow_create_parent: bool = False) -> Path:
    path = Path(path_str)
    # If user provided a relative path, make it relative to cwd then resolve
    try:
        resolved = path.resolve(strict=must_exist)
    except Exception:
        # If must_exist is False, resolve with strict=False to avoid exceptions for non-existent files
        resolved = path.resolve(strict=False)
    if not is_within_directory(resolved, base):
        raise ValueError(f"Path '{path_str}' is outside allowed base directory '{base}'")
    if must_exist and not resolved.exists():
        raise ValueError(f"Required path does not exist: '{resolved}'")
    if allow_create_parent:
        parent = resolved.parent
        if not is_within_directory(parent, base):
            raise ValueError(f"Parent directory '{parent}' is outside allowed base '{base}'")
    return resolved

def validate_names(section_name: str, symbol_name: str):
    if not re.match(r'^[A-Za-z0-9_.-]+$', section_name):
        raise ValueError(f"Invalid section name: '{section_name}'")
    if not re.match(r'^[A-Za-z_]\w*$', symbol_name):
        raise ValueError(f"Invalid symbol name: '{symbol_name}'")

def binary_to_assembly(input_file: Path, output_file: Path, section_name: str, symbol_name: str, bytes_per_line: int):
    with input_file.open("rb") as f:
        data = f.read()

    asm_lines = [
        f'.section {section_name}, "a"',
        f".global {symbol_name}",
        f"{symbol_name}:"
    ]

    for i in range(0, len(data), bytes_per_line):
        chunk = data[i:i+bytes_per_line]
        byte_list = ", ".join(f"0x{b:02X}" for b in chunk)
        asm_lines.append(f"    .byte {byte_list}")

    # Safe creation and write (parent path was validated before calling)
    output_file.parent.mkdir(parents=True, exist_ok=True)
    with output_file.open("w", newline="\n") as f:
        f.write("\n".join(asm_lines) + "\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert a binary file to assembly .byte directives.")
    parser.add_argument("-i", "--input", required=True, help="Input binary file")
    parser.add_argument("-o", "--output", required=True, help="Output assembly file")
    parser.add_argument("-s", "--section", required=True, help="Target section name")
    parser.add_argument("-g", "--symbol", required=True, help="Global symbol name")
    parser.add_argument("-l", "--length", type=int, required=True, help="Number of bytes per .byte line")
    parser.add_argument("--root", required=False, default=".", help="Allowed base root directory (default: current working directory)")

    args = parser.parse_args()

    if args.length <= 0 or args.length > 4096:
        print("Error: --length must be between 1 and 4096", file=sys.stderr)
        sys.exit(2)

    base_dir = Path(args.root).resolve()
    try:
        input_path = validate_path(args.input, base_dir, must_exist=True)
        output_path = validate_path(args.output, base_dir, must_exist=False, allow_create_parent=True)
        validate_names(args.section, args.symbol)
    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(2)

    binary_to_assembly(input_path, output_path, args.section, args.symbol, args.length)
