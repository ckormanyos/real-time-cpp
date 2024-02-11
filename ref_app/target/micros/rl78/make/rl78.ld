/*
 Copyright Christopher Kormanyos 2007 - 2024.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

OUTPUT_ARCH(rl78)

/* The beginning and end of the program ROM area */
__rom_begin = 0x002000;
__rom_end   = 0x00FFFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 1K */
__stack_begin = 0x0FFAE0;
__stack_end   = 0x0FFEE0;

__initial_stack_pointer = 0x0FFEE0;

MEMORY
{
  IVEC (rx)  : ORIGIN = 0x000000, LENGTH = 0x00080
  OPT  (r)   : ORIGIN = 0x0000C0, LENGTH = 0x00004
  ROM  (rx)  : ORIGIN = 0x002000, LENGTH = 0x0DFFC
  RAM  (rw)  : ORIGIN = 0x0FEF00, LENGTH = 0x00600
  STACK(rw)  : ORIGIN = 0x0FFAE0, LENGTH = 0x00400
}

SECTIONS
{
  . = 0x0;

  .ivec :
  {
    KEEP(*(.ivec))
  } > IVEC

  .opt_bytes :
  {
    KEEP(*(.opt_bytes))
  } > OPT

  /* Program code (text), ISR vectors, read-only data and static ctors */
  .text :
  {
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text.*)
    . = ALIGN(2);
    *(.plt)
    . = ALIGN(2);
    *(.rodata)
    . = ALIGN(2);
    *(.rodata*)
    . = ALIGN(2);
    __ctors_begin = .;
    KEEP (*(SORT(.ctors.*)))
    . = ALIGN(2);
    KEEP (*(.ctors))
    . = ALIGN(2);
    __ctors_end = .;
  } > ROM

  . = 0x0FEF00;

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    . = ALIGN(2);
    __data_begin = . ;
    *(.data)
    . = ALIGN(2);
    *(.data.*)
    . = ALIGN(2);
    __data_end = . ;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    . = ALIGN(2);
    __bss_begin = .;
    *(.bss)
    . = ALIGN(2);
    *(.bss*)
    . = ALIGN(2);
    __bss_end = . ;
  } > RAM

  __rom_data_begin = LOADADDR(.data);
}
