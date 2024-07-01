
/*
 Copyright Christopher Kormanyos 2014.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for Renesas RX610 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_ARCH(rx)

/* The beginning and end of the program ROM area */
__rom_begin = 0xFFFC0000;
__rom_end   = 0xFFFCFFFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 4K */
__stack_begin = 0x00007000;
__stack_end   = 0x00008000;

__initial_stack_pointer = 0x00008000;

MEMORY
{
  RAM       (w)   : ORIGIN = 0x00000000, LENGTH = 0x00FFFC
  STACK     (w)   : ORIGIN = 0x00007000, LENGTH = 0x001000
  IVEC_USER (r)   : ORIGIN = 0xFFFC0000, LENGTH = 0x000400
  ROM       (w)   : ORIGIN = 0xFFFC0400, LENGTH = 0x00FC00
  IVEC_FIXED(r)   : ORIGIN = 0xFFFFFFD0, LENGTH = 0x000030
}

SECTIONS
{
  . = 0x00000000;

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    . = ALIGN(4);
    __data_begin = . ;
    *(.data)
    . = ALIGN(4);
    *(.data.*)
    . = ALIGN(4);
    __data_end = . ;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    . = ALIGN(4);
    __bss_begin = .;
    *(.bss)
    . = ALIGN(4);
    *(.bss*)
    . = ALIGN(4);
    __bss_end = . ;
  } > RAM

  . = 0xFFFC0000;

  /* User isr vectors */
  .ivec_user :
  {
    . = ALIGN(4);
    __vectors_begin = . ;
    KEEP(*(.vectors_user))
  } > IVEC_USER

  . = 0xFFFC0400;

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
    *(.plt)
    . = ALIGN(4);
    *(.rodata C C_2 C_1 W W_2 W_1 .rodata.* .gnu.linkonce.r.*)
    . = ALIGN(4);
    *(.rodata1)
    __ctors_begin = . ;
    KEEP (*(SORT(.init_array.*)))
    . = ALIGN(4);
    KEEP (*(.init_array))
    . = ALIGN(4);
    __ctors_end = . ;
  } > ROM

  . = 0xFFFFFFD0;

  .ivec_fixed :
  {
    . = ALIGN(4);
    KEEP(*(.vectors_fixed))
  } > IVEC_FIXED

  __rom_data_begin = LOADADDR(.data);
}
