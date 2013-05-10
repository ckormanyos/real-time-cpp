
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/


OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

INPUT(libc.a)

__stack = 0x800400;

MEMORY
{
  text (rx)   : ORIGIN = 0, LENGTH = 16K
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
    _ctors_begin = . ;
     *(.ctors)
    KEEP(*(.ctors))
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
    PROVIDE(_data_begin = .);
    *(.data)
    *(.data*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(2);
    PROVIDE(_data_end = .);
  } > data

  .bss : AT(ADDR (.bss))
  {
    PROVIDE(_bss_begin = .);
    . = ALIGN(2);
    *(.bss)
    KEEP (*(.bss.))
    . = ALIGN(2);
    *(.bss*)
    KEEP (*(.bss.*))
    PROVIDE(_bss_end = .);
  } > data

  _rom_data_begin = LOADADDR(.data);
}
