/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : RV32IMAC
  
  MCU         : CH32V307VCT6
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.06.2021
  
  Description : Linker description file for WCH RISC-V MCU CH32V307VCT6
  
******************************************************************************************/

INPUT(libc.a libm.a libgcc.a)

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(__my_startup)

/******************************************************************************************
 Globals
******************************************************************************************/

__STACK_START_ADDRESS = 0x20000000;
__STACK_SIZE = 1K;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  BOOT(rx)    : ORIGIN = 0x00000000, LENGTH = 0x00000100
  FLASH(rx)   : ORIGIN = 0x00000100, LENGTH = 64K
  STACK(rw)   : ORIGIN = 0x20000000, LENGTH = 4K
  RAM(rwx)    : ORIGIN = 0x20000000 + 4K, LENGTH = 64K - 4K
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  /* Program code (text) */
  .startup : ALIGN(0x10)
  {
    *(.startup)
    . = ALIGN(0x10);
    *(.startup*)
    . = ALIGN(0x10);
  } > BOOT = 0x5555
  
  /* Program code (text) */
  .text : ALIGN(4)
  {
    PROVIDE(__CODE_BASE_ADDRESS = .);
    *(.text*)
    . = ALIGN(4);
  } > FLASH

  /* vectored IVT */
  .vivt : ALIGN(64)
  {
    PROVIDE(__VIVT_BASE_ADDRESS = .);
    *(*vivt*)
    . = ALIGN(4);
  } > FLASH

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    __CTOR_LIST__ = . ;
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors*))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    LONG(-1) ;
    __CTOR_END__ = . ;
  }  > FLASH


  /* Section for destructors */
  .dtors : ALIGN(4)
  {
    __DTOR_LIST__ = . ;
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors*))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    LONG(-1) ;
    __DTOR_END__ = . ;
  } > FLASH

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
    *(.data*)
    . = ALIGN(4);
  } > RAM  AT>FLASH
  
  .sdata : ALIGN(4) 
  {
    *(.sdata*)
    . = ALIGN(4);
  } > RAM  AT>FLASH

  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
  {
    *(.bss*)
    . = ALIGN(4);
  } > RAM
  
  .sbss : ALIGN(4)
  {
    *(.sbss*)
    . = ALIGN(4);
  } > RAM

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .) ;
  } > STACK

}
