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
/* INPUT(libc.a libm.a libgcc.a) */

/******************************************************************************************
 Globals
******************************************************************************************/
__STACK_SIZE_CORE0 = 1K;
__STACK_SIZE_CORE1 = 1K;

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
    *(.boot)
    *(.text)
    *(.text*)
    . = ALIGN(4);
  } > FLASH

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
    *(.rodata*)
  } > FLASH

 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    PROVIDE(__CTOR_LIST__  = .);
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    LONG(-1) ;
    PROVIDE(__CTOR_END__  = .);
    . = ALIGN(4);
  }  > FLASH


  /* Section for destructors */
  .dtors : ALIGN(4)
  {
    PROVIDE(__DTOR_LIST__  = .);
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    LONG(-1) ;
    PROVIDE(__DTOR_END__  = .);
    . = ALIGN(4);
  } > FLASH

  /* Runtime clear table */
  .clear_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    LONG(0 + ADDR(.bss));   LONG(SIZEOF(.bss));
    LONG(-1);                 LONG(-1);
    . = ALIGN(4);
  } > FLASH

  /* Runtime copy table */
  .copy_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
    LONG(LOADADDR(.data));   LONG(0 + ADDR(.data));   LONG(SIZEOF(.data));
    LONG(-1);                LONG(-1);                LONG(-1);
    . = ALIGN(4);
    PROVIDE(__CODE_END_ADDRESS = .);
  } > FLASH

  /* The ROM-to-RAM initialized data sections */
  .data : ALIGN(4) 
  {
    *(.data)
    *(.data*)
    . = ALIGN(4);
  } > RAM  AT>FLASH
  
  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
  {
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
  } > RAM

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

}
