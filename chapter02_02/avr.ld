/*
  Copyright Christopher Kormanyos 2007 - 2013.
  Distributed under the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt
  or copy at http://www.boost.org/LICENSE_1_0.txt)
*/


/* Default linker script, for normal executables */

OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

INPUT(libc.a libg.a libm.a libgcc.a)

MEMORY
{
  text   (rx)   : ORIGIN = 0, LENGTH = 32K
  data   (rw!x) : ORIGIN = 0x800060, LENGTH = 1K - 60
}

SECTIONS
{
  /* Internal text space or external memory.  */
  .text   :
  {
    *(.isr_vectors)
    KEEP(*(.isr_vectors))
    /* For data that needs to reside in the lower 64k of progmem.  */
    *(.progmem.gcc*)
    *(.progmem*)
    . = ALIGN(2);
     __trampolines_start = . ;
    /* The jump trampolines for the 16-bit limited relocs will reside here.  */
    *(.trampolines)
    *(.trampolines*)
     __trampolines_end = . ;
    /* For future tablejump instruction arrays for 3 byte pc devices.
       We don't relax jump/call instructions within these sections.  */
    *(.jumptables)
    *(.jumptables*)
    /* For code that needs to reside in the lower 128k progmem.  */
    *(.lowtext)
    *(.lowtext*)
     __ctors_start = . ;
     *(.ctors)
     __ctors_end = . ;
     __dtors_start = . ;
     *(.dtors)
     __dtors_end = . ;
    KEEP(SORT(*)(.ctors))
    KEEP(SORT(*)(.dtors))
    /* From this point on, we don't bother about wether the insns are
       below or above the 16 bits boundary.  */
    *(.init0)  /* Start here after reset.  */
    KEEP (*(.init0))
    *(.init4)  /* Initialize data and BSS.  */
    KEEP (*(.init4))
    *(.init6)  /* C++ constructors.  */
    KEEP (*(.init6))
    *(.text)
    . = ALIGN(2);
    *(.text.*)
    . = ALIGN(2);
    *(.fini6)  /* C++ destructors.  */
    KEEP (*(.fini6))
     _etext = . ;
  }  > text

  .data    : AT (ADDR (.text) + SIZEOF (.text))
  {
    PROVIDE (__data_start = .) ;
    *(.data)
    *(.data*)
    *(.rodata)  /* We need to include .rodata here if gcc is used */
    *(.rodata*) /* with -fdata-sections.  */
    *(.gnu.linkonce.d*)
    . = ALIGN(2);
     _edata = . ;
     PROVIDE (__data_end = .) ;
  }  > data

  .bss   : AT (ADDR (.bss))
  {
    PROVIDE (__bss_start = .) ;
    *(.bss)
    *(.bss*)
    *(COMMON)
     PROVIDE (__bss_end = .) ;
  }  > data
   __data_load_start = LOADADDR(.data);
   __data_load_end = __data_load_start + SIZEOF(.data);

  /* Global data not cleared after reset.  */
  .noinit  :
  {
    PROVIDE (__noinit_start = .) ;
    *(.noinit*)
    PROVIDE (__noinit_end = .) ;
    _end = . ;
  }  > data
}
