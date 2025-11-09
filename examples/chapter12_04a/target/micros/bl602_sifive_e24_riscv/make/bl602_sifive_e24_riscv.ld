/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.06.2021
  
  Description : Linker description file for FE310 SiFive
  
******************************************************************************************/

INPUT(libc.a libm.a libgcc.a)

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

/******************************************************************************************
 Globals
******************************************************************************************/

__STACK_SIZE = 4K;

__RAM_START_ADDRESS = 0x42020000;
__RAM_SIZE =  64K - __STACK_SIZE;

__STACK_START_ADDRESS = __RAM_START_ADDRESS + __RAM_SIZE;

__ROM_START_ADDRESS = 0x23000000;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  BOOT(rx)    : ORIGIN = 0x23000000,                 LENGTH = 0x100
  VEC(rx)     : ORIGIN = 0x23000100,                 LENGTH = 0x200
  START(rx)   : ORIGIN = 0x23000300,                 LENGTH = 0x100
  ROM(rx)     : ORIGIN = 0x23000400,                 LENGTH = 256K - 0x400
  SRAM(rwx)   : ORIGIN = __RAM_START_ADDRESS,        LENGTH = 32K
  RAM(rwx)    : ORIGIN = __RAM_START_ADDRESS + 32K,  LENGTH = __RAM_SIZE - 32K
  STACK(rw)   : ORIGIN = __STACK_START_ADDRESS,      LENGTH = __STACK_SIZE
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  . = __ROM_START_ADDRESS;

  .boot : ALIGN(0x10)
  {
    *(.boot)
    . = ALIGN(0x10);
    *(.boot*)
    . = ALIGN(0x10);
  } > BOOT = 0x5555

  .startup : ALIGN(0x10)
  {
    *(.startup)
    . = ALIGN(0x10);
    *(.startup*)
    . = ALIGN(0x10);
  } > START = 0x5555

  .isr_vector : ALIGN(0x100)
  {
    *(.isr_vector)
    . = ALIGN(0x100);
    *(.isr_vector*)
    . = ALIGN(0x100);
  } > VEC = 0xAAAA

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
    *(.srodata)
    . = ALIGN(4);
    *(.srodata*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > ROM

  .riscv.extab :
  {
    . = ALIGN(4);
    *(.riscv.extab)
    *(.gnu.linkonce.riscvextab.*)
    . = ALIGN(4);
  } > ROM

  .exidx :
  {
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    *(.riscv.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > ROM

  . = __RAM_START_ADDRESS;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized sdata section */
  .sdata : ALIGN(4)
  {
    _sdata_begin = .;
    *(.sdata)
    . = ALIGN(4);
    KEEP (*(.sdata))
    *(.sdata*)
    . = ALIGN(4);
    KEEP (*(.sdata*))
    _sdata_end = .;
  } > SRAM AT > ROM

  /* The ROM-to-RAM initialized data section */
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
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) sbss section */
  .sbss : ALIGN(4)
  {
    _sbss_begin = .;
    *(.sbss)
    . = ALIGN(4);
    KEEP (*(.sbss))
    *(.sbss*)
    . = ALIGN(4);
    KEEP (*(.sbss*))
    _sbss_end = .;
  } > SRAM

  /* The uninitialized (zero-cleared) bss section */
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

  . = __STACK_START_ADDRESS;

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__initial_stack_pointer = .) ;
  } > STACK

  _srom_data_begin = LOADADDR(.sdata);
  _rom_data_begin = LOADADDR(.data);
}
