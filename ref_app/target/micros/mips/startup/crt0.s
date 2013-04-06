
#define zero $0
#define AT   $1
#define v0   $2
#define v1   $3
#define a0   $4
#define a1   $5
#define a2   $6
#define a3   $7
#define t0   $8
#define t1   $9
#define t2   $10
#define t3   $11
#define t4   $12
#define t5   $13
#define t6   $14
#define t7   $15
#define s0   $16
#define s1   $17
#define s2   $18
#define s3   $19
#define s4   $20
#define s5   $21
#define s6   $22
#define s7   $23
#define t8   $24
#define t9   $25
#define jp   $25
#define k0   $26
#define k1   $27
#define gp   $28
#define s8   $28
#define sp   $29
#define fp   $30
#define s9   $30
#define ra   $31
#define CP0_INDEX    $0
#define CP0_RANDOM   $1
#define CP0_ENTRYLO0 $2
#define CP0_ENTRYLO1 $3
#define CP0_CONTEXT  $4
#define CP0_PGMASK   $5
#define CP0_WIRED    $6
#define CP0_BADVADDR $8
#define CP0_COUNT    $9
#define CP0_ENTRYHI  $10
#define CP0_COMPARE  $11
#define CP0_STATUS   $12
#define CP0_CAUSE    $13
#define CP0_EPC      $14
#define CP0_PRID     $15
#define CP0_CONFIG   $16
#define CP0_DIAG     $22
#define CP0_TAGLO    $28
#define CP0_TAGHI    $29
#define CP0_ERREPC   $30

#define PRID_REV   0x000000FF
#define PRID_CPU   0x0000FF00
/* Processor revisions */
#define PRID_REV_QEMU       0x00
#define PRID_REV_WRT54G     0x29
#define PRID_REV_WRT54GL    0x08
#define PRID_REV_WRT350N    0x1A
#define PRID_REV_WRT160NL   0x74

#define PRID_CPU_BCM3302    0x9000
#define PRID_CPU_24K        0x9300


#define CAUSE_EXC 0x0000007C
#define CAUSE_IRQ 0x0000FF00
#define CAUSE_EXC_SHIFT 2
#define CAUSE_IRQ_SHIFT 8
#define CAUSE_SW0 0x00000100
#define CAUSE_SW1 0x00000200
#define CAUSE_HW0 0x00000400
#define CAUSE_HW1 0x00000800
#define CAUSE_HW2 0x00001000
#define CAUSE_HW3 0x00002000
#define CAUSE_HW4 0x00004000
#define CAUSE_HW5 0x00008000
#define STATUS_IE  0x00000001
#define STATUS_EXL 0x00000002
#define STATUS_ERL 0x00000004
#define STATUS_KSU 0x00000018
#define STATUS_SW0 CAUSE_SW0
#define STATUS_SW1 CAUSE_SW1
#define STATUS_HW0 CAUSE_HW0
#define STATUS_HW1 CAUSE_HW1
#define STATUS_HW2 CAUSE_HW2
#define STATUS_HW3 CAUSE_HW3
#define STATUS_HW4 CAUSE_HW4
#define STATUS_HW5 CAUSE_HW5
#define KSU_USER        0x00000010
#define KSU_SPRVSR      0x00000008
#define KSU_KERNEL      0x00000000
#define ENTRYHI_VPN2    0xFFFFF000
#define ENTRYHI_ASID    0x000000FF
#define ENTRYLO_PFN     0xFFFFFFC0
#define ENTRYLO_CCA     0x00000038
#define ENTRYLO_DIRTY   0x04
#define ENTRYLO_VALID   0x02
#define ENTRYLO_GLOBL   0x01
#define CONTEXT_BADVPN  0x00FFFFF0

#define KUSEG_BASE 0x00000000
#define KUSEG_SIZE 0x80000000
#define KSEG0_BASE 0x80000000
#define KSEG0_SIZE 0x20000000
#define KSEG1_BASE 0xA0000000
#define KSEG1_SIZE 0x20000000
#define KSEG2_BASE 0xC0000000
#define KSEG2_SIZE 0x40000000
#define PMEM_MASK  0x1FFFFFFF
#define CONTEXT 64
#define CONTEXT_WORDS (CONTEXT / sizeof(long))

#define RA_CON  (CONTEXT - 8)
#define S9_CON  52
#define S8_CON  48
#define S7_CON  44
#define S6_CON  40
#define S5_CON  36
#define S4_CON  32
#define S3_CON  28
#define S2_CON  24
#define S1_CON  20
#define S0_CON  16

#define CONFIG1_IS    22
#define CONFIG1_IL    19
#define CONFIG1_IA    16
#define CONFIG1_DS    13
#define CONFIG1_DL    10
#define CONFIG1_DA     7
#define CONFIG1_MASK   7
#define INDEX_STORE_TAG_I  0x8
#define FILL_I_CACHE       0x14
#define INDEX_STORE_TAG_D  0x9


#define C0_DDATA_LO        $28,3
#define C0_EBASE           $15,1
#define C0_INTCTL          $12,1
#define C0_SRSCTL          $12,2
#define C0_SRSMAP          $12,3
#define C0_HWRENA          $7,0


.section .reset,"ax",@progbits

.set noreorder
.ent _reset

_reset:
  # Jump to startup code
  la      $26, _startup
  jr      $26
  nop
.end _reset

.globl _reset

.section .startup,"ax",@progbits

.set noreorder
.ent _startup

