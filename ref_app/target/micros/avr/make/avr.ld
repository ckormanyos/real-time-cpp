
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for ATMEL(R) AVR(R) ATmega16/32, etc. */

INPUT(libc.a libm.a libgcc.a)

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
  .text :
  {
    *(.isr_vector)
    KEEP(*(.isr_vector))
    . = ALIGN(2);

    _ctors_begin = . ;
     *(.ctors)
    . = ALIGN(2);
    _ctors_end = . ;
    _dtors_begin = . ;
    *(.dtors)
    . = ALIGN(2);
    _dtors_end = . ;

    KEEP(SORT(*)(.ctors))

    *(.init0)       /* Start here after reset. */
    . = ALIGN(2);
    KEEP (*(.init0))
    *(.init4)       /* Initializion of the data and BSS. */
    . = ALIGN(2);
    KEEP (*(.init4))
    *(.init6)       /* Initializion of the C++ constructors. */
    . = ALIGN(2);
    KEEP (*(.init6))
    *(.text)
    . = ALIGN(2);
    *(.text*)
    . = ALIGN(2);
  } > ROM

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
    *(.rodata)
    . = ALIGN(2);
    *(.rodata*)
    . = ALIGN(2);
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
    KEEP (*(.bss.*))
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
}
