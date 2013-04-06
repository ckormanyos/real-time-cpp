/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(_reset)

/*************************************************************************
 * Processor-specific object file.  Contains SFR definitions.
 *************************************************************************/
/*
INPUT("processor.o")
*/

/*************************************************************************
 * For interrupt vector handling
 *************************************************************************/
PROVIDE(_vector_spacing = 0x00000001);
_ebase_address = 0x9FC01000;

/*************************************************************************
 * Memory Address Equates
 * _RESET_ADDR      -- Reset Vector
 * _BEV_EXCPT_ADDR  -- Boot exception Vector
 * _DBG_EXCPT_ADDR  -- In-circuit Debugging Exception Vector
 * _DBG_CODE_ADDR   -- In-circuit Debug Executive address
 * _DBG_CODE_SIZE   -- In-circuit Debug Executive size
 * _GEN_EXCPT_ADDR  -- General Exception Vector
 *************************************************************************/
_RESET_ADDR              = 0xBFC00000;
_BEV_EXCPT_ADDR          = 0xBFC00380;
_DBG_EXCPT_ADDR          = 0xBFC00480;
_DBG_CODE_ADDR           = 0xBFC02000;
_DBG_CODE_SIZE           = 0xFF0     ;
_GEN_EXCPT_ADDR          = _ebase_address + 0x180;

/*************************************************************************
 * Memory Regions
 *
 * Memory regions without attributes cannot be used for orphaned sections.
 * Only sections specifically assigned to these regions can be allocated
 * into these regions.
 *************************************************************************/
MEMORY
{
  kseg0_program_mem    (rx)  : ORIGIN = 0x9D000000, LENGTH = 0x40000
  kseg0_boot_mem             : ORIGIN = 0x9FC00490, LENGTH = 0x970
  exception_mem              : ORIGIN = 0x9FC01000, LENGTH = 0x1000
  kseg1_boot_mem             : ORIGIN = 0xBFC00000, LENGTH = 0x490
  debug_exec_mem             : ORIGIN = 0xBFC02000, LENGTH = 0xFF0
  config3                    : ORIGIN = 0xBFC02FF0, LENGTH = 0x4
  config2                    : ORIGIN = 0xBFC02FF4, LENGTH = 0x4
  config1                    : ORIGIN = 0xBFC02FF8, LENGTH = 0x4
  config0                    : ORIGIN = 0xBFC02FFC, LENGTH = 0x4
  kseg1_data_mem       (w!x) : ORIGIN = 0xA0000000, LENGTH = 0x10000
  sfrs                       : ORIGIN = 0xBF800000, LENGTH = 0x100000
  configsfrs                 : ORIGIN = 0xBFC02FF0, LENGTH = 0x10
}

/*************************************************************************
 * Configuration-word sections
 *************************************************************************/
SECTIONS
{
  .config_BFC02FF0 : {
    KEEP(*(.config_BFC02FF0))
  } > config3
  .config_BFC02FF4 : {
    KEEP(*(.config_BFC02FF4))
  } > config2
  .config_BFC02FF8 : {
    KEEP(*(.config_BFC02FF8))
  } > config1
  .config_BFC02FFC : {
    KEEP(*(.config_BFC02FFC))
  } > config0
}