_startup:

  ##################################################################
  # If entered because of an NMI, jump to the NMI handler.
  ##################################################################
  mfc0    $26,$12
  ext     $26,$26,19,1          # Extract NMI bit
  beqz    $26,_no_nmi
  nop
  la      $26,_nmi_handler
  jr      $26
  nop

_no_nmi:

  ##################################################################
  # Initialize Stack Pointer
  #   _stack is initialized by the linker script to point to the
  #    starting location of the stack in DRM
  ##################################################################
  la      $29,_stack

  ##################################################################
  # Initialize Global Pointer
  #   _gp is initialized by the linker script to point to "middle"
  #   of the small variables region
  ##################################################################
  la      $28,_gp

  ##################################################################
  # Initialize Global Pointer in Shadow Set
  #   The SRSCtl's PSS field must be set to the shadow set in which
  #   to initialize the global pointer.  Since we only have a
  #   single shadow set (besides the normal), we will initialize
  #   SRSCtl<PSS> to SRSCtl<HSS>.  We then write the global pointer
  #   to the previous shadow set to ensure that on interrupt, the
  #   global pointer has been initialized.
  ##################################################################
  mfc0    $9,$12,2                # Read SRSCtl register
  add     $11,$9,$0               # Save off current SRSCtl
  ext     $10,$9,26,4             # to obtain HSS field
  ins     $9,$10,6,4              # Put HSS field
  mtc0    $9,$12,2                # into SRSCtl<PSS>
  ehb                             # Clear hazard before using new SRSCTL
  wrpgpr  $28,$28                 # Set global pointer in PSS
  mtc0    $11,$12,2               # Restore SRSCtl

  ##################################################################
  # Clear uninitialized data sections
  ##################################################################
  la      $8,_bss_begin
  la      $9,_bss_end
  b       _bss_check
  nop

_bss_init:
  sw      $0,0x0($8)
  sw      $0,0x4($8)
  sw      $0,0x8($8)
  sw      $0,0xc($8)
  addu    $8,16
_bss_check:
  bltu    $8,$9,_bss_init
  nop

  ##################################################################
  # Copy initialized data from program flash to data memory
  #   src=_data_image_begin dst=_data_begin stop=_data_end
  ##################################################################
  la      $8,_data_image_begin
  la      $9,_data_begin
  la      $10,_data_end
  b       _init_check
  nop

_init_data:
  lw      $11,($8)
  sw      $11,($9)
  addu    $8,4
  addu    $9,4
_init_check:
  bltu    $9,$10,_init_data
  nop

  ##################################################################
  # Initialize CP0 registers
  ##################################################################
  # Initialize Count register
  ##################################################################
  mtc0    $0,$9

  ##################################################################
  # Initialize Compare register
  ##################################################################
  li      $10,-1
  mtc0    $10,$11

  ##################################################################
  # Initialize EBase register
  ##################################################################
  la      $9,_ebase_address
  mtc0    $9,$15,1

  ##################################################################
  # Initialize IntCtl register
  ##################################################################
  la      $9,_vector_spacing
  li      $10,0                    # Clear t2 and
  ins     $10,$9,5,5               # shift value to VS field
  mtc0    $10,$12,1

  ##################################################################
  # Initialize CAUSE registers
  # - Enable counting of Count register <DC = 0>
  # - Use special exception vector <IV = 1>
  # - Clear pending software interrupts <IP1:IP0 = 0>
  ##################################################################
  li      $9,0x00800000
  mtc0    $9,$13

  ##################################################################
  # Initialize STATUS register
  # - Access to Coprocessor 0 not allowed in user mode <CU0 = 0>
  # - User mode uses configured endianness <RE = 0>
  # - Preserve Bootstrap Exception vectors <BEV>
  # - Preserve soft reset <SR> and non-maskable interrupt <NMI>
  # - CorExtend enabled based on whether CorExtend User Defined
  #   Instructions have been implemented <CEE = Config<UDI>>
  # - Disable any pending interrups <IM7..IM2 = 0, IM1..IM0 = 0>
  # - Disable hardware interrupts <IPL7:IPL2 = 0>
  # - Base mode is Kernel mode <UM = 0>
  # - Error level is normal <ERL = 0>
  # - Exception level is normal <EXL = 0>
  # - Interrupts are disabled <IE = 0>
  ##################################################################
  mfc0    $8,$16
  ext     $9,$8,22,1              # Extract UDI from Config register
  sll     $9,$9,17                # Move UDI to Status.CEE location
  mfc0    $8,$12
  and     $8,$8,0x00580000        # Preserve SR, NMI, and BEV
  or      $8,$9,$8                # Include Status.CEE (from UDI)
  mtc0    $8,$12

  ##################################################################
  # Initialize Status<BEV> for normal exception vectors
  ##################################################################
  mfc0    $8,$12
  and     $8,$8,0xffbfffff        # Clear BEV
  mtc0    $8,$12

  ##################################################################
  # Call main. We do this via a thunk in the text section so that
  # a normal jump and link can be used, enabling the startup code
  # to work properly whether main is written in MIPS16 or MIPS32
  # code. I.e., the linker will correctly adjust the JAL to JALX if
  # necessary
  ##################################################################
  and     $4,$4,0
  and     $5,$5,0
  la      $8,_main_entry
  jr      $8
  nop

.end _startup

.text

.ent _main_entry

_main_entry:
  ##################################################################
  # Call main
  ##################################################################
  jal main
  nop

.end _main_entry
