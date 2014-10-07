
/*
 Copyright Michael Schnerr 2011 - 2014.
 Copyright Christopher Kormanyos 2013 - 2014.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for Bare-Metal BeagleBone(R) AM335x ARM(R) A8 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
_rom_begin = 0x402F0400;
_rom_end   = 0x402FBFFC;

/* The beginning of the RAM area */
_ram_begin = 0x402FC000;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 8K */
_stack_begin = 0x402FE000;
_stack_end   = 0x40300000;

/* The end of the stack */
__initial_stack_pointer = 0x40300000;

MEMORY
{
  ROM(rx)  : ORIGIN = 0x402F0400, LENGTH = 0xBC00 - 4
  RAM(rwx) : ORIGIN = 0x402FC000, LENGTH = 0x1000
}

SECTIONS
{
  . = _rom_begin;
  . = ALIGN(4);

  /* Startup: This is where the program starts. */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0xAAAA

  /* Non-maskable ISR vectors */
  .isr_vector_nmi :
  {
    *(.isr_vector_nmi)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector_nmi))
  } > ROM = 0xAAAA

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
