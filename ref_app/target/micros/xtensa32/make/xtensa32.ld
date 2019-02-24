
/*
 Copyright Christopher Kormanyos 2019.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for xtensa32 */

INPUT(libc.a libm.a libgcc.a)

/* TBD: Finish the linker definition file. */
/* See also *.ld in a location such as: */
/* C:\Users\christopher\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.1\tools\sdk\ld */

/* The beginning and end of the program ROM area */
/* Set up a ROM area with a size of 32K - 4 - 18 */
_rom_begin = 0x400D0018;
_rom_end   = 0x400D7FFC;

MEMORY
{
  ROM(rx)  : ORIGIN = 0x400D0018, LENGTH = 32K - 4 - 18
  RAM(rwx) : ORIGIN = 0x3FFB0000, LENGTH = 0x8000
}

SECTIONS
{
  . = 0x400D0018;
  . = ALIGN(4);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x10);
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
    *(.progmem*)
    . = ALIGN(2);
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

  . = 0x3FFB0000;
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
