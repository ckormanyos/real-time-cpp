/* Linker script for NEC V850 FX2 upD70F3231 */

INPUT(libc.a libg.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-v850", "elf32-v850","elf32-v850")
OUTPUT_ARCH(v850)

EXTERN(__tp __ctbp __ep __gp);

MEMORY
{
  ROM  (rx)   : org = 0x00000000, len = 128K
  RAM  (rw!x) : org = 0x03FFD800, len = 0x1000
  stack(rw!x) : org = 0x03FFE800, len = 0x0800
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

  PROVIDE(__tp = .);

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

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    . = ALIGN(4);
    _ctors_begin = .;
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend(.ctors))
    _ctors_end = .;
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
  } > ROM = 0

  .call_table_data ALIGN (4) :
  {
    PROVIDE(__ctbp = .);
    *(.call_table_data)
  } > ROM = 0xFF

  .call_table_text :
  {
    *(.call_table_text)
  } > ROM

  PROVIDE(__tp = .);

  .rodata  : { *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*) } > ROM
  .rodata1 : { *(.rodata1) } > ROM

  .jcr :
  {
    KEEP (*(.jcr))
  } > ROM

  .gcc_except_table : { *(.gcc_except_table) } > ROM
  .got              : { *(.got.plt) *(.got) } > ROM
  .dynamic          : { *(.dynamic) } > ROM

  . = 0x03FFD800;
  . = ALIGN(4);

  __ep = . ;
  __gp = . ;

  /* The ROM-to-RAM initialized data section */
  .data ALIGN (4) :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    *(.sdata*)
    . = ALIGN(4);
    KEEP (*(.sdata*))
    *(.rosdata*)
    . = ALIGN(4);
    KEEP (*(.rosdata*))
    _data_end = .;
  } > RAM AT > ROM

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
    _bss_end = . ;
  } > RAM

  _end = . ;

  PROVIDE (end = .);

  . = 0x03FFE800;
  . = ALIGN(4);

  .stack :
  {
    *(.stack)
  } > stack

  _rom_data_begin = LOADADDR(.data);
}
