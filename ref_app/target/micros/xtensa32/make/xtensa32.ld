
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
/* See also https://exploreembedded.com/wiki/Setting_up_Bare_Metal_Development_Toolchain_for_ESP32 */
/* See also: https://github.com/nkolban/esp32-snippets */


MEMORY
{
  IVEC(rx) : ORIGIN = 0x40000000, LENGTH = 1024
  ROM(rx)  : ORIGIN = 0x40210000, LENGTH = 32K - 4
  RAM(rwx) : ORIGIN = 0x40100000, LENGTH = 0x8000
}

SECTIONS
{
  . = 0x40000000;
  . = ALIGN(4);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > IVEC = 0xAAAA

  . = 0x40210000;
  . = ALIGN(4);

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

  . = 0x40100000;
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