/*
* Provide for a minimum stack and heap size
* - _min_stack_size - represents the minimum space that must be made
* available for the stack. Can be overridden from
* the command line using the linker's --defsym option.
* - _min_heap_size - represents the minimum space that must be made
* available for the heap. Can be overridden from
* the command line using the linker's --defsym option.
*/
EXTERN (_min_stack_size _min_heap_size)
PROVIDE(_min_stack_size = 0x400) ;
PROVIDE(_min_heap_size = 0) ;
SECTIONS
{
/* Boot Sections */
.reset _RESET_ADDR :
{
KEEP(*(.reset))
} > kseg1_boot_mem
.bev_excpt _BEV_EXCPT_ADDR :
{
KEEP(*(.bev_handler))
} > kseg1_boot_mem
.dbg_excpt _DBG_EXCPT_ADDR (NOLOAD) :
{
. += (DEFINED (_DEBUGGER) ? 0x8 : 0x0);
} > kseg1_boot_mem
.dbg_code _DBG_CODE_ADDR (NOLOAD) :
{
. += (DEFINED (_DEBUGGER) ? 0xFF0 : 0x0);
} > debug_exec_mem
.app_excpt _GEN_EXCPT_ADDR :
{
KEEP(*(.gen_handler))
} > exception_mem
.vector_0 _ebase_address + 0x200 :
{
KEEP(*(.vector_0))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_0) <= (_vector_spacing << 5), "function at exception vector 0 too large")
.vector_1 _ebase_address + 0x200 + (_vector_spacing << 5) * 1 :
{
KEEP(*(.vector_1))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_1) <= (_vector_spacing << 5), "function at exception vector 1 too large")
.vector_2 _ebase_address + 0x200 + (_vector_spacing << 5) * 2 :
{
KEEP(*(.vector_2))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_2) <= (_vector_spacing << 5), "function at exception vector 2 too large")
.vector_3 _ebase_address + 0x200 + (_vector_spacing << 5) * 3 :
{
KEEP(*(.vector_3))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_3) <= (_vector_spacing << 5), "function at exception vector 3 too large")
.vector_4 _ebase_address + 0x200 + (_vector_spacing << 5) * 4 :
{
KEEP(*(.vector_4))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_4) <= (_vector_spacing << 5), "function at exception vector 4 too large")
.vector_5 _ebase_address + 0x200 + (_vector_spacing << 5) * 5 :
{
KEEP(*(.vector_5))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_5) <= (_vector_spacing << 5), "function at exception vector 5 too large")
.vector_6 _ebase_address + 0x200 + (_vector_spacing << 5) * 6 :
{
KEEP(*(.vector_6))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_6) <= (_vector_spacing << 5), "function at exception vector 6 too large")
.vector_7 _ebase_address + 0x200 + (_vector_spacing << 5) * 7 :
{
KEEP(*(.vector_7))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_7) <= (_vector_spacing << 5), "function at exception vector 7 too large")
.vector_8 _ebase_address + 0x200 + (_vector_spacing << 5) * 8 :
{
KEEP(*(.vector_8))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_8) <= (_vector_spacing << 5), "function at exception vector 8 too large")
.vector_9 _ebase_address + 0x200 + (_vector_spacing << 5) * 9 :
{
KEEP(*(.vector_9))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_9) <= (_vector_spacing << 5), "function at exception vector 9 too large")
.vector_10 _ebase_address + 0x200 + (_vector_spacing << 5) * 10 :
{
KEEP(*(.vector_10))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_10) <= (_vector_spacing << 5), "function at exception vector 10 too large")
.vector_11 _ebase_address + 0x200 + (_vector_spacing << 5) * 11 :
{
KEEP(*(.vector_11))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_11) <= (_vector_spacing << 5), "function at exception vector 11 too large")
.vector_12 _ebase_address + 0x200 + (_vector_spacing << 5) * 12 :
{
KEEP(*(.vector_12))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_12) <= (_vector_spacing << 5), "function at exception vector 12 too large")
.vector_13 _ebase_address + 0x200 + (_vector_spacing << 5) * 13 :
{
KEEP(*(.vector_13))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_13) <= (_vector_spacing << 5), "function at exception vector 13 too large")
.vector_14 _ebase_address + 0x200 + (_vector_spacing << 5) * 14 :
{
KEEP(*(.vector_14))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_14) <= (_vector_spacing << 5), "function at exception vector 14 too large")
.vector_15 _ebase_address + 0x200 + (_vector_spacing << 5) * 15 :
{
KEEP(*(.vector_15))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_15) <= (_vector_spacing << 5), "function at exception vector 15 too large")
.vector_16 _ebase_address + 0x200 + (_vector_spacing << 5) * 16 :
{
KEEP(*(.vector_16))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_16) <= (_vector_spacing << 5), "function at exception vector 16 too large")
.vector_17 _ebase_address + 0x200 + (_vector_spacing << 5) * 17 :
{
KEEP(*(.vector_17))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_17) <= (_vector_spacing << 5), "function at exception vector 17 too large")
.vector_18 _ebase_address + 0x200 + (_vector_spacing << 5) * 18 :
{
KEEP(*(.vector_18))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_18) <= (_vector_spacing << 5), "function at exception vector 18 too large")
.vector_19 _ebase_address + 0x200 + (_vector_spacing << 5) * 19 :
{
KEEP(*(.vector_19))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_19) <= (_vector_spacing << 5), "function at exception vector 19 too large")
.vector_20 _ebase_address + 0x200 + (_vector_spacing << 5) * 20 :
{
KEEP(*(.vector_20))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_20) <= (_vector_spacing << 5), "function at exception vector 20 too large")
.vector_21 _ebase_address + 0x200 + (_vector_spacing << 5) * 21 :
{
KEEP(*(.vector_21))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_21) <= (_vector_spacing << 5), "function at exception vector 21 too large")
.vector_22 _ebase_address + 0x200 + (_vector_spacing << 5) * 22 :
{
KEEP(*(.vector_22))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_22) <= (_vector_spacing << 5), "function at exception vector 22 too large")
.vector_23 _ebase_address + 0x200 + (_vector_spacing << 5) * 23 :
{
KEEP(*(.vector_23))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_23) <= (_vector_spacing << 5), "function at exception vector 23 too large")
.vector_24 _ebase_address + 0x200 + (_vector_spacing << 5) * 24 :
{
KEEP(*(.vector_24))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_24) <= (_vector_spacing << 5), "function at exception vector 24 too large")
.vector_25 _ebase_address + 0x200 + (_vector_spacing << 5) * 25 :
{
KEEP(*(.vector_25))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_25) <= (_vector_spacing << 5), "function at exception vector 25 too large")
.vector_26 _ebase_address + 0x200 + (_vector_spacing << 5) * 26 :
{
KEEP(*(.vector_26))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_26) <= (_vector_spacing << 5), "function at exception vector 26 too large")
.vector_27 _ebase_address + 0x200 + (_vector_spacing << 5) * 27 :
{
KEEP(*(.vector_27))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_27) <= (_vector_spacing << 5), "function at exception vector 27 too large")
.vector_28 _ebase_address + 0x200 + (_vector_spacing << 5) * 28 :
{
KEEP(*(.vector_28))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_28) <= (_vector_spacing << 5), "function at exception vector 28 too large")
.vector_29 _ebase_address + 0x200 + (_vector_spacing << 5) * 29 :
{
KEEP(*(.vector_29))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_29) <= (_vector_spacing << 5), "function at exception vector 29 too large")
.vector_30 _ebase_address + 0x200 + (_vector_spacing << 5) * 30 :
{
KEEP(*(.vector_30))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_30) <= (_vector_spacing << 5), "function at exception vector 30 too large")
.vector_31 _ebase_address + 0x200 + (_vector_spacing << 5) * 31 :
{
KEEP(*(.vector_31))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_31) <= (_vector_spacing << 5), "function at exception vector 31 too large")
.vector_32 _ebase_address + 0x200 + (_vector_spacing << 5) * 32 :
{
KEEP(*(.vector_32))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_32) <= (_vector_spacing << 5), "function at exception vector 32 too large")
.vector_33 _ebase_address + 0x200 + (_vector_spacing << 5) * 33 :
{
KEEP(*(.vector_33))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_33) <= (_vector_spacing << 5), "function at exception vector 33 too large")
.vector_34 _ebase_address + 0x200 + (_vector_spacing << 5) * 34 :
{
KEEP(*(.vector_34))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_34) <= (_vector_spacing << 5), "function at exception vector 34 too large")
.vector_35 _ebase_address + 0x200 + (_vector_spacing << 5) * 35 :
{
KEEP(*(.vector_35))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_35) <= (_vector_spacing << 5), "function at exception vector 35 too large")
.vector_36 _ebase_address + 0x200 + (_vector_spacing << 5) * 36 :
{
KEEP(*(.vector_36))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_36) <= (_vector_spacing << 5), "function at exception vector 36 too large")
.vector_37 _ebase_address + 0x200 + (_vector_spacing << 5) * 37 :
{
KEEP(*(.vector_37))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_37) <= (_vector_spacing << 5), "function at exception vector 37 too large")
.vector_38 _ebase_address + 0x200 + (_vector_spacing << 5) * 38 :
{
KEEP(*(.vector_38))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_38) <= (_vector_spacing << 5), "function at exception vector 38 too large")
.vector_39 _ebase_address + 0x200 + (_vector_spacing << 5) * 39 :
{
KEEP(*(.vector_39))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_39) <= (_vector_spacing << 5), "function at exception vector 39 too large")
.vector_40 _ebase_address + 0x200 + (_vector_spacing << 5) * 40 :
{
KEEP(*(.vector_40))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_40) <= (_vector_spacing << 5), "function at exception vector 40 too large")
.vector_41 _ebase_address + 0x200 + (_vector_spacing << 5) * 41 :
{
KEEP(*(.vector_41))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_41) <= (_vector_spacing << 5), "function at exception vector 41 too large")
.vector_42 _ebase_address + 0x200 + (_vector_spacing << 5) * 42 :
{
KEEP(*(.vector_42))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_42) <= (_vector_spacing << 5), "function at exception vector 42 too large")
.vector_43 _ebase_address + 0x200 + (_vector_spacing << 5) * 43 :
{
KEEP(*(.vector_43))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_43) <= (_vector_spacing << 5), "function at exception vector 43 too large")
.vector_44 _ebase_address + 0x200 + (_vector_spacing << 5) * 44 :
{
KEEP(*(.vector_44))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_44) <= (_vector_spacing << 5), "function at exception vector 44 too large")
.vector_45 _ebase_address + 0x200 + (_vector_spacing << 5) * 45 :
{
KEEP(*(.vector_45))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_45) <= (_vector_spacing << 5), "function at exception vector 45 too large")
.vector_46 _ebase_address + 0x200 + (_vector_spacing << 5) * 46 :
{
KEEP(*(.vector_46))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_46) <= (_vector_spacing << 5), "function at exception vector 46 too large")
.vector_47 _ebase_address + 0x200 + (_vector_spacing << 5) * 47 :
{
KEEP(*(.vector_47))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_47) <= (_vector_spacing << 5), "function at exception vector 47 too large")
.vector_48 _ebase_address + 0x200 + (_vector_spacing << 5) * 48 :
{
KEEP(*(.vector_48))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_48) <= (_vector_spacing << 5), "function at exception vector 48 too large")
.vector_49 _ebase_address + 0x200 + (_vector_spacing << 5) * 49 :
{
KEEP(*(.vector_49))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_49) <= (_vector_spacing << 5), "function at exception vector 49 too large")
.vector_50 _ebase_address + 0x200 + (_vector_spacing << 5) * 50 :
{
KEEP(*(.vector_50))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_50) <= (_vector_spacing << 5), "function at exception vector 50 too large")
.vector_51 _ebase_address + 0x200 + (_vector_spacing << 5) * 51 :
{
KEEP(*(.vector_51))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_51) <= (_vector_spacing << 5), "function at exception vector 51 too large")
.vector_52 _ebase_address + 0x200 + (_vector_spacing << 5) * 52 :
{
KEEP(*(.vector_52))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_52) <= (_vector_spacing << 5), "function at exception vector 52 too large")
.vector_53 _ebase_address + 0x200 + (_vector_spacing << 5) * 53 :
{
KEEP(*(.vector_53))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_53) <= (_vector_spacing << 5), "function at exception vector 53 too large")
.vector_54 _ebase_address + 0x200 + (_vector_spacing << 5) * 54 :
{
KEEP(*(.vector_54))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_54) <= (_vector_spacing << 5), "function at exception vector 54 too large")
.vector_55 _ebase_address + 0x200 + (_vector_spacing << 5) * 55 :
{
KEEP(*(.vector_55))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_55) <= (_vector_spacing << 5), "function at exception vector 55 too large")
.vector_56 _ebase_address + 0x200 + (_vector_spacing << 5) * 56 :
{
KEEP(*(.vector_56))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_56) <= (_vector_spacing << 5), "function at exception vector 56 too large")
.vector_57 _ebase_address + 0x200 + (_vector_spacing << 5) * 57 :
{
KEEP(*(.vector_57))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_57) <= (_vector_spacing << 5), "function at exception vector 57 too large")
.vector_58 _ebase_address + 0x200 + (_vector_spacing << 5) * 58 :
{
KEEP(*(.vector_58))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_58) <= (_vector_spacing << 5), "function at exception vector 58 too large")
.vector_59 _ebase_address + 0x200 + (_vector_spacing << 5) * 59 :
{
KEEP(*(.vector_59))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_59) <= (_vector_spacing << 5), "function at exception vector 59 too large")
.vector_60 _ebase_address + 0x200 + (_vector_spacing << 5) * 60 :
{
KEEP(*(.vector_60))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_60) <= (_vector_spacing << 5), "function at exception vector 60 too large")
.vector_61 _ebase_address + 0x200 + (_vector_spacing << 5) * 61 :
{
KEEP(*(.vector_61))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_61) <= (_vector_spacing << 5), "function at exception vector 61 too large")
.vector_62 _ebase_address + 0x200 + (_vector_spacing << 5) * 62 :
{
KEEP(*(.vector_62))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_62) <= (_vector_spacing << 5), "function at exception vector 62 too large")
.vector_63 _ebase_address + 0x200 + (_vector_spacing << 5) * 63 :
{
KEEP(*(.vector_63))
} > exception_mem
ASSERT (_vector_spacing == 0 || SIZEOF(.vector_63) <= (_vector_spacing << 5), "function at exception vector 63 too large")
.startup ORIGIN(kseg0_boot_mem) :
{
KEEP(*(.startup))
} > kseg0_boot_mem
/* Code Sections */
.text ORIGIN(kseg0_program_mem) :
{
_text_begin = . ;
*(.text .stub .text.* .gnu.linkonce.t.*)
KEEP (*(.text.*personality*))
/* .gnu.warning sections are handled specially by elf32.em. */
*(.gnu.warning)
*(.mips16.fn.*)
*(.mips16.call.*)
_text_end = . ;
} >kseg0_program_mem =0
/* Read-only sections */
.rodata :
{
*(.rodata .rodata.* .gnu.linkonce.r.*)
*(.rodata1)
. = ALIGN(32 / 8) ;
} >kseg0_program_mem
/*
* Small initialized constant global and static data can be placed in the
* .sdata2 section. This is different from .sdata, which contains small
* initialized non-constant global and static data.
*/
.sdata2 :
{
*(.sdata2 .sdata2.* .gnu.linkonce.s2.*)
. = ALIGN(32 / 8) ;
} >kseg0_program_mem
/*
* Uninitialized constant global and static data (i.e., variables which will
* always be zero). Again, this is different from .sbss, which contains
* small non-initialized, non-constant global and static data.
*/
.sbss2 :
{
*(.sbss2 .sbss2.* .gnu.linkonce.sb2.*)
. = ALIGN(32 / 8) ;
} >kseg0_program_mem
.eh_frame_hdr : { *(.eh_frame_hdr) }
.eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }
.dbg_data (NOLOAD) :
{
. += (DEFINED (_DEBUGGER) ? 0x200 : 0x0);
} >kseg1_data_mem
.data :
{
_data_begin = . ;
*(.data .data.* .gnu.linkonce.d.*)
KEEP (*(.gnu.linkonce.d.*personality*))
*(.data1)
} >kseg1_data_mem AT>kseg0_program_mem
_data_image_begin = LOADADDR(.data) ;
.eh_frame : ONLY_IF_RW { KEEP (*(.eh_frame)) }
_gp = ALIGN(16) + 0x7FF0 ;
.got :
{
*(.got.plt) *(.got)
} >kseg1_data_mem AT>kseg0_program_mem
/*
* We want the small data sections together, so single-instruction offsets
* can access them all, and initialized data all before uninitialized, so
* we can shorten the on-disk segment size.
*/
.sdata :
{
_sdata_begin = . ;
*(.sdata .sdata.* .gnu.linkonce.s.*)
_sdata_end = . ;
} >kseg1_data_mem AT>kseg0_program_mem
.lit8 :
{
*(.lit8)
} >kseg1_data_mem AT>kseg0_program_mem
.lit4 :
{
*(.lit4)
} >kseg1_data_mem AT>kseg0_program_mem
. = ALIGN (4) ;
_data_end = . ;
_bss_begin = . ;
.sbss :
{
_sbss_begin = . ;
*(.dynsbss)
*(.sbss .sbss.* .gnu.linkonce.sb.*)
*(.scommon)
_sbss_end = . ;
} >kseg1_data_mem
.bss :
{
*(.dynbss)
*(.bss .bss.* .gnu.linkonce.b.*)
*(COMMON)
/*
* Align here to ensure that the .bss section occupies space up to
* _end. Align after .bss to ensure correct alignment even if the
* .bss section disappears because there are no input sections.
*/
. = ALIGN(32 / 8) ;
} >kseg1_data_mem
. = ALIGN(32 / 8) ;
_end = . ;
_bss_end = . ;
/* Heap allocating takes a chunk of memory following BSS */
.heap ALIGN(4) :
{
_heap = . ;
. += _min_heap_size ;
} >kseg1_data_mem
/* Stack allocation follows the heap */
.stack ALIGN(4) :
{
_splim = . ;
_SPLIM = . ;
. += _min_stack_size ;
} >kseg1_data_mem
/*
* RAM functions go at the end of our stack and heap allocation.
* Alignment of 2K required by the boundary register (BMXDKPBA).
*/
.ramfunc ALIGN(2K) :
{
_ramfunc_begin = . ;
*(.ramfunc .ramfunc.*)
. = ALIGN(4) ;
_ramfunc_end = . ;
} >kseg1_data_mem AT>kseg0_program_mem
_ramfunc_image_begin = LOADADDR(.ramfunc) ;
_ramfunc_length = SIZEOF(.ramfunc) ;
_bmxdkpba_address = _ramfunc_begin - ORIGIN(kseg1_data_mem) ;
_bmxdudba_address = LENGTH(kseg1_data_mem) ;
_bmxdupba_address = LENGTH(kseg1_data_mem) ;
/*
* The actual top of stack should include the gap between the stack
* section and the beginning of the .ramfunc section caused by the
* alignment of the .ramfunc section minus 1 word. If RAM functions
* do not exist, then the top of the stack should point to the end of
* the data memory.
*/
_stack = (_ramfunc_length > 0)
? _ramfunc_begin - 4
: ORIGIN(kseg1_data_mem) + LENGTH(kseg1_data_mem) ;
ASSERT((_min_stack_size + _min_heap_size) <= (_stack - _heap),
"Not enough space to allocate both stack and heap. Reduce heap and/or stack size.")
/* The .pdf section belongs in the absolute section */
.pdr 0 : { *(.pdr) }
/* We don't load .reginfo onto the target, so don't locate it
* in real memory
*/
.reginfo 0 : { *(.reginfo) }
/* Stabs debugging sections. */
.stab 0 : { *(.stab) }
.stabstr 0 : { *(.stabstr) }
.stab.excl 0 : { *(.stab.excl) }
.stab.exclstr 0 : { *(.stab.exclstr) }
.stab.index 0 : { *(.stab.index) }
.stab.indexstr 0 : { *(.stab.indexstr) }
.comment 0 : { *(.comment) }
/* DWARF debug sections.
Symbols in the DWARF debugging sections are relative to the beginning
of the section so we begin them at 0. */
/* DWARF 1 */
.debug 0 : { *(.debug) }
.line 0 : { *(.line) }
/* GNU DWARF 1 extensions */
.debug_srcinfo 0 : { *(.debug_srcinfo) }
.debug_sfnames 0 : { *(.debug_sfnames) }
/* DWARF 1.1 and DWARF 2 */
.debug_aranges 0 : { *(.debug_aranges) }
.debug_pubnames 0 : { *(.debug_pubnames) }
/* DWARF 2 */
.debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
.debug_abbrev 0 : { *(.debug_abbrev) }
.debug_line 0 : { *(.debug_line) }
.debug_frame 0 : { *(.debug_frame) }
.debug_str 0 : { *(.debug_str) }
.debug_loc 0 : { *(.debug_loc) }
.debug_macinfo 0 : { *(.debug_macinfo) }
/* SGI/MIPS DWARF 2 extensions */
.debug_weaknames 0 : { *(.debug_weaknames) }
.debug_funcnames 0 : { *(.debug_funcnames) }
.debug_typenames 0 : { *(.debug_typenames) }
.debug_varnames 0 : { *(.debug_varnames) }
/DISCARD/ : { *(.note.GNU-stack) }
}
