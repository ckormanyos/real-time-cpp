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

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(__my_startup)

/******************************************************************************************
 Globals
******************************************************************************************/

__FLASH_START_ADDRESS = 0x20000000;
__FLASH_SIZE          = 4M;

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
  /* Program code (text) */
  .boot : ALIGN(4)
  {
    PROVIDE(__BOOT_BASE_ADDRESS = .);
    *(.boot)
    . = ALIGN(4);
    *(.startup)
    . = ALIGN(4);
    *(.intvect)
    . = ALIGN(4);
  } > FLASH

  /* Program code (text) */
  .text : ALIGN(4)
  {
    PROVIDE(__CODE_BASE_ADDRESS = .);
    *(.progmem*)
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > FLASH

  .exidx : ALIGN(4)
  {
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > FLASH

  /* Program code (riscv.attributes) */
  .riscv.attributes : ALIGN(4)
  {
    *(.riscv.attributes)
    . = ALIGN(4);
  } > FLASH

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata.*)
    . = ALIGN(4);
  } > FLASH

 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    __CTOR_LIST__ = . ;
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    LONG(-1) ;
    __CTOR_END__ = . ;
  }  > FLASH

  /* Runtime clear table */
  .clear_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    LONG(0 + ADDR(.bss));   LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.sbss));  LONG(SIZEOF(.sbss));
    LONG(-1);               LONG(-1);
  } > FLASH

  /* Runtime copy table */
  .copy_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
    LONG(LOADADDR(.data));   LONG(0 + ADDR(.data));   LONG(SIZEOF(.data));
    LONG(LOADADDR(.sdata));  LONG(0 + ADDR(.sdata));  LONG(SIZEOF(.sdata));
    LONG(-1);                LONG(-1);                LONG(-1);
  } > FLASH 

  /* The FLASH-to-RAM initialized data sections */
  .data : ALIGN(4) 
  {
    *(.data)
    . = ALIGN(4);
  } > RAM AT > FLASH
  
  .sdata : ALIGN(4) 
  {
    *(.sdata)
    . = ALIGN(4);
  } > RAM AT > FLASH

  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
  {
    *(.bss)
    . = ALIGN(4);
    *(.bss.*)
    . = ALIGN(4);
  } > RAM
  
  .sbss : ALIGN(4)
  {
    *(.sbss)
    . = ALIGN(4);
  } > RAM

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .) ;
  } > STACK
}
