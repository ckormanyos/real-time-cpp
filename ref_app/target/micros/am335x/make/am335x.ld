/*
*  Copyright (C) 2010 Texas Instruments Incorporated. - http://www.ti.com/
*  All rights reserved.
*/

/*
 * ld script for SitaraWare AM335x
 */

/*
 * The starting address of DDR2 SDRAM is 0x80000000.
 * Though the DDR size is >128 MB, we keep the top of the stack at
 * 128 MB. Assumed that the (application + stack depth) < 128 MB
 * The Decremeting Stack top address = 0x87FFFFF8.
 */

INPUT(libc.a libm.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
  . = 0x402F0400;
  . = ALIGN(4);

  .startcode     :
  {
    *init.o      (.text)
  }
  . = ALIGN(4);

  .text      :
  {
    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
    *(.init_array*)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array*)))
    _ctors_end = .;
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  }
  . = ALIGN(4);

  .data :
  {
    _data_start = .;
    *(.data)
    . = ALIGN(4);
    KEEP (*(.data))
    *(.data*)
    . = ALIGN(4);
    KEEP (*(.data*))
    _data_end = .;
  }
  . = ALIGN(4);

  .bss :
  {
    _bss_start = .;
    *(.bss)
    . = ALIGN(4);
    KEEP (*(.bss))
    *(.bss*)
    . = ALIGN(4);
    KEEP (*(.bss*))
    _bss_end = .;
  }
  . = ALIGN(4);

  _bss_end = .;

  __initial_stack_pointer = 0x4030A000;
}

