
/*
 Copyright Christopher Kormanyos 2007 - 2018.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for ATMEL(R) AVR(R) ATmega2560. */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:6)

/* The beginning and end of the program ROM area. */
_rom_begin = 0x00000000;
_rom_end   = 0x0000FFFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 2K */
_stack_begin = 0x801800;
_stack_end   = 0x802000;

/* The initial stack pointer (top of stack) is at the top of the 8K RAM */
__initial_stack_pointer = 0x802000;

MEMORY
{
  ROM(rx)   : ORIGIN = 0, LENGTH = 64K - 4
  RAM(rw!x) : ORIGIN = 0x800100, LENGTH = 0x1700
}

SECTIONS
{
  . = 0x0;
  . = ALIGN(2);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x80);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Startup code */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0xAAAA

  /* ISR handlers */
  .isr_handlers :
  {
    *(.isr_handlers)
    . = ALIGN(0x10);
    KEEP(*(.isr_handlers))
  } > ROM = 0xAAAA

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.ctors)
    . = ALIGN(2);
    KEEP (*(SORT(.ctors)))
    _ctors_end = .;
    . = ALIGN(2);
    *(.progmem*)
    . = ALIGN(2);
    *(.trampolines*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text*)
    . = ALIGN(2);
  } > ROM

  .text :
  {
    . = ALIGN(0x10);
  } > ROM = 0xAAAA

  . = 0x800100;
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
    *(.rodata)  /* Do *NOT* move this! Include .rodata here if gcc is used with -fdata-sections. */
    . = ALIGN(2);
    KEEP (*(.rodata))
    *(.rodata*)
    . = ALIGN(2);
    KEEP (*(.rodata*))
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
