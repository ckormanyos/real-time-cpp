/* Linker script for NEC V850 FX2 upD70F3231 */

INPUT(libc.a libg.a libgcc.a)

OUTPUT_FORMAT("elf32-v850", "elf32-v850","elf32-v850")
OUTPUT_ARCH(v850)

EXTERN(__tp __ep __gp);

MEMORY
{
  ROM  (rx)   : org = 0x00000000, len = 128K
  RAM  (rw!x) : org = 0x03FFD900, len = 0x1000 - 0x100
  stack(rw!x) : org = 0x03FFE800, len = 0x0800 - 0x100
}

SECTIONS
{
  . = 0x00000000;

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x100);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Read-only sections, merged into text segment. */

  .rozdata ALIGN (4) :
  {
    *(.rozdata)
    *(romzdata)
    *(romzbss)
  } > ROM

  /* Read-only sections, merged into text segment. */

  .interp                : { *(.interp) }
  .hash                  : { *(.hash) }
  .dynsym                : { *(.dynsym) }
  .dynstr                : { *(.dynstr) }
  .rel.text              : { *(.rel.text) }
  .rela.text             : { *(.rela.text) }
  .rel.data              : { *(.rel.data) }
  .rela.data             : { *(.rela.data) }
  .rel.rodata            : { *(.rel.rodata) }
  .rela.rodata           : { *(.rela.rodata) }
  .rel.gcc_except_table  : { *(.rel.gcc_except_table) }
  .rela.gcc_except_table : { *(.rela.gcc_except_table) }
  .rel.got               : { *(.rel.got) }
  .rela.got              : { *(.rela.got) }
  .rel.ctors             : { *(.rel.ctors) }
  .rela.ctors            : { *(.rela.ctors) }
  .rel.dtors             : { *(.rel.dtors) }
  .rela.dtors            : { *(.rela.dtors) }
  .rel.init              : { *(.rel.init) }
  .rela.init             : { *(.rela.init) }
  .rel.fini              : { *(.rel.fini) }
  .rela.fini             : { *(.rela.fini) }
  .rel.bss               : { *(.rel.bss) }
  .rela.bss              : { *(.rela.bss) }
  .rel.plt               : { *(.rel.plt) }
  .rela.plt              : { *(.rela.plt) }
  .init                  : { KEEP (*(.init)) } =0
  .plt                   : { *(.plt) }

  .text :
  {
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    _ctors_begin = .;
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend(.ctors))
    _ctors_end = .;
  } > ROM = 0

  .jcr :
  {
    KEEP (*(.jcr))
  } > ROM
  
  .gcc_except_table : { *(.gcc_except_table) } > ROM
  .got              : { *(.got.plt) *(.got) } > ROM
  .dynamic          : { *(.dynamic) } > ROM

  PROVIDE(__tp = .);

  . = 0x03FFD900;
  . = ALIGN(4);

  .data :
  {
    PROVIDE(__data_ram_start = .);
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d*)
    CONSTRUCTORS
  } > RAM AT > ROM

  PROVIDE (__ep = .);

  PROVIDE (__gp = . + 0x00008000);

  .sdata ALIGN (4) :
  {
    *(.sdata)
  } > RAM AT > ROM

  .rosdata :
  {
    *(.rosdata)
  } > RAM AT > ROM
 
  _data_begin = LOADADDR(.data);
  _data_end   = LOADADDR(.rosdata) + SIZEOF(.rosdata);

  .bss ALIGN (4) :
  {
    _bss_begin = . ;
    *(.sbss)
    *(.sbss*)
    *(.scommon)
    *(.dynbss)
    *(.bss)
    *(.bss*)
    *(COMMON)
  } > RAM

  _bss_end = . ;
  _end = . ;

  PROVIDE (end = .);

  .stack :
  {
    *(.stack)
  } > stack

  _rom_data_begin = LOADADDR(.data);
}
