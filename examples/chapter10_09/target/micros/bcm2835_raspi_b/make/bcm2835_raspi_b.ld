/*
 Copyright Christopher Kormanyos 2013 - 2020.
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

/* Set up stacks with total size of 16K. */
_sys_stack_size = 0x4000;
_svc_stack_size = 0x4000;
_abt_stack_size = 0x4000;
_und_stack_size = 0x4000;
_irq_stack_size = 0x4000;
_fiq_stack_size = 0x4000;

/* Set up memory regions. */
MEMORY
{
  ROM   (rwx) : ORIGIN = 0x00008000,
                LENGTH = 0x00008000
  RAM   (rwx) : ORIGIN = 0x00010000,
                LENGTH = 0x00010000
  STACKS(rwx) : ORIGIN = 0x00020000,
                LENGTH =   _sys_stack_size
                         + _svc_stack_size
                         + _abt_stack_size
                         + _und_stack_size
                         + _irq_stack_size
                         + _fiq_stack_size
  POOL  (rwx) : ORIGIN = 0x00100000,
                LENGTH = 512M - 1M
}

SECTIONS
{
  . = 0x00008000;
  . = ALIGN(4);

  /* Interrupt vector table */
  .isr_vector :
  {
    PROVIDE(_intvect_base_address = .) ;
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > ROM = 0x5555

  /* Startup: This is where the program starts. */
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

  . = 0x00020000;
  . = ALIGN(4);

  /* user-system mode stack definition */
  .stack_sys :
  {
    . = ALIGN(MAX(_sys_stack_size , .), 8);
    PROVIDE(_sys_stack_top = .) ;
  } > STACKS

  /* Supervisor mode stack definition */
  .stack_svc :
  {
    . = ALIGN(MAX(_svc_stack_size , .), 8);
    PROVIDE(_svc_stack_top = .) ;
  } > STACKS

  /* Abort mode stack definition */
  .stack_abt :
  {
    . = ALIGN(MAX(_abt_stack_size , .), 8);
    PROVIDE(_abt_stack_top = .) ;
  } > STACKS

  /* Undefined mode stack definition */
  .stack_und :
  {
    . = ALIGN(MAX(_und_stack_size , .), 8);
    PROVIDE(_und_stack_top = .) ;
  } > STACKS

  /* Interrupt mode stack definition */
  .stack_irq :
  {
    . = ALIGN(MAX(_irq_stack_size , .), 8);
    PROVIDE(_irq_stack_top = .) ;
  } > STACKS

  /* Fast interrupt mode stack definition */
  .stack_fiq :
  {
    . = ALIGN(MAX(_fiq_stack_size , .), 8);
    PROVIDE(_fiq_stack_top = .) ;
  } > STACKS

  . = 0x00100000;
  . = ALIGN(4);

  .dram_noinit_pool (NOLOAD) :
  {
    *(.dram_noinit_pool)
    . = ALIGN(4);
  } > POOL

  _rom_data_begin = LOADADDR(.data);
}
