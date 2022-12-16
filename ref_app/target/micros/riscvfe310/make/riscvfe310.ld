/*
 Copyright Christopher Kormanyos 2022.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for RISC-V FE310 MCU */

ENTRY(_start)

INPUT(libc.a libm.a libgcc.a)

__STACK_SIZE = 2K;

MEMORY
{
  ROM(rx)   : ORIGIN = 0x20000000,                LENGTH = 64K
  ITIM(rx)  : ORIGIN = 0x08000000,                LENGTH = 8K
  STACK(rw) : ORIGIN = 0x08000000,                LENGTH = __STACK_SIZE
  RAM(rwx)  : ORIGIN = 0x08000000 + __STACK_SIZE, LENGTH = 16K - __STACK_SIZE
}

SECTIONS
{
  . = 0x20000000;

  .boot : ALIGN(4)
  {
    *boot.o(.text)
    . = ALIGN(4);
  } > ROM

  /* Program code (text), read-only data and static ctors */
  .text :
  {
    _ctors_begin = .;
    *(.init_array)
    . = ALIGN(4);
    KEEP (*(SORT(.init_array)))
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

  .text :
  {
    . = ALIGN(0x10);
  } > ROM = 0xAAAA

  .exidx :
  {
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx*)
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
  } > ROM

  .riscv.attributes :
  {
    *(.riscv.attributes)
  } > ROM

  . = 0x80000000;

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE, .), 8);
    PROVIDE(__STACK_TOP = .);
  } > STACK

  . = 0x80000000 + __STACK_SIZE;
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

  /* The ROM-to-RAM initialized sdata section */
  .sdata :
  {
    _sdata_begin = .;
    *(.sdata)
    . = ALIGN(4);
    KEEP (*(.sdata))
    *(.sdata*)
    . = ALIGN(4);
    KEEP (*(.sdata*))
    _sdata_end = .;
  } > RAM AT > ROM

  /* The uninitialized (zero-cleared) bss section */
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

  /* The uninitialized (zero-cleared) sbss section */
  .sbss :
  {
    _sbss_begin = .;
    *(.sbss)
    . = ALIGN(4);
    KEEP (*(.sbss))
    *(.sbss*)
    . = ALIGN(4);
    KEEP (*(.sbss*))
    _sbss_end = .;
  } > RAM

  _rom_data_begin = LOADADDR(.data);
  _rom_sdata_begin = LOADADDR(.sdata);
}
