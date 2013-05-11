
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for ATMEL(R) AVR(R) Atmega16 */

INPUT(libc.a libgcc.a)

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/* The end of the 1K RAM stack */
__stack = 0x800400;

MEMORY
{
  ROM(rx)   : ORIGIN = 0, LENGTH = 16K
  RAM(rw!x) : ORIGIN = 0x800100, LENGTH = 1K - 100
}

SECTIONS
{
  .text :
  {
    . = ALIGN(2);
    *(.isr_vector)
    KEEP(*(.isr_vector))

    . = ALIGN(2);
    _ctors_begin = . ;
     *(.ctors)
    KEEP(*(SORT(.ctors)))
    _ctors_end = . ;
    . = ALIGN(2);
    _dtors_begin = . ;
    *(.dtors)
    KEEP(*(.dtors))
    _dtors_end = . ;

    . = ALIGN(2);
    *(.init0)            /* Start here after reset. */
    KEEP (*(.init0))
    . = ALIGN(2);
    *(.init4)            /* Initializion of the data and BSS. */
    KEEP (*(.init4))
    . = ALIGN(2);
    *(.init6)            /* Initializion of the C++ constructors. */
    KEEP (*(.init6))
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text*)
    . = ALIGN(2);
    *(.rodata)
    . = ALIGN(2);
    *(.rodata*)
  } > ROM

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    . = ALIGN(2);
    _data_begin = .;
    *(.data)
    KEEP (*(.data))
    . = ALIGN(2);
    *(.data*)
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    . = ALIGN(2);
    _bss_begin = .;
    *(.bss)
    KEEP (*(.bss))
    . = ALIGN(2);
    *(.bss*)
    KEEP (*(.bss.*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
