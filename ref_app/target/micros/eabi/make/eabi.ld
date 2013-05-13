
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for STM32F103x ARM(R) Cortex(TM)-M3 MCU */

INPUT(libc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The end of the 8K RAM stack */
_estack = 0x20002000;

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
    . = ALIGN(4);
    *(.isr_vector)
    KEEP(*(.isr_vector))

    . = ALIGN(4);
    _ctors_begin = .;
    *(.init_array)
    KEEP (*(SORT(.init_array)))
    . = ALIGN(4);
    *(.init_array*)
    KEEP (*(SORT(.init_array*)))
    _ctors_end = .;
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
  } > ROM

  . = 0x20000000;

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    . = ALIGN(4);
    _data_begin = .;
    *(.data)
    KEEP (*(.data))
    . = ALIGN(4);
    *(.data*)
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    . = ALIGN(4);
    _bss_begin = .;
    *(.bss)
    KEEP (*(.bss))
    . = ALIGN(4);
    *(.bss*)
    KEEP (*(.bss*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
