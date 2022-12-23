/*
 Copyright Christopher Kormanyos 2022.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Originally from: */

/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.06.2021
  
  Description : Linker description file for FE310 SiFive
  
******************************************************************************************/

/* Linker script for RISC-V FE310 SiFive MCU */

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(__my_startup)

INPUT(libc.a libm.a libgcc.a)

/******************************************************************************************
 Globals
******************************************************************************************/

__FLASH_START_ADDRESS = 0x20000000;
__FLASH_SIZE          = 64K;

__ITIM_START_ADDRESS = 0x08000000;
__ITIM_SIZE          = 8K;

__STACK_START_ADDRESS = 0x80000000;
__STACK_SIZE = 1K;

__RAM_START_ADDRESS = 0x80000000 + __STACK_SIZE;
__RAM_SIZE =  16K - __STACK_SIZE;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  FLASH(rx)   : ORIGIN = __FLASH_START_ADDRESS, LENGTH = __FLASH_SIZE
  ITIM(rx)    : ORIGIN = __ITIM_START_ADDRESS,  LENGTH = __ITIM_SIZE
  STACK(rw)   : ORIGIN = __STACK_START_ADDRESS, LENGTH = __STACK_SIZE
  RAM(rwx)    : ORIGIN = __RAM_START_ADDRESS,   LENGTH = __RAM_SIZE
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  .startup : ALIGN(0x10)
  {
    *(.startup)
    . = ALIGN(4);
    *(.startup*)
    . = ALIGN(4);
  } > FLASH

  .intvect : ALIGN(0x100)
  {
    *(.intvect)
    . = ALIGN(4);
    *(.intvect*)
    . = ALIGN(4);
  } > FLASH

  /* Program code (text) */
  .text : ALIGN(0x100)
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
  } > FLASH

  /* Program code (riscv.attributes) */
  .riscv.attributes : ALIGN(4)
  {
    *(.riscv.attributes)
    . = ALIGN(4);
  } > FLASH

  /* The FLASH-to-RAM initialized data sections */
  .data : ALIGN(4) 
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _data_end = .;
  } > RAM AT > FLASH

  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
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
  PROVIDE(_fini = .);

  _rom_data_begin = LOADADDR(.data);

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__initial_stack_pointer = .) ;
  } > STACK
}
