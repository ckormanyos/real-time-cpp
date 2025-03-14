/*
 Copyright Christopher Kormanyos 2025.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Originally from: */
/******************************************************************************************
  Filename    : Memory_Map.ld

  Core        : Xtensa LX7

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 16.02.2025

  Description : Linker description file script for ESP32-S3

******************************************************************************************/

ENTRY(_start)

INPUT(libgcc_call0_abi.a libc_call0_abi.a libg_call0_abi.a libm_call0_abi.a)

/******************************************************************************************
 Globals
******************************************************************************************/
__STACK_SIZE_CORE0 = 4K;
__STACK_SIZE_CORE1 = 4K;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  D_SRAM(rwx)   : ORIGIN = 0x3FC88000, LENGTH = 480K
  I_SRAM(rw)    : ORIGIN = 0x40370000, LENGTH = 448K
  ULP_SRAM(rwx) : ORIGIN = 0x50000000, LENGTH = 8K
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  .program : ALIGN(4)
  {
    . = ALIGN(4);
    *(.vector*)
    . = ALIGN(4);
    *(.startup*)
    . = ALIGN(4);
    *(.literal)
    . = ALIGN(4);
    *(.literal*)
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
  } > I_SRAM

  /* Read-only data (.rodata) (note: esp32-s3 has not data access path on I_SRAM, rodata must be move to D_SRAM) */
  .rodata : ALIGN(4)
  {
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    PROVIDE(__INTVECT_BASE_ADDRESS = .);
    *(.intvect_core*)
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
  .stack_core0 :
  {
    . = ALIGN(MAX(__STACK_SIZE_CORE0 , .), 16);
    PROVIDE(__CORE0_STACK_TOP = .) ;
  } > D_SRAM

  .stack_core1 :
  {
    . = ALIGN(MAX(__STACK_SIZE_CORE1 , .), 16);
    PROVIDE(__CORE1_STACK_TOP = .) ;
  } > D_SRAM

  . = 0x50000000;

  .ulp :
  {
    *(.coprocessor*)
  } > ULP_SRAM
}
