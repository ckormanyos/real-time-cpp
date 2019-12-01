
/*
 Copyright Christopher Kormanyos 2014.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for Microchip(R) PIC32MX795x. */

INPUT(libc.a)

OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH("mips")
ENTRY(__my_startup_entry)

/* The beginning and end of the program ROM area */
_rom_begin = 0x9D000000;
_rom_end   = 0x9D007FFC;

/* The beginning and end (i.e., top) of the stack */
/* Set up a stack with a size of 4K */
_stack_begin = 0xA0007000;
_stack_end   = 0xA0008000;

__initial_stack_pointer = 0xA0008000;

/* Interrupt vector memory allocation definitions. */
PROVIDE(_vector_spacing = 0x00000001);
PROVIDE(_ebase_address  = 0x9FC01000);

MEMORY
{
  ROM   (rx)  : ORIGIN = 0x9D000000, LENGTH = 0x00008000 - 4
  IVEC  (rx)  : ORIGIN = 0x9FC01200, LENGTH = 0x00000800
  RAM   (rwx) : ORIGIN = 0xA0000000, LENGTH = 0x00007000
  RESET (rx)  : ORIGIN = 0xBFC00000, LENGTH = 0x00000400
  CONFIG(r)   : ORIGIN = 0xBFC02FF0, LENGTH = 0x00000010
}

