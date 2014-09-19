
/*
 Copyright Michael Schnerr 2011 - 2013.
 Copyright Christopher Kormanyos 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for SitaraWare AM335x ARM(R) A8 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
_rom_begin = 0x00008000;
_rom_end   = 0x0000E000;

/* The beginning of the RAM area */
_ram_begin = 0x0000E000;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 8K */
_stack_begin = 0x0000F000;
_stack_end   = 0x00010000;

/* The end of the stack */
__initial_stack_pointer = 0x00010000;

MEMORY
{
  ROM(rx)  : ORIGIN = 0x00008000, LENGTH = 0x6000 - 4
  RAM(rwx) : ORIGIN = 0x0000E000, LENGTH = 0x1000
}

SECTIONS
{
  . = _rom_begin;
  . = ALIGN(4);

  /* Startup: This is where the program starts. */
  .text.startup :
  {
    *(.text.startup)
    . = ALIGN(0x10);
    KEEP(*(.text.startup))
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

  . = _ram_begin;
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
