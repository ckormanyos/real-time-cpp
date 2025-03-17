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
# 
#####################################################################################
import argparse

def binary_to_assembly(input_file, output_file, section_name, symbol_name, bytes_per_line):
    with open(input_file, "rb") as f:
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

    with open(output_file, "w") as f:
        f.write("\n".join(asm_lines) + "\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert a binary file to assembly .byte directives.")
    parser.add_argument("-i", "--input", required=True, help="Input binary file")
    parser.add_argument("-o", "--output", required=True, help="Output assembly file")
    parser.add_argument("-s", "--section", required=True, help="Target section name")
    parser.add_argument("-g", "--symbol", required=True, help="Global symbol name")
    parser.add_argument("-l", "--length", type=int, required=True, help="Number of bytes per .byte line")

    args = parser.parse_args()
    binary_to_assembly(args.input, args.output, args.section, args.symbol, args.length)
