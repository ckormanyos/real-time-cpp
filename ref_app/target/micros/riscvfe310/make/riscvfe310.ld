/*
 Copyright Christopher Kormanyos 2022.
 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/* Linker script for RISC-V FE310 SiFive MCU */

ENTRY(__my_startup)

INPUT(libc.a libm.a libgcc.a)

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

__STACK_START_ADDRESS = 0x80000000;
__STACK_SIZE = 2K;

__RAM_START_ADDRESS = 0x80000000 + __STACK_SIZE;
__RAM_SIZE =  16K - __STACK_SIZE;

MEMORY
{
  BOOT(rx)    : ORIGIN = 0x20000000,            LENGTH = 0x100
  VEC(rx)     : ORIGIN = 0x20000100,            LENGTH = 0x300
  ROM(rx)     : ORIGIN = 0x20000400,            LENGTH = 64K - 0x400
  ITIM(rx)    : ORIGIN = 0x08000000,            LENGTH = 8K
  STACK(rw)   : ORIGIN = __STACK_START_ADDRESS, LENGTH = __STACK_SIZE
  RAM(rwx)    : ORIGIN = __RAM_START_ADDRESS,   LENGTH = __RAM_SIZE
}

SECTIONS
{
  . = 0x20000000;

  .startup : ALIGN(0x10)
  {
    *(.startup)
    . = ALIGN(0x10);
    *(.startup*)
    . = ALIGN(0x10);
  } > BOOT = 0x5555

  .intvect : ALIGN(0x100)
  {
    *(.intvect)
    . = ALIGN(0x100);
    *(.intvect*)
    . = ALIGN(0x100);
  } > VEC = 0xAAAA

  /* Program code (text) */
  .text : ALIGN(0x100)
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
    *(.srodata)
    . = ALIGN(4);
    *(.srodata*)
    . = ALIGN(4);
    *(.glue_7)
    . = ALIGN(4);
    *(.glue_7t)
    . = ALIGN(4);
  } > ROM

  .riscv.extab :
  {
    . = ALIGN(4);
    *(.riscv.extab)
    *(.gnu.linkonce.riscvextab.*)
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

  .riscv.attributes : ALIGN(4)
  {
    *(.riscv.attributes)
    . = ALIGN(4);
  } > ROM


  . = __STACK_START_ADDRESS;

  /* stack definition */
  .stack :
  {
    . = ALIGN(MAX(__STACK_SIZE , .), 8);
    PROVIDE(__initial_stack_pointer = .) ;
  } > STACK

  . = __RAM_START_ADDRESS;
  . = ALIGN(4);

  /* The ROM-to-RAM initialized data section */
  .data : ALIGN(4)
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
  .bss : ALIGN(4)
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
}
