/*
 Copyright Christopher Kormanyos 2024.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for STM32F1xx ARM(R) Cortex(TM)-M3 MCU */

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY
{
  SBL(rx)   : ORIGIN = 0x10000000, LENGTH = 0x200
  VEC(rx)   : ORIGIN = 0x10000200, LENGTH = 0x200
  ROM(rx)   : ORIGIN = 0x10000400, LENGTH = 2M - 0x400
  RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 264K - 4K - 4K
}

SECTIONS
{
  /* Pico Secondary bootloader */
  .SBL :
  {
    . = ALIGN(4);
    PROVIDE(__SBL_BASE_ADDRESS = .);
    *(.SBL)
    KEEP(*(.SBL))
  } > SBL

  /* Interrupt vector table */
  .intvect :
  {
    . = ALIGN(4);
    PROVIDE(__INTVECT_BASE_ADDRESS = .);
    *(.intvect_c0)
    *(.intvect_c1)
    KEEP(*(.intvect_c0))
    KEEP(*(.intvect_c1))
  } > VEC

  /* startup */
  .startup :
  {
    *(.startup)
    . = ALIGN(0x10);
    KEEP(*(.startup))
  } > ROM = 0x5555

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    _ctors_end = .;
    *(.progmem*)
    . = ALIGN(4);
    *(.text)
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > ROM

  .ARM.extab :
  {
    . = ALIGN(4);
    *(.ARM.extab)
    *(.ARM.extab*)
    *(.gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } > ROM

  .exidx :
  {
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > ROM

  .ARM.attributes :
  {
    *(.ARM.attributes)
  } > ROM

  . = 0x20000000;
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

  PROVIDE(end = .);
  PROVIDE(_fini = .);

  _rom_data_begin = LOADADDR(.data);

  /* stack definitions */

  . = 0x2003EFF8;
  . = ALIGN(8);

  PROVIDE(__CORE1_STACK_TOP = .) ;

  . = 0x2003FFF8;
  . = ALIGN(8);

  PROVIDE(__CORE0_STACK_TOP = .) ;
}
