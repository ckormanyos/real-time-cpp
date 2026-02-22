/*
 Copyright Christopher Kormanyos 2026.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Originally from: */
/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Linker descriptor file
  
******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

/******************************************************************************************
 Link librariess
******************************************************************************************/
INPUT(libc.a libm.a libgcc.a)

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
  HP_TCM(rwx)   : ORIGIN = 0x20000000, LENGTH = 8k
  FLASH(rx)     : ORIGIN = 0x40005000, LENGTH = 31M
  LP_FLASH(rx)  : ORIGIN = 0x41F00000, LENGTH = 1M
  RAM(rwx)      : ORIGIN = 0x48000000, LENGTH = 31M
  HP_L2MEM(rwx) : ORIGIN = 0x4FF00000, LENGTH = 768K
  LP_SRAM(rwx)  : ORIGIN = 0x50108000, LENGTH = 32K
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  /* Program code (text) */
  .text : ALIGN(4)
  {
    PROVIDE(__CODE_BASE_ADDRESS = .);
    . = ALIGN(4);
    *(.boot)
    . = ALIGN(4);
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
    *(.srodata)
    . = ALIGN(4);
    *(.srodata*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > FLASH

  .riscv.extab :
  {
    . = ALIGN(4);
    *(.riscv.extab)
    *(.gnu.linkonce.riscvextab.*)
    . = ALIGN(4);
  } > FLASH

  .exidx :
  {
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    *(.riscv.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > FLASH

  .riscv.attributes : ALIGN(4)
  {
    *(.riscv.attributes)
    . = ALIGN(4);
  } > FLASH

  /* The ROM-to-RAM initialized data sections */
  .data : ALIGN(4) 
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _small_ram_begin = .;
    *(.sdata)
    . = ALIGN(4);
    KEEP (*(.sdata))
    *(.sdata*)
    . = ALIGN(4);
    KEEP (*(.sdata*))
    _data_end = .;
  } > RAM  AT>FLASH

  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
  {
    _bss_begin = .;
    *(.sbss)
    . = ALIGN(4);
    KEEP (*(.sbss))
    *(.sbss*)
    . = ALIGN(4);
    KEEP (*(.sbss*))
    _small_ram_end = .;
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

  /* stack definition */
  .stack_core0 :
  {
    PROVIDE(__CORE0_STACK_BOTTOM = .) ;
    . = ALIGN(MAX(__STACK_SIZE_CORE0 , .), 8);
    PROVIDE(__CORE0_STACK_TOP = .) ;
  } > RAM

  .stack_core1 :
  {
    PROVIDE(__CORE1_STACK_BOTTOM = .) ;
    . = ALIGN(MAX(__STACK_SIZE_CORE1 , .), 8);
    PROVIDE(__CORE1_STACK_TOP = .) ;
  } > RAM

  __ULP_CODE_BASE = 0x40008000;

  /* ROM APIs */
  printf = 0x4fc00024;

  _rom_data_begin = LOADADDR(.data);

  _global_pointer = _small_ram_begin + (_small_ram_end - _small_ram_begin) / 2;
}
