
/*
 Copyright Christopher Kormanyos 2014.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for RaspberryPi(R) ARM(R) A11 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
_rom_begin = 0x00008000;
_rom_end   = 0x00026000;

/* The beginning of the RAM area */
_ram_begin = 0x00026000;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 4K */
_stack_begin = 0x00027000;
_stack_end   = 0x00028000;

/* The end of the stack */
__initial_stack_pointer = 0x00028000;

MEMORY
{
  VECLO(rwx) : ORIGIN = 0x00000000, LENGTH = 0x00000040
  VECHI(rwx) : ORIGIN = 0x00008000, LENGTH = 0x00000040
  ISR  (rwx) : ORIGIN = 0x00008040, LENGTH = 0x000003C0
  ROM  (rwx) : ORIGIN = 0x00008400, LENGTH = 0x0001DC00 - 4
  RAM  (rwx) : ORIGIN = 0x00026000, LENGTH = 0x00001000
}

SECTIONS
{
  . = 0x0000;
  . = ALIGN(4);

  /* Interrupt vectors low: The low interrupt vector table at address 0x0000. */
  .text.veclo :
  {
    *(.text.veclo)
    . = ALIGN(4);
    KEEP(*(.text.veclo))
  } > VECLO

  . = _rom_begin;
  . = ALIGN(4);

  /* Interrupt vectors high: The high interrupt vector table at address 0x8000. */
  .text.vechi :
  {
    *(.text.vechi)
    . = ALIGN(4);
    KEEP(*(.text.vechi))
  } > VECHI

  /* Interrupt service routines: The interrupt service routines are at fixed addresses. */
  .text.isr1  : { *(.text.isr1)  . = ALIGN(0x40); KEEP(*(.text.isr1))  } > ISR
  .text.isr2  : { *(.text.isr2)  . = ALIGN(0x40); KEEP(*(.text.isr2))  } > ISR
  .text.isr3  : { *(.text.isr3)  . = ALIGN(0x40); KEEP(*(.text.isr3))  } > ISR
  .text.isr4  : { *(.text.isr4)  . = ALIGN(0x40); KEEP(*(.text.isr4))  } > ISR
  .text.isr5  : { *(.text.isr5)  . = ALIGN(0x40); KEEP(*(.text.isr5))  } > ISR
  .text.isr6  : { *(.text.isr6)  . = ALIGN(0x40); KEEP(*(.text.isr6))  } > ISR
  .text.isr7  : { *(.text.isr7)  . = ALIGN(0x40); KEEP(*(.text.isr7))  } > ISR
  .text.isr8  : { *(.text.isr8)  . = ALIGN(0x40); KEEP(*(.text.isr8))  } > ISR
  .text.isr9  : { *(.text.isr9)  . = ALIGN(0x40); KEEP(*(.text.isr9))  } > ISR
  .text.isr10 : { *(.text.isr10) . = ALIGN(0x40); KEEP(*(.text.isr10)) } > ISR
  .text.isr11 : { *(.text.isr11) . = ALIGN(0x40); KEEP(*(.text.isr11)) } > ISR
  .text.isr12 : { *(.text.isr12) . = ALIGN(0x40); KEEP(*(.text.isr12)) } > ISR
  .text.isr13 : { *(.text.isr13) . = ALIGN(0x40); KEEP(*(.text.isr13)) } > ISR
  .text.isr14 : { *(.text.isr14) . = ALIGN(0x40); KEEP(*(.text.isr14)) } > ISR
  .text.isr15 : { *(.text.isr15) . = ALIGN(0x40); KEEP(*(.text.isr15)) } > ISR

  /* Startup: This is the startup code. */
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