SECTIONS
{
  . = 0x9D000000;
  . = ALIGN(4);

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.ctors)
    . = ALIGN(4);
    KEEP (*(SORT(.ctors)))
    _ctors_end = .;
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    *(.rodata.*)
    . = ALIGN(4);
  } > ROM

  .= 0x9FC01200;

  /* ISR vectors */
  /* Declare the interrupt vectors. */
  /* There are 64 code segments for the interrupt vectors. */
  /* Each interupt vector code segment is 32 bytes wide. */

  .vector_0  : { . = ALIGN(32); KEEP(*(.vector_0))  } > IVEC
  .vector_1  : { . = ALIGN(32); KEEP(*(.vector_1))  } > IVEC
  .vector_2  : { . = ALIGN(32); KEEP(*(.vector_2))  } > IVEC
  .vector_3  : { . = ALIGN(32); KEEP(*(.vector_3))  } > IVEC
  .vector_4  : { . = ALIGN(32); KEEP(*(.vector_4))  } > IVEC
  .vector_5  : { . = ALIGN(32); KEEP(*(.vector_5))  } > IVEC
  .vector_6  : { . = ALIGN(32); KEEP(*(.vector_6))  } > IVEC
  .vector_7  : { . = ALIGN(32); KEEP(*(.vector_7))  } > IVEC
  .vector_8  : { . = ALIGN(32); KEEP(*(.vector_8))  } > IVEC
  .vector_9  : { . = ALIGN(32); KEEP(*(.vector_9))  } > IVEC
  .vector_10 : { . = ALIGN(32); KEEP(*(.vector_10)) } > IVEC
  .vector_11 : { . = ALIGN(32); KEEP(*(.vector_11)) } > IVEC
  .vector_12 : { . = ALIGN(32); KEEP(*(.vector_12)) } > IVEC
  .vector_13 : { . = ALIGN(32); KEEP(*(.vector_13)) } > IVEC
  .vector_14 : { . = ALIGN(32); KEEP(*(.vector_14)) } > IVEC
  .vector_15 : { . = ALIGN(32); KEEP(*(.vector_15)) } > IVEC
  .vector_16 : { . = ALIGN(32); KEEP(*(.vector_16)) } > IVEC
  .vector_17 : { . = ALIGN(32); KEEP(*(.vector_17)) } > IVEC
  .vector_18 : { . = ALIGN(32); KEEP(*(.vector_18)) } > IVEC
  .vector_19 : { . = ALIGN(32); KEEP(*(.vector_19)) } > IVEC
  .vector_20 : { . = ALIGN(32); KEEP(*(.vector_20)) } > IVEC
  .vector_21 : { . = ALIGN(32); KEEP(*(.vector_21)) } > IVEC
  .vector_22 : { . = ALIGN(32); KEEP(*(.vector_22)) } > IVEC
  .vector_23 : { . = ALIGN(32); KEEP(*(.vector_23)) } > IVEC
  .vector_24 : { . = ALIGN(32); KEEP(*(.vector_24)) } > IVEC
  .vector_25 : { . = ALIGN(32); KEEP(*(.vector_25)) } > IVEC
  .vector_26 : { . = ALIGN(32); KEEP(*(.vector_26)) } > IVEC
  .vector_27 : { . = ALIGN(32); KEEP(*(.vector_27)) } > IVEC
  .vector_28 : { . = ALIGN(32); KEEP(*(.vector_28)) } > IVEC
  .vector_29 : { . = ALIGN(32); KEEP(*(.vector_29)) } > IVEC
  .vector_30 : { . = ALIGN(32); KEEP(*(.vector_30)) } > IVEC
  .vector_31 : { . = ALIGN(32); KEEP(*(.vector_31)) } > IVEC
  .vector_32 : { . = ALIGN(32); KEEP(*(.vector_32)) } > IVEC
  .vector_33 : { . = ALIGN(32); KEEP(*(.vector_33)) } > IVEC
  .vector_34 : { . = ALIGN(32); KEEP(*(.vector_34)) } > IVEC
  .vector_35 : { . = ALIGN(32); KEEP(*(.vector_35)) } > IVEC
  .vector_36 : { . = ALIGN(32); KEEP(*(.vector_36)) } > IVEC
  .vector_37 : { . = ALIGN(32); KEEP(*(.vector_37)) } > IVEC
  .vector_38 : { . = ALIGN(32); KEEP(*(.vector_38)) } > IVEC
  .vector_39 : { . = ALIGN(32); KEEP(*(.vector_39)) } > IVEC
  .vector_40 : { . = ALIGN(32); KEEP(*(.vector_40)) } > IVEC
  .vector_41 : { . = ALIGN(32); KEEP(*(.vector_41)) } > IVEC
  .vector_42 : { . = ALIGN(32); KEEP(*(.vector_42)) } > IVEC
  .vector_43 : { . = ALIGN(32); KEEP(*(.vector_43)) } > IVEC
  .vector_44 : { . = ALIGN(32); KEEP(*(.vector_44)) } > IVEC
  .vector_45 : { . = ALIGN(32); KEEP(*(.vector_45)) } > IVEC
  .vector_46 : { . = ALIGN(32); KEEP(*(.vector_46)) } > IVEC
  .vector_47 : { . = ALIGN(32); KEEP(*(.vector_47)) } > IVEC
  .vector_48 : { . = ALIGN(32); KEEP(*(.vector_48)) } > IVEC
  .vector_49 : { . = ALIGN(32); KEEP(*(.vector_49)) } > IVEC
  .vector_50 : { . = ALIGN(32); KEEP(*(.vector_50)) } > IVEC
  .vector_51 : { . = ALIGN(32); KEEP(*(.vector_51)) } > IVEC
  .vector_52 : { . = ALIGN(32); KEEP(*(.vector_52)) } > IVEC
  .vector_53 : { . = ALIGN(32); KEEP(*(.vector_53)) } > IVEC
  .vector_54 : { . = ALIGN(32); KEEP(*(.vector_54)) } > IVEC
  .vector_55 : { . = ALIGN(32); KEEP(*(.vector_55)) } > IVEC
  .vector_56 : { . = ALIGN(32); KEEP(*(.vector_56)) } > IVEC
  .vector_57 : { . = ALIGN(32); KEEP(*(.vector_57)) } > IVEC
  .vector_58 : { . = ALIGN(32); KEEP(*(.vector_58)) } > IVEC
  .vector_59 : { . = ALIGN(32); KEEP(*(.vector_59)) } > IVEC
  .vector_60 : { . = ALIGN(32); KEEP(*(.vector_60)) } > IVEC
  .vector_61 : { . = ALIGN(32); KEEP(*(.vector_61)) } > IVEC
  .vector_62 : { . = ALIGN(32); KEEP(*(.vector_62)) } > IVEC
  .vector_63 : { . = ALIGN(32); KEEP(*(.vector_63)) } > IVEC

  . = 0xA0000000;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized data section */
  .data :
  {
    _data_begin = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data.*)
    . = ALIGN(4);
    KEEP (*(.data.*))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    *(.sdata*)
    . = ALIGN(4);
    KEEP (*(.sdata*))
    _data_end = .;
  } > RAM AT > ROM

  /* Add the small data section after the gp.*/
  /* TBD: The project does not use small data. */
  /* Does anyone want to use small data? */

  _gp = ALIGN(16) + 0x7FF0;

  . = ALIGN(4);

  /* The uninitialized (zero-cleared) data section */
  .bss :
  {
    _bss_begin = .;
    *(.sbss*)
    . = ALIGN(4);
    KEEP (*(.sbss*))
    *(.sbss.*)
    . = ALIGN(4);
    KEEP (*(.sbss.*))
    *(.bss*)
    . = ALIGN(4);
    KEEP (*(.bss*))
    *(.bss.*)
    . = ALIGN(4);
    KEEP (*(.bss.*))
    _bss_end = .;
  } > RAM

  .= 0xBFC00000;

  .startup :
  {
    . = ALIGN(0x10);
    *(.startup)
  } > RESET = 0xAAAA

  .= 0xBFC02FF0;

  .config : { . = ALIGN(0x4); KEEP(*(.config)) } > CONFIG

  _rom_data_begin = LOADADDR(.data);
}
