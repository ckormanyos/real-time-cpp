/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : ARM Cortex-R5
  
  MCU         : AM6254
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 26.07.2025
  
  Description : Linker description file
  
******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

/******************************************************************************************
 Globals
******************************************************************************************/
__SYS_STACK_SIZE = 128;
__SVC_STACK_SIZE = 128;
__ABT_STACK_SIZE = 128;
__UND_STACK_SIZE = 128;
__IRQ_STACK_SIZE = 128;
__FIQ_STACK_SIZE = 128;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  FLASH(rx)   : ORIGIN = 0x70000100, LENGTH = 8K
  RAM(rwx)    : ORIGIN = 0x70002000, LENGTH = 8K
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
  /* Program code */
  .program : ALIGN(4)
  {
    *(.intvect)
    KEEP(*(.intvect))
    *(.boot*)
    *(.text)
    *(.text*)
  } > FLASH

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
  } > FLASH

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
  }  > FLASH


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
    LONG(LOADADDR(.data));  LONG(0 + ADDR(.data));  LONG(SIZEOF(.data));
    LONG(-1);                 LONG(-1);                  LONG(-1);
    . = ALIGN(4);
  } > FLASH

  /* The ROM-to-RAM initialized data section */
  .data :  ALIGN(4)
  {
    PROVIDE(__DATA_BASE_ADDRESS = .);
    *(.data)
    *(.data*)
  } > RAM  AT>FLASH

  /* The uninitialized (zero-cleared) bss section */
  .bss : ALIGN(4)
  {
    PROVIDE(__BSS_BASE_ADDRESS = .);
    *(.bss)
    *(.bss*)
  } > RAM

  /* user-system mode stack definition */
  .stack_sys :
  {
    . = ALIGN(MAX(__SYS_STACK_SIZE , .), 8);
    PROVIDE(__SYS_STACK_TOP = .) ;
  } > RAM

  /* Supervisor mode stack definition */
  .stack_svc :
  {
    . = ALIGN(MAX(__SVC_STACK_SIZE , .), 8);
    PROVIDE(__SVC_STACK_TOP = .) ;
  } > RAM

  /* Abort mode stack definition */
  .stack_abt :
  {
    . = ALIGN(MAX(__ABT_STACK_SIZE , .), 8);
    PROVIDE(__ABT_STACK_TOP = .) ;
  } > RAM

  /* Undefined mode stack definition */
  .stack_und :
  {
    . = ALIGN(MAX(__UND_STACK_SIZE , .), 8);
    PROVIDE(__UND_STACK_TOP = .) ;
  } > RAM

  /* Interrupt mode stack definition */
  .stack_irq :
  {
    . = ALIGN(MAX(__IRQ_STACK_SIZE , .), 8);
    PROVIDE(__IRQ_STACK_TOP = .) ;
  } > RAM

  /* Fast interrupt mode stack definition */
  .stack_fiq :
  {
    . = ALIGN(MAX(__FIQ_STACK_SIZE , .), 8);
    PROVIDE(__FIQ_STACK_TOP = .) ;
  } > RAM
}
