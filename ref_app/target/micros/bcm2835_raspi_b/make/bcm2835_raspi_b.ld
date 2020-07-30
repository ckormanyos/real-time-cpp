/*
 Copyright Christopher Kormanyos 2014 - 2020.
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
_rom_end   = 0x00010000;

/* The beginning of the RAM area */
_ram_begin = 0x00010000;

/* Set up the stacks with sizes of 4K */

__SYS_STACK_SIZE = 4K;
__SVC_STACK_SIZE = 4K;
__ABT_STACK_SIZE = 4K;
__UND_STACK_SIZE = 4K;
__IRQ_STACK_SIZE = 4K;
__FIQ_STACK_SIZE = 4K;


MEMORY
{
  ROM   (rwx) : ORIGIN = 0x00008000, LENGTH = 0x00008000
  RAM   (rwx) : ORIGIN = 0x00010000, LENGTH = 0x00008000
  STACKS(rwx) : ORIGIN = 0x00018000, LENGTH = 0x00006000
}

SECTIONS
{
  . = 0x00008000;
  . = ALIGN(4);

  /* Interrupt vector table */
  .intvect :
  {
    PROVIDE(__INTVECT_BASE_ADDRESS = .) ;
    *(.intvect)
    . = ALIGN(4);
    KEEP(*(.intvect))
  } > ROM

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

  . = 0x00010000;
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

  . = 0x00018000;
  . = ALIGN(4);

  /* user-system mode stack definition */
  .stack_sys :
  {
    . = ALIGN(MAX(__SYS_STACK_SIZE , .), 8);
    PROVIDE(__SYS_STACK_TOP = .) ;
  } > STACKS

  /* Supervisor mode stack definition */
  .stack_svc :
  {
    . = ALIGN(MAX(__SVC_STACK_SIZE , .), 8);
    PROVIDE(__SVC_STACK_TOP = .) ;
  } > STACKS

  /* Abort mode stack definition */
  .stack_abt :
  {
    . = ALIGN(MAX(__ABT_STACK_SIZE , .), 8);
    PROVIDE(__ABT_STACK_TOP = .) ;
  } > STACKS

  /* Undefined mode stack definition */
  .stack_und :
  {
    . = ALIGN(MAX(__UND_STACK_SIZE , .), 8);
    PROVIDE(__UND_STACK_TOP = .) ;
  } > STACKS

  /* Interrupt mode stack definition */
  .stack_irq :
  {
    . = ALIGN(MAX(__IRQ_STACK_SIZE , .), 8);
    PROVIDE(__IRQ_STACK_TOP = .) ;
  } > STACKS

  /* Fast interrupt mode stack definition */
  .stack_fiq :
  {
    . = ALIGN(MAX(__FIQ_STACK_SIZE , .), 8);
    PROVIDE(__FIQ_STACK_TOP = .) ;
  } > STACKS

  _rom_data_begin = LOADADDR(.data);
}
