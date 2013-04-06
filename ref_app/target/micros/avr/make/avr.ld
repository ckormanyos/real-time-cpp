
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)

INPUT(libc.a)

MEMORY
{
  text (rx)   : ORIGIN = 0, LENGTH = 32K
  data (rw!x) : ORIGIN = 0x800060, LENGTH = 1K - 60
}

SECTIONS
{
  .text :
  {
    . = ALIGN(2);
    *(.isr_vector)
    KEEP(*(.isr_vector))

    . = ALIGN(2);
    __ctors_start = . ;
     *(.ctors)
    __ctors_end = . ;
    . = ALIGN(2);
    __dtors_start = . ;
    *(.dtors)
    __dtors_end = . ;
    KEEP(SORT(*)(.ctors))
    KEEP(SORT(*)(.dtors))

    /* From this point on, we don't bother about wether the insns are
       below or above the 16 bits boundary. */
    *(.init0)            /* Start here after reset. */

    KEEP (*(.init0))
    *(.init4)            /* Initialize data and BSS. */
    KEEP (*(.init4))
    *(.init6)            /* C++ constructors. */
    KEEP (*(.init6))
    *(.text)
    . = ALIGN(2);
    *(.text.*)
    . = ALIGN(2);
    *(.fini6)            /* C++ destructors. */
    KEEP (*(.fini6))
     _etext = . ;
  } > text

  .data : AT(ADDR (.text) + SIZEOF (.text))
  {
    PROVIDE(__data_start = .);
    *(.data)
    *(.data*)
    *(.rodata)           /* We need to include .rodata here if gcc is used */
    *(.rodata*)          /* with -fdata-sections. */
    . = ALIGN(2);
    _edata = . ;
    PROVIDE(__data_end = .);
  } > data

  .bss : AT(ADDR (.bss))
  {
    PROVIDE(__bss_start = .);
    *(.bss)
    *(.bss*)
    PROVIDE(__bss_end = .);
  } > data

  __data_load_start = LOADADDR(.data);
  __data_load_end   = __data_load_start + SIZEOF(.data);
}
