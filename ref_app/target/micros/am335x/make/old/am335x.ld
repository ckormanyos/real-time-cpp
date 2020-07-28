
/*
 Copyright Michael Schnerr 2011 - 2013.
 Copyright Christopher Kormanyos 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for SitaraWare AM335x ARM(R) A8 MCU */

INPUT(libc.a libm.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
_rom_begin = 0x402F0400;
_rom_end   = 0x402FDFFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 4K */
_stack_begin = 0x402FF000;
_stack_end   = 0x40300000;

/* The end of the stack */
__initial_stack_pointer = 0x40300000;

MEMORY
{
  ROM(rx)  : ORIGIN = 0x402F0400, LENGTH = 0xDC00 - 4
  RAM(rwx) : ORIGIN = 0x402FE000, LENGTH = 0x1C00
}

SECTIONS
{
  . = 0x402F0400;
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

  . = 0x402FE000;
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
