/******************************************************************************************
  Filename    : coprocessor.ld
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 24.02.2025
  
  Description : Linker description file script for ESP32-S3 co-processor (ULP-RISC-V)
  
******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
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
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
    PROVIDE(__INTVECT_BASE_ADDRESS = .);
    *(.intvect_core*)
  } > D_SRAM

 /* Section for constructors */
  .ctors : ALIGN(4)
  {
    PROVIDE(__CPPCTOR_LIST__ = .);
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    LONG(-1) ;
    PROVIDE(__CPPCTOR_END__ = .);
    . = ALIGN(4);
  }  > D_SRAM


  /* Section for destructors */
  .dtors : ALIGN(4)
  {
    PROVIDE(__CPPDTOR_LIST__ = .);
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    LONG(-1) ;
    PROVIDE(__CPPDTOR_END__ = .);
    . = ALIGN(4);
  } > D_SRAM

  /* Runtime clear table */
  .clear_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    LONG(0 + ADDR(.bss));   LONG(SIZEOF(.bss));
    LONG(-1);                 LONG(-1);
    . = ALIGN(4);
  } > D_SRAM

  /* Runtime copy table (note: note needed on esp32-s3 bootROM copied the data from flash to SRAM) */
#if 0
  .copy_sec : ALIGN(4)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
    LONG(LOADADDR(.data));  LONG(0 + ADDR(.data));  LONG(SIZEOF(.data));
    LONG(-1);                 LONG(-1);                  LONG(-1);
    . = ALIGN(4);
  } > D_SRAM
#endif

  /* The ROM-to-RAM initialized data section */
  .data :  ALIGN(4)
  {
    PROVIDE(__DATA_BASE_ADDRESS = .);
    *(.data)
    *(.data*)
  } > D_SRAM

  /* The uninitialized (zero-cleared) bss section */
  .bss : ALIGN(4)
  {
    PROVIDE(__BSS_BASE_ADDRESS = .);
    *(.bss)
    *(.bss*)
  } > D_SRAM

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .);
  } > D_SRAM
}
