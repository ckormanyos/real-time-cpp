/*
 Copyright Christopher Kormanyos 2013 - 2021.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for RaspberryPi(R) ARM(R) A11 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end of the program ROM area */
/* Set up a ROM area with a size of 512K */
_rom_begin = 0x00008000;
_rom_end   = 0x00080000;

/* The beginning of the RAM area */
_ram_begin = 0x00088000;

/* Set up the various stacks with total size of (5 * 64K). */

__SYS_STACK_SIZE = 0x10000;
__SVC_STACK_SIZE = 0x10000;
__ABT_STACK_SIZE = 0x10000;
__UND_STACK_SIZE = 0x10000;
__IRQ_STACK_SIZE = 0x10000;
__FIQ_STACK_SIZE = 0x10000;

/* Set up the memory regions. */

MEMORY
{
  ROM   (rwx) : ORIGIN = 0x00008000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x00088000, LENGTH = 24M
  STACKS(rwx) : ORIGIN = 0x01888000, LENGTH =   __SYS_STACK_SIZE
                                              + __SVC_STACK_SIZE
                                              + __ABT_STACK_SIZE
                                              + __UND_STACK_SIZE
                                              + __IRQ_STACK_SIZE
                                              + __FIQ_STACK_SIZE
}

SECTIONS
{
  . = 0x00008000;
  . = ALIGN(4);

  /* Interrupt vector table */
  .isr_vector :
  {
    PROVIDE(__INTVECT_BASE_ADDRESS = .) ;
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* Startup: This is where the program starts. */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0x5555

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    _ctors_end = .;
    *(.progmem*)
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > ROM

  .ARM.extab :
  {
    . = ALIGN(4);
    *(.ARM.extab)
    *(.gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } > ROM

  .exidx :
  {
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > ROM

  .ARM.attributes :
  {
    *(.ARM.attributes)
  } > ROM

  . = 0x00088000;
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

  PROVIDE(end = .);

  . = 0x01888000;
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
