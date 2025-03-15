/*
 Copyright Christopher Kormanyos 2025.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Originally from: */
/******************************************************************************************
  Filename    : coprocessor.ld
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 24.02.2025
  
  Description : Linker description file script for ESP32-S3 co-processor (ULP-RISC-V)
  
******************************************************************************************/

ENTRY(_start)

/******************************************************************************************
 Globals
******************************************************************************************/
__STACK_SIZE = 1K;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  I_SRAM(rwx) : ORIGIN = 0x50000000, LENGTH = 4K
  D_SRAM(rw)  : ORIGIN = 0x50001000, LENGTH = 4K
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  .program : ALIGN(4)
  {
    *(.vector*)
    *(.boot*)
    *(.text)
    *(.text*)
  } > I_SRAM

  /* Read-only data (.rodata) (note: esp32-s3 has not data access path on I_SRAM, rodata must be move to D_SRAM) */
  .rodata : ALIGN(4)
  {
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } > D_SRAM

 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    _ctors_begin = .;
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    _ctors_end = .;
    . = ALIGN(4);
  }  > D_SRAM

  /* The ROM-to-RAM initialized data section */
  .data :  ALIGN(4)
  {
    _data_begin = .;
    *(.data)
    *(.data*)
    _data_end = .;
  } > D_SRAM

  /* The uninitialized (zero-cleared) bss section */
  .bss : ALIGN(4)
  {
    _bss_begin = .;
    *(.bss)
    *(.bss*)
    _bss_end = .;
  } > D_SRAM

  PROVIDE(end = .);
  PROVIDE(_fini = .);

  _rom_data_begin = LOADADDR(.data);

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .);
  } > D_SRAM
}
