/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : ARM Cortex-M4
  
  MCU         : Renesas R7FA4M1AB
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 21.10.2025
  
  Description : Linker descriptor file
  
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
  FLASH(rx)   : ORIGIN = 0x00000000, LENGTH = 256K
  CONFIG(r)   : ORIGIN = 0x01010008, LENGTH = 44
  RAM(rwx)    : ORIGIN = 0x20000000, LENGTH = 32K
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
    KEEP(*(.intvect))
    *(.boot)
    *(.text)
    . = ALIGN(4);
  } > FLASH

  .flash_config (0x00000400) : ALIGN(4)
  {
    LONG(0xffffffff); /* OFS0 */
    LONG(0xffffcfff); /* OFS1 */
    LONG(0xffffffff); /* SECMPU00 */
    LONG(0xffffffff); /* SECMPU01 */
    LONG(0xffffffff); /* SECMPU02 */
    LONG(0xffffffff); /* SECMPU03 */
    LONG(0xffffffff); /* SECMPU04 */
    LONG(0xffffffff); /* SECMPU05 */
    LONG(0xffffffff); /* SECMPU06 */
    LONG(0xffffffff); /* SECMPU07 */
    LONG(0xffffffff); /* SECMPU08 */
    LONG(0xffffffff); /* SECMPU09 */
    LONG(0xffffffff); /* SECMPU10 */
    LONG(0xffffffff); /* SECMPU11 */
    LONG(0xffffffff); /* SECMPU12 */
  } > FLASH

  .flash_config_mirror (0x00002400) : ALIGN(4)
  {
    LONG(0xffffffff); /* OFS0 */
    LONG(0xffffcfff); /* OFS1 */
    LONG(0xffffffff); /* SECMPU00 */
    LONG(0xffffffff); /* SECMPU01 */
    LONG(0xffffffff); /* SECMPU02 */
    LONG(0xffffffff); /* SECMPU03 */
    LONG(0xffffffff); /* SECMPU04 */
    LONG(0xffffffff); /* SECMPU05 */
    LONG(0xffffffff); /* SECMPU06 */
    LONG(0xffffffff); /* SECMPU07 */
    LONG(0xffffffff); /* SECMPU08 */
    LONG(0xffffffff); /* SECMPU09 */
    LONG(0xffffffff); /* SECMPU10 */
    LONG(0xffffffff); /* SECMPU11 */
    LONG(0xffffffff); /* SECMPU12 */
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
  
  .sdata : ALIGN(4) 
  {
    *(.sdata)
    . = ALIGN(4);
  } > RAM  AT>FLASH

  /* The uninitialized (zero-cleared) data sections */
  .bss : ALIGN(4)
  {
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
  } > RAM
  
  .sbss : ALIGN(4)
  {
    *(.sbss)
    . = ALIGN(4);
  } > RAM

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__STACK_TOP = .) ;
  } > RAM

  /* configuration section for Renesas R7FA4M1AB */
  .config : ALIGN(4)
  {
    PROVIDE(__CONFIG_BASE_ADDRESS = .);
    *(.config)
    KEEP(*(.config))
  } > CONFIG
}

_start = 4;
