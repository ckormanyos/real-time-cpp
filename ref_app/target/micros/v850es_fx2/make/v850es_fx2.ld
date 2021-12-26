/* Linker script for NEC V850 FX2 upD70F3231 */

INPUT(libc.a libg.a libgcc.a)

OUTPUT_FORMAT("elf32-v850", "elf32-v850","elf32-v850")
OUTPUT_ARCH(v850)

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 2K */
_stack_begin = 0x03FFE800;
_stack_end   = 0x03FFF000;

__initial_stack_pointer = 0x03FFF000 - 4;

EXTERN(__tp __ep __gp);

MEMORY
{
  ROM  (rx)   : org = 0x00000000, len = 128K
  RAM  (rw!x) : org = 0x03FFD800, len = 0x1000
  STACK(rw!x) : org = 0x03FFE800, len = 0x0800
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

  /* This is the read only part of the zero data area.
     Having it as a seperate section prevents its
     attributes from being inherited by the zdata
     section.  Specifically it prevents the zdata
     section from being marked READONLY.  */

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
    *(.text)
    *(.text.*)
    _ctors_begin = .;
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend(.ctors))
    _ctors_end = .;
  } > ROM = 0

  _etext = .;

  PROVIDE (etext = .);

  /* This is special code area at the end of the normal text section.
     It contains a small lookup table at the start followed by the
     code pointed to by entries in the lookup table.  */

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

  .data :
  {
    PROVIDE(__data_ram_start = .);
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d*)
    CONSTRUCTORS
  } > RAM AT > ROM

  .data1 : { *(.data1) } > RAM AT > ROM

  .zdata ALIGN (4) :
  {
    *(.zdata)
    *(.zbss)
    *(reszdata)
    *(.zcommon)
  } > RAM AT > ROM

  .tdata ALIGN (4) :
  {
    PROVIDE (__ep = .);
    *(.tbyte)
    *(.tcommon_byte)
    *(.tdata)
    *(.tbss)
    *(.tcommon)
  } > RAM AT > ROM

  /* We want the small data sections together, so single-instruction offsets
     can access them all, and initialized data all before uninitialized, so
     we can shorten the on-disk segment size.  */

  .sdata ALIGN (4) :
  {
    PROVIDE (__gp = . + 0x00008000);
    *(.sdata)
  } > RAM AT > ROM

  /* See comment about .rozdata. */

  .rosdata :
  {
    *(.rosdata)
  } > RAM AT > ROM
 
  _data_begin = LOADADDR(.data);
  _data_end   = LOADADDR(.rosdata) + SIZEOF(.rosdata);
  
  /* We place the .sbss data section AFTER the .rosdata section, so that
     it can directly preceed the .bss section.  This allows runtime startup
     code to initialise all the zero-data sections by simply taking the
     value of '_edata' and zeroing until it reaches '_end'.  */

  .sbss ALIGN(4) :
  {
    __sbss_start = .;
    *(.sbss)
    *(.scommon)
  } > RAM

  _edata  = __sbss_start;

  PROVIDE (edata = _edata);

  .bss ALIGN (4) :
  {
    _bss_begin = . ;
    __real_bss_start = . ;
    *(.dynbss)
    *(.bss)
    *(COMMON)
  } > RAM

  _bss_end = . ;
  _end = . ;

  PROVIDE (end = .);

  . = 0x03FFE800;
  . = ALIGN(4);

  /* User STACK.  */
  .STACK :
  {
    *(.STACK)
  } > STACK

  _rom_data_begin = LOADADDR(.data);
}
