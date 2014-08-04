
/*
 Copyright Christopher Kormanyos 2007 - 2013.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Default linker script, for normal executables */

OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH("mips")
ENTRY(__my_startup_reset)

/* The beginning and end of the program ROM area */
_rom_begin = 0x9D000000;
_rom_end   = 0x9D07FFFC;

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
  ROM    (rx)  : ORIGIN = 0x9D000000, LENGTH = 0x08000 - 4
  IVEC   (rx)  : ORIGIN = 0x9FC01200, LENGTH = 0x00800
  RAM    (rwx) : ORIGIN = 0xA0000000, LENGTH = 0x07000
  RESET  (rx)  : ORIGIN = 0xBFC00000, LENGTH = 0x00400
  CONFIG3(r)   : ORIGIN = 0xBFC02FF0, LENGTH = 0x00004
  CONFIG2(r)   : ORIGIN = 0xBFC02FF4, LENGTH = 0x00004
  CONFIG1(r)   : ORIGIN = 0xBFC02FF8, LENGTH = 0x00004
  CONFIG0(r)   : ORIGIN = 0xBFC02FFC, LENGTH = 0x00004
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
  } > ROM

  .= 0x9FC01200;

  . = ALIGN(0x20);

  /* ISR vectors */
  /*
   * Interrupt vectors.
   * They are 64 small code segments in sequence.
   */
  .vector_0  _ebase_address + 0x200 + (_vector_spacing << 5) *  0 : { KEEP(*(.vector_0))  } > IVEC
  .vector_1  _ebase_address + 0x200 + (_vector_spacing << 5) *  1 : { KEEP(*(.vector_1))  } > IVEC
  .vector_2  _ebase_address + 0x200 + (_vector_spacing << 5) *  2 : { KEEP(*(.vector_2))  } > IVEC
  .vector_3  _ebase_address + 0x200 + (_vector_spacing << 5) *  3 : { KEEP(*(.vector_3))  } > IVEC
  .vector_4  _ebase_address + 0x200 + (_vector_spacing << 5) *  4 : { KEEP(*(.vector_4))  } > IVEC
  .vector_5  _ebase_address + 0x200 + (_vector_spacing << 5) *  5 : { KEEP(*(.vector_5))  } > IVEC
  .vector_6  _ebase_address + 0x200 + (_vector_spacing << 5) *  6 : { KEEP(*(.vector_6))  } > IVEC
  .vector_7  _ebase_address + 0x200 + (_vector_spacing << 5) *  7 : { KEEP(*(.vector_7))  } > IVEC
  .vector_8  _ebase_address + 0x200 + (_vector_spacing << 5) *  8 : { KEEP(*(.vector_8))  } > IVEC
  .vector_9  _ebase_address + 0x200 + (_vector_spacing << 5) *  9 : { KEEP(*(.vector_9))  } > IVEC
  .vector_10 _ebase_address + 0x200 + (_vector_spacing << 5) * 10 : { KEEP(*(.vector_10)) } > IVEC
  .vector_11 _ebase_address + 0x200 + (_vector_spacing << 5) * 11 : { KEEP(*(.vector_11)) } > IVEC
  .vector_12 _ebase_address + 0x200 + (_vector_spacing << 5) * 12 : { KEEP(*(.vector_12)) } > IVEC
  .vector_13 _ebase_address + 0x200 + (_vector_spacing << 5) * 13 : { KEEP(*(.vector_13)) } > IVEC
  .vector_14 _ebase_address + 0x200 + (_vector_spacing << 5) * 14 : { KEEP(*(.vector_14)) } > IVEC
  .vector_15 _ebase_address + 0x200 + (_vector_spacing << 5) * 15 : { KEEP(*(.vector_15)) } > IVEC
  .vector_16 _ebase_address + 0x200 + (_vector_spacing << 5) * 16 : { KEEP(*(.vector_16)) } > IVEC
  .vector_17 _ebase_address + 0x200 + (_vector_spacing << 5) * 17 : { KEEP(*(.vector_17)) } > IVEC
  .vector_18 _ebase_address + 0x200 + (_vector_spacing << 5) * 18 : { KEEP(*(.vector_18)) } > IVEC
  .vector_19 _ebase_address + 0x200 + (_vector_spacing << 5) * 19 : { KEEP(*(.vector_19)) } > IVEC
  .vector_20 _ebase_address + 0x200 + (_vector_spacing << 5) * 20 : { KEEP(*(.vector_20)) } > IVEC
  .vector_21 _ebase_address + 0x200 + (_vector_spacing << 5) * 21 : { KEEP(*(.vector_21)) } > IVEC
  .vector_22 _ebase_address + 0x200 + (_vector_spacing << 5) * 22 : { KEEP(*(.vector_22)) } > IVEC
  .vector_23 _ebase_address + 0x200 + (_vector_spacing << 5) * 23 : { KEEP(*(.vector_23)) } > IVEC
  .vector_24 _ebase_address + 0x200 + (_vector_spacing << 5) * 24 : { KEEP(*(.vector_24)) } > IVEC
  .vector_25 _ebase_address + 0x200 + (_vector_spacing << 5) * 25 : { KEEP(*(.vector_25)) } > IVEC
  .vector_26 _ebase_address + 0x200 + (_vector_spacing << 5) * 26 : { KEEP(*(.vector_26)) } > IVEC
  .vector_27 _ebase_address + 0x200 + (_vector_spacing << 5) * 27 : { KEEP(*(.vector_27)) } > IVEC
  .vector_28 _ebase_address + 0x200 + (_vector_spacing << 5) * 28 : { KEEP(*(.vector_28)) } > IVEC
  .vector_29 _ebase_address + 0x200 + (_vector_spacing << 5) * 29 : { KEEP(*(.vector_29)) } > IVEC
  .vector_30 _ebase_address + 0x200 + (_vector_spacing << 5) * 30 : { KEEP(*(.vector_30)) } > IVEC
  .vector_31 _ebase_address + 0x200 + (_vector_spacing << 5) * 31 : { KEEP(*(.vector_31)) } > IVEC
  .vector_32 _ebase_address + 0x200 + (_vector_spacing << 5) * 32 : { KEEP(*(.vector_32)) } > IVEC
  .vector_33 _ebase_address + 0x200 + (_vector_spacing << 5) * 33 : { KEEP(*(.vector_33)) } > IVEC
  .vector_34 _ebase_address + 0x200 + (_vector_spacing << 5) * 34 : { KEEP(*(.vector_34)) } > IVEC
  .vector_35 _ebase_address + 0x200 + (_vector_spacing << 5) * 35 : { KEEP(*(.vector_35)) } > IVEC
  .vector_36 _ebase_address + 0x200 + (_vector_spacing << 5) * 36 : { KEEP(*(.vector_36)) } > IVEC
  .vector_37 _ebase_address + 0x200 + (_vector_spacing << 5) * 37 : { KEEP(*(.vector_37)) } > IVEC
  .vector_38 _ebase_address + 0x200 + (_vector_spacing << 5) * 38 : { KEEP(*(.vector_38)) } > IVEC
  .vector_39 _ebase_address + 0x200 + (_vector_spacing << 5) * 39 : { KEEP(*(.vector_39)) } > IVEC
  .vector_40 _ebase_address + 0x200 + (_vector_spacing << 5) * 40 : { KEEP(*(.vector_40)) } > IVEC
  .vector_41 _ebase_address + 0x200 + (_vector_spacing << 5) * 41 : { KEEP(*(.vector_41)) } > IVEC
  .vector_42 _ebase_address + 0x200 + (_vector_spacing << 5) * 42 : { KEEP(*(.vector_42)) } > IVEC
  .vector_43 _ebase_address + 0x200 + (_vector_spacing << 5) * 43 : { KEEP(*(.vector_43)) } > IVEC
  .vector_44 _ebase_address + 0x200 + (_vector_spacing << 5) * 44 : { KEEP(*(.vector_44)) } > IVEC
  .vector_45 _ebase_address + 0x200 + (_vector_spacing << 5) * 45 : { KEEP(*(.vector_45)) } > IVEC
  .vector_46 _ebase_address + 0x200 + (_vector_spacing << 5) * 46 : { KEEP(*(.vector_46)) } > IVEC
  .vector_47 _ebase_address + 0x200 + (_vector_spacing << 5) * 47 : { KEEP(*(.vector_47)) } > IVEC
  .vector_48 _ebase_address + 0x200 + (_vector_spacing << 5) * 48 : { KEEP(*(.vector_48)) } > IVEC
  .vector_49 _ebase_address + 0x200 + (_vector_spacing << 5) * 49 : { KEEP(*(.vector_49)) } > IVEC
  .vector_50 _ebase_address + 0x200 + (_vector_spacing << 5) * 50 : { KEEP(*(.vector_50)) } > IVEC
  .vector_51 _ebase_address + 0x200 + (_vector_spacing << 5) * 51 : { KEEP(*(.vector_51)) } > IVEC
  .vector_52 _ebase_address + 0x200 + (_vector_spacing << 5) * 52 : { KEEP(*(.vector_52)) } > IVEC
  .vector_53 _ebase_address + 0x200 + (_vector_spacing << 5) * 53 : { KEEP(*(.vector_53)) } > IVEC
  .vector_54 _ebase_address + 0x200 + (_vector_spacing << 5) * 54 : { KEEP(*(.vector_54)) } > IVEC
  .vector_55 _ebase_address + 0x200 + (_vector_spacing << 5) * 55 : { KEEP(*(.vector_55)) } > IVEC
  .vector_56 _ebase_address + 0x200 + (_vector_spacing << 5) * 56 : { KEEP(*(.vector_56)) } > IVEC
  .vector_57 _ebase_address + 0x200 + (_vector_spacing << 5) * 57 : { KEEP(*(.vector_57)) } > IVEC
  .vector_58 _ebase_address + 0x200 + (_vector_spacing << 5) * 58 : { KEEP(*(.vector_58)) } > IVEC
  .vector_59 _ebase_address + 0x200 + (_vector_spacing << 5) * 59 : { KEEP(*(.vector_59)) } > IVEC
  .vector_60 _ebase_address + 0x200 + (_vector_spacing << 5) * 60 : { KEEP(*(.vector_60)) } > IVEC
  .vector_61 _ebase_address + 0x200 + (_vector_spacing << 5) * 61 : { KEEP(*(.vector_61)) } > IVEC
  .vector_62 _ebase_address + 0x200 + (_vector_spacing << 5) * 62 : { KEEP(*(.vector_62)) } > IVEC
  .vector_63 _ebase_address + 0x200 + (_vector_spacing << 5) * 63 : { KEEP(*(.vector_63)) } > IVEC

  . = 0xA0000000;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized data section */
  .data :
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

  /* TBD: Add the small data section after the gp if small data are used. */
  _gp = ALIGN(16) + 0x7FF0;

  /* The uninitialized (zero-cleared) data section */
  .bss :
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

  .= 0xBFC00000;

  . = ALIGN(0x4);

  .startup :
  {
    *(.startup)
  } > RESET

  .= 0xBFC02FF0;

  . = ALIGN(0x4);

  .config3 : { KEEP(*(.config3)) } > CONFIG3
  .config2 : { KEEP(*(.config2)) } > CONFIG2
  .config1 : { KEEP(*(.config1)) } > CONFIG1
  .config0 : { KEEP(*(.config0)) } > CONFIG0

  _rom_data_begin = LOADADDR(.data);
}
