
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for ATMEL(R) AVR(R) ATmega16/32, etc. */

INPUT(libc.a libm.a)

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/* The end of the 1K RAM stack */
__initial_stack_pointer = 0x800400;

MEMORY
{
  ROM(rx)   : ORIGIN = 0, LENGTH = 16K
  RAM(rw!x) : ORIGIN = 0x800100, LENGTH = 1K - 100
}

SECTIONS
{
  . = 0x0;
  . = ALIGN(2);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Startup code */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0xAAAA

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.ctors)
    . = ALIGN(2);
    KEEP (*(SORT(.ctors)))
    _ctors_end = .;
    *(.text)
    . = ALIGN(2);
    *(.text*)
    . = ALIGN(2);
    *(.rodata)
    . = ALIGN(2);
    *(.rodata*)
    . = ALIGN(2);
  } > ROM

  .text :
  {
    . = ALIGN(0x10);
  } > ROM = 0xAAAA

  .= 0x800100;
  . = ALIGN(2);

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(2);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(2);
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    _bss_begin = .;
    *(.bss)
    . = ALIGN(2);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(2);
    KEEP (*(.bss*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}

