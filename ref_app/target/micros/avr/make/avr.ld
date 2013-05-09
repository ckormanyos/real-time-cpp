
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/


OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

INPUT(libc.a)

MEMORY
{
  text (rx)   : ORIGIN = 0, LENGTH = 32K
  data (rw!x) : ORIGIN = 0x800060, LENGTH = 1K - 60
}

SECTIONS
{
  .text :
  {
    . = ALIGN(2);
    *(.isr_vector)
    KEEP(*(.isr_vector))

    . = ALIGN(2);
    __ctors_start = . ;
     *(.ctors)
    KEEP(*(.ctors))
    __ctors_end = . ;
    . = ALIGN(2);
    __dtors_start = . ;
    *(.dtors)
    KEEP(*(.dtors))
    __dtors_end = . ;

    . = ALIGN(2);
    *(.init0)            /* Start here after reset. */
    KEEP (*(.init0))
    . = ALIGN(2);
    *(.init4)            /* Initialize data and BSS. */
    KEEP (*(.init4))
    . = ALIGN(2);
    *(.init6)            /* C++ constructors. */
    KEEP (*(.init6))
    . = ALIGN(2);
    *(.text)
    KEEP (*(.text))
    . = ALIGN(2);
    *(.text.*)
    KEEP (*(.text.*))
  } > text

  .data : AT(ADDR (.text) + SIZEOF (.text))
  {
    . = ALIGN(2);
    PROVIDE(__data_start = .);
    *(.data)
    *(.data*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(2);
    PROVIDE(__data_end = .);
  } > data

  .bss : AT(ADDR (.bss))
  {
    . = ALIGN(2);
    PROVIDE(__bss_start = .);
    *(.bss)
    *(.bss*)
    PROVIDE(__bss_end = .);
  } > data

  __data_load_start = LOADADDR(.data);
  __data_load_end   = __data_load_start + SIZEOF(.data);
}
