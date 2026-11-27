/******************************************************************************************
  Filename    : V850ES.ld

  Core        : V850ES/JG3-L

  Mcu         : uPD70F3793

  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine

  Date        : 27.10.2026

  Description : Linker description file

******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

/******************************************************************************************
 Libraries
******************************************************************************************/
INPUT(libc.a libm.a libgcc.a)

/******************************************************************************************
 Globals
******************************************************************************************/
__STACK_SIZE = 1K;

/******************************************************************************************
 Memory configuration
******************************************************************************************/

MEMORY
{
  FLASH(rx)     : ORIGIN = 0x00000000, LENGTH = 512K
  RAM(rwx)      : ORIGIN = 0x03FF5000, LENGTH = 40K
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
    *(.intvect)
    *(.boot)
    *(.text)
    *(.text*)
    . = ALIGN(4);
  } > FLASH

  .call_table_data ALIGN (4) :
  {
    PROVIDE(__ctbp = .);
    *(.call_table_data)
  } > FLASH = 0xFF

  .call_table_text :
  {
    *(.call_table_text)
  } > FLASH

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
    *(.rodata1)
  } > FLASH

  .jcr :
  {
    KEEP (*(.jcr))
  } > FLASH

  .gcc_except_table : { *(.gcc_except_table) } > FLASH
  .got              : { *(.got.plt) *(.got) } > FLASH
  .dynamic          : { *(.dynamic) } > FLASH

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
  .stack :
  {
    PROVIDE(__STACK_BOTTOM = .) ;
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .) ;
  } > RAM
}
