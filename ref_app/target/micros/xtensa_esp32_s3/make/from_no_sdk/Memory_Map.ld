/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.02.2025
  
  Description : Linker description file script for ESP32-S3
  
******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

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
  D_SRAM(rwx) : ORIGIN = 0x3FC88000, LENGTH = 480K
  I_SRAM(rw)  : ORIGIN = 0x40370000, LENGTH = 448K
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
    *(.literal)
    . = ALIGN(4);
    *(.literal*)
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.progmem*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > I_SRAM

  /* Read-only data (.rodata) (note: esp32-s3 has not data access path on I_SRAM, rodata must be move to D_SRAM) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
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
    PROVIDE(__CPPCTOR_LIST__ = .);
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    LONG(-1) ;
    PROVIDE(__CPPCTOR_END__ = .);
    . = ALIGN(4);
  }  > D_SRAM

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
}
