
/*
 Copyright Christopher Kormanyos 2007 - 2018.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for LPC11C24/301 ARM(R) Cortex(TM)-M0 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
_rom_begin = 0x00000000;
_rom_end   = 0x00007FFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 2K */
_stack_begin = 0x10001800;
_stack_end   = 0x10002000;

__initial_stack_pointer = 0x10002000;

MEMORY
{
  ROM(rx)  : ORIGIN = 0x00000000, LENGTH = 32K
  RAM(rwx) : ORIGIN = 0x10000000, LENGTH = 8k
}

SECTIONS
{
  . = 0x00000000;
  . = ALIGN(4);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x100);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
    _ctors_end = .;
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } > ROM

  .text :
  {
    . = ALIGN(0x10);
  } > ROM = 0xAAAA

  . = 0x20000000;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    _bss_begin = .;
    *(.bss)
    . = ALIGN(4);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(4);
    KEEP (*(.bss*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
