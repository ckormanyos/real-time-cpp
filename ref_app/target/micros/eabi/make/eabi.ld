
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for STM32F103x ARM(R) Cortex(TM)-M3 MCU */

INPUT(libc.a libm.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The end of the 8K RAM stack */
__initial_stack_pointer = 0x20002000;

MEMORY
{
  ROM(rx)   : ORIGIN = 0x08000000, LENGTH = 128K
  RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 8K
}

SECTIONS
{
  . = 0x08000000;

  /* Program code (text), ISR vectors, read-only data and static ctors */
  .text :
  {
    *(.isr_vector)
    . = ALIGN(4);
    KEEP(*(.isr_vector))

    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
    *(.init_array*)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array*)))
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

  . = 0x20000000;

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
