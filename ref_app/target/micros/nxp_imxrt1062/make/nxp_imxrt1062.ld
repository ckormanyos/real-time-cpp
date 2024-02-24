
/*
 Copyright Christopher Kormanyos 2007 - 2024.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for NXP iMXRT1062 ARM(R) Cortex(TM)-M7 MCU */

/* ENTRY(__my_startup) */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* The beginning and end (i.e., the top) of the stack */
/* Set up a stack with a size of 8K */
_stack_begin = 0x2000E000;
_stack_end   = 0x20010000;

__initial_stack_pointer = 0x20010000 - 4;

MEMORY
{
  ROM (rx)  : ORIGIN = 0x60000000, LENGTH = 2M
  DTCM(rwx) : ORIGIN = 0x20000000, LENGTH = 64K - 8K
  RAM (rwx) : ORIGIN = 0x20200000, LENGTH = 512K
}

SECTIONS
{
  . = 0x60000000;
  . = ALIGN(4);

  PROVIDE(__ROM_START = .);

  /* Image vector table and FlexSPI NOR configuration */
  .bootRomCfg : ALIGN(4)
  {
    PROVIDE(__BOOT_ROM_CFG_BASE_ADDRESS = .);
    *(.FlexSPI_NOR_Config)
     KEEP(*(.FlexSPI_NOR_Config))
    
    *(.ImageVectorTable)
    KEEP(*(.ImageVectorTable))
  } > ROM

  /* ISR vectors */
  .isr_vector :
  {
    PROVIDE(__IVT_BASE_ADDRESS = .);
    *(.isr_vector)
    . = ALIGN(0x10);
    KEEP(*(.isr_vector))
  } > ROM = 0xAAAA

  /* startup */
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
    *(.ARM.extab*)
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

  PROVIDE(__ROM_END = .) ;

  . = 0x20000000;
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
  } > DTCM AT > ROM

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
  } > DTCM

  PROVIDE(end = .);
  PROVIDE(_fini = .);

  _rom_data_begin = LOADADDR(.data);
  __IMAGE_SIZE = __ROM_END - __ROM_START;
}
