/*
 Copyright Christopher Kormanyos 2007 - 2025.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for ATMEL(R) AVR(R) ATmega32P. */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 0x80=(1/8)K */
_stack_begin = 0x00800880;
_stack_end   = 0x00800900;

/* The initial stack pointer (top of stack) is at the top of the 2K RAM */
__initial_stack_pointer = 0x00800900 - 2;

MEMORY
{
  VEC(rx)  : ORIGIN = 0x00000000, LENGTH = 0x00000080
  ROM(rx)  : ORIGIN = 0x00000080, LENGTH = 32K - 0x00000080
  RAM(rwx) : ORIGIN = 0x00800100, LENGTH = 0x00000880 - 0x00000100
}

SECTIONS
{
  . = 0x00000000;
  . = ALIGN(2);

  /* ISR vectors */
  .isr_vector :
  {
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > VEC = 0x5555

  /* Startup code */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
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
    *(.jumptables.*)
    . = ALIGN(2);
    *(.trampolines*)
    . = ALIGN(2);
  } > ROM

  . = 0x00800100;
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
    *(.rodata)  /* Use special handling of rodata (i.e., as part of data since _const_ variables are stored in RAM for AVR arch). */
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
