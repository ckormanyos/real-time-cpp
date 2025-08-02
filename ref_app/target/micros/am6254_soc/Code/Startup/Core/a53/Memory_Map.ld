/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : ARM Cortex-A53
  
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.05.2025
  
  Description : Linker description file for 64-bit multicore ARM Cortex-A53 (ARMv8-A)
  
******************************************************************************************/

/* IMPORTANT NOTE: All addresses defined in this file has 8-byte length (ARM 64-bit) */

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
OUTPUT_ARCH(aarch64)
ENTRY(_start)

/******************************************************************************************
 Globals
******************************************************************************************/
__CORE0_EL0_STACK_SIZE = 1K;
__CORE0_EL1_STACK_SIZE = 1K;
__CORE0_EL2_STACK_SIZE = 1K;
__CORE0_EL3_STACK_SIZE = 1K;

__CORE1_EL0_STACK_SIZE = 1K;
__CORE1_EL1_STACK_SIZE = 1K;
__CORE1_EL2_STACK_SIZE = 1K;
__CORE1_EL3_STACK_SIZE = 1K;

__CORE2_EL0_STACK_SIZE = 1K;
__CORE2_EL1_STACK_SIZE = 1K;
__CORE2_EL2_STACK_SIZE = 1K;
__CORE2_EL3_STACK_SIZE = 1K;

__CORE3_EL0_STACK_SIZE = 1K;
__CORE3_EL1_STACK_SIZE = 1K;
__CORE3_EL2_STACK_SIZE = 1K;
__CORE3_EL3_STACK_SIZE = 1K;

__STACK_ALIGNEMENT_AARCH64 = 16;

__KERNEL_ROM_EL2_START_ADDRESS = 0x80080000;
__KERNEL_ROM_EL3_START_ADDRESS = 0x80000000;
__KERNEL_ROM_START_ADDRESS     = __KERNEL_ROM_EL3_START_ADDRESS;
__KERNEL_ROM_SIZE              = 32M;
__KERNEL_RAM_START_ADDRESS     = __KERNEL_ROM_START_ADDRESS + __KERNEL_ROM_SIZE;
__KERNEL_RAM_SIZE              = 32M;

/******************************************************************************************
 Internal flash configuration
******************************************************************************************/

MEMORY
{
  ROM(rx)  : ORIGIN = __KERNEL_ROM_START_ADDRESS, LENGTH = __KERNEL_ROM_SIZE
  RAM(rwx) : ORIGIN = __KERNEL_RAM_START_ADDRESS, LENGTH = __KERNEL_RAM_SIZE
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  /* Boot Manager */
  .boot : ALIGN(8)
  {
    PROVIDE(__BOOT_BASE_ADDRESS = .) ;
    *(.boot)
    KEEP(*(.boot))
  } > ROM

  /* Interrupt vector table (alignment must be 2048) */
  .intvect : ALIGN(0x800)
  {
    PROVIDE(__INTVECT_BASE_ADDRESS = .) ;
    *(.intvect)
    KEEP(*(.intvect))
  } > ROM

  /* Program code (text) */
  .text : ALIGN(8)
  {
    *(.text)
  } > ROM

  /* Read-only data (.rodata) */
  .rodata : ALIGN(8)
  {
    *(*.rodata*)
    . = ALIGN(8); /* force section size to be multiple of 8-bytes */
  } > ROM

 /* Section for constructors */
  .ctors : ALIGN(8)
  {
    __CTOR_LIST__ = . ;
    QUAD(((__CTOR_END__ - __CTOR_LIST__) / 8) - 2);
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    QUAD(0) ;
    __CTOR_END__ = . ;
  }  > ROM


  /* Section for destructors */
  .dtors : ALIGN(8)
  {
    __DTOR_LIST__ = . ;
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    QUAD(0) ;
    __DTOR_END__ = . ;
  } > ROM

  /* Runtime clear table */
  .clear_sec : ALIGN(8)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    QUAD(0 + ADDR(.bss));   QUAD(SIZEOF(.bss));
    QUAD(-1);                 QUAD(-1);
  } > ROM

  /* Runtime copy table */	
  .copy_sec : ALIGN(8)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
    QUAD(LOADADDR(.data));  QUAD(0 + ADDR(.data));  QUAD(SIZEOF(.data));
    QUAD(-1);                 QUAD(-1);                  QUAD(-1);
  } > ROM 

  /* The ROM-to-RAM initialized data section */
  .data : ALIGN(8)
  {
    *(*.data*)
    . = ALIGN(8); /* force section size to be multiple of 8-bytes */
  } > RAM  AT>ROM

  /* The uninitialized (zero-cleared) bss section */
  .bss : ALIGN(8)
  {
    *(*.bss*)
    . = ALIGN(8); /* force section size to be multiple of 8-bytes */
  } > RAM

  /* stacks definition for CORE0 */
  .stacks_core0 : ALIGN(__STACK_ALIGNEMENT_AARCH64)
  {
    . = ALIGN(MAX(__CORE0_EL0_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE0_EL0_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE0_EL1_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE0_EL1_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE0_EL2_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE0_EL2_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE0_EL3_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE0_EL3_STACK_TOP = .) ;
  } > RAM

  /* stacks definition for CORE1 */
  .stacks_core1 : ALIGN(__STACK_ALIGNEMENT_AARCH64)
  {
    . = ALIGN(MAX(__CORE1_EL0_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE1_EL0_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE1_EL1_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE1_EL1_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE1_EL2_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE1_EL2_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE1_EL3_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE1_EL3_STACK_TOP = .) ;
  } > RAM

  /* stacks definition for CORE2 */
  .stacks_core2 : ALIGN(__STACK_ALIGNEMENT_AARCH64)
  {
    . = ALIGN(MAX(__CORE2_EL0_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE2_EL0_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE2_EL1_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE2_EL1_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE2_EL2_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE2_EL2_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE2_EL3_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE2_EL3_STACK_TOP = .) ;
  } > RAM

  /* stacks definition for CORE3 */
  .stacks_core3 : ALIGN(__STACK_ALIGNEMENT_AARCH64)
  {
    . = ALIGN(MAX(__CORE3_EL0_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE3_EL0_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE3_EL1_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE3_EL1_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE3_EL2_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE3_EL2_STACK_TOP = .) ;

    . = . + ALIGN(MAX(__CORE3_EL3_STACK_SIZE , .), __STACK_ALIGNEMENT_AARCH64);
    PROVIDE(__CORE3_EL3_STACK_TOP = .) ;
  } > RAM

}
