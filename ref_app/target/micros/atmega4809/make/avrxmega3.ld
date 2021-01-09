/*
 Copyright Christopher Kormanyos 2021.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Default linker script, for normal executables */
/* Copyright (C) 2014-2015 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */

/* Linker script for MICROCHIP(R) AVR(R) ATmega4809. */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:103)

/* The beginning and end of the program ROM area. */
_rom_begin = 0x00000000;
_rom_end   = 0x0000BFFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 0x200=(1/2)K */
_stack_begin = 0x00803E00;
_stack_end   = 0x00803FFE;

/* The initial stack pointer (top of stack) is at the top of the 6K RAM */
__initial_stack_pointer = 0x00803FFE;

__TEXT_REGION_LENGTH__   = DEFINED(__TEXT_REGION_LENGTH__)   ? __TEXT_REGION_LENGTH__   : 1024K;
__DATA_REGION_LENGTH__   = DEFINED(__DATA_REGION_LENGTH__)   ? __DATA_REGION_LENGTH__   : 0x0000FFA0;
__EEPROM_REGION_LENGTH__ = DEFINED(__EEPROM_REGION_LENGTH__) ? __EEPROM_REGION_LENGTH__ : 64K;
__FUSE_REGION_LENGTH__   = DEFINED(__FUSE_REGION_LENGTH__)   ? __FUSE_REGION_LENGTH__   : 1K;
__RODATA_PM_OFFSET__     = DEFINED(__RODATA_PM_OFFSET__)     ? __RODATA_PM_OFFSET__     : 0x00008000;

MEMORY
{
  ROM       (rx)   : ORIGIN = 0x00000000, LENGTH = __TEXT_REGION_LENGTH__
  RAM       (rw!x) : ORIGIN = 0x00802000, LENGTH = __DATA_REGION_LENGTH__
  FUSE      (rw!x) : ORIGIN = 0x00820000, LENGTH = __FUSE_REGION_LENGTH__
  LOCK      (rw!x) : ORIGIN = 0x00830000, LENGTH = __LOCK_REGION_LENGTH__
  SIGNATURE (rw!x) : ORIGIN = 0x00840000, LENGTH = __SIGNATURE_REGION_LENGTH__
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
  } > ROM = 0xAAAA

  /* Startup code */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0xAAAA

  .text :
  {
    /* For data that needs to reside in the lower 64k of progmem.  */
     *(.progmem.gcc*)
    /* PR 13812: Placing the trampolines here gives a better chance
       that they will be in range of the code that uses them.  */
    . = ALIGN(2);
     __trampolines_start = . ;
    /* The jump trampolines for the 16-bit limited relocs will reside here.  */
    *(.trampolines)
     *(.trampolines*)
     __trampolines_end = . ;
    /* avr-libc expects these data to reside in lower 64K. */
     *libc.a:*(.progmem.data)
     *(.progmem*)
    . = ALIGN(2);
    /* For code that needs to reside in the lower 128k progmem.  */
    *(.lowtext)
     *(.lowtext*)
     _ctors_begin = .;
    *(.ctors)
    . = ALIGN(2);
    KEEP (*(SORT(.ctors)))
     _ctors_end = .;
  } > ROM

  .rodata  ADDR(.text) + SIZEOF (.text) + __RODATA_PM_OFFSET__:
  {
    *(.rodata)
     *(.rodata*)
  } AT > ROM

  .data :
  {
    _data_begin = .;
    *(.data)
    *(.data*)
    . = ALIGN(2);
    _data_end = .;
  } > RAM AT > ROM

  .bss ADDR(.data) + SIZEOF (.data) : AT (ADDR (.bss))
  {
    _bss_begin = .;
    *(.bss)
     *(.bss*)
    *(COMMON)
    _bss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
  _rom_data_end   = _rom_data_begin + SIZEOF(.data);

  .fuse :
  {
    KEEP(*(.fuse))
    KEEP(*(.lfuse))
    KEEP(*(.hfuse))
    KEEP(*(.efuse))
  } > FUSE

  .lock :
  {
    KEEP(*(.lock*))
  } > LOCK

  .signature :
  {
    KEEP(*(.signature*))
  } > SIGNATURE
}
