/*
  Copyright Christopher Kormanyos 2007 - 2021.
  Distributed under the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt
  or copy at http://www.boost.org/LICENSE_1_0.txt)
*/


/* Default linker script, for normal executables */

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

/* The end of the 2K RAM stack */
__initial_stack_pointer = 0x00800800;

MEMORY
{
  ROM(rx)   : ORIGIN = 0x00000000, LENGTH = 32K
  RAM(rw!x) : ORIGIN = 0x00800100, LENGTH =  2K - 100
}

SECTIONS
{
  . = 0x0;
  . = ALIGN(2);

  /* ISR vectors */
  .isr_vectors :
  {
    *(.isr_vectors)
    . = ALIGN(2);
    KEEP(*(.isr_vectors))
  } > ROM

  /* Startup code */
  .startup :
  {
    *(.startup)
    . = ALIGN(2);
    KEEP(*(.startup))
  } > ROM

  /* Program code (text), read-only data and static ctors */
  .text :
  {
     __ctors_start = . ;
    *(.ctors)
    . = ALIGN(2);
    KEEP (*(SORT(.ctors)))
     __ctors_end = . ;
    *(.progmem*)
    . = ALIGN(2);
    *(.trampolines*)
    . = ALIGN(2);
    *(.text)
    . = ALIGN(2);
    *(.text*)
    . = ALIGN(2);
  } > ROM

  . = 0x800100;
  . = ALIGN(2);

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    __data_start = .;
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
    __data_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    __bss_start = .;
    *(.bss)
    . = ALIGN(2);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(2);
    KEEP (*(.bss*))
    __bss_end = .;
  } > RAM

   __data_load_start = LOADADDR(.data);
}
