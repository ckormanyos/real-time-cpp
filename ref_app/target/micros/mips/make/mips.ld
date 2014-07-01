
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Default linker script, for normal executables */

OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(__my_startup)

/* The beginning and end of the program ROM area */
_rom_begin = 0x1D000000;
_rom_end   = 0x1D007FFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 4K */
_stack_begin = 0x00007000;
_stack_end   = 0x00008000;

__initial_stack_pointer = 0x00008000;

MEMORY
{
  RAM       (w)   : ORIGIN = 0x00000000, LENGTH = 0x00FFFC
  STACK     (w)   : ORIGIN = 0x00007000, LENGTH = 0x001000
  ROM       (w)   : ORIGIN = 0x1D000000, LENGTH = 0x008000 - 4
  IVEC_USER (r)   : ORIGIN = 0x1D008000, LENGTH = 0x001000
}

SECTIONS
{
  . = 0x00000000;

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    . = ALIGN(4);
    _data_begin = . ;
    *(.data)
    . = ALIGN(4);
    *(.data.*)
    . = ALIGN(4);
    _data_end = . ;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    . = ALIGN(4);
    _bss_begin = .;
    *(.bss)
    . = ALIGN(4);
    *(.bss*)
    . = ALIGN(4);
    _bss_end = . ;
  } > RAM

  . = 0x1D000000;

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text.*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    _ctors_begin = . ;
    KEEP (*(SORT(.init_array.*)))
    . = ALIGN(4);
    KEEP (*(.init_array))
    . = ALIGN(4);
    _ctors_end = . ;
  } > ROM

  . = 0x1D008000;

  /* User isr vectors */
  .ivec_user :
  {
    . = ALIGN(4);
    _vectors_begin = . ;
    KEEP(*(.vectors_user))
  } > IVEC_USER

  _rom_data_begin = LOADADDR(.data);
}
