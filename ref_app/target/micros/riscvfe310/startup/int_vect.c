///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

/******************************************************************************************************
  Filename    : intvect.c

  Core        : RV32IMAC

  MCU         : FE310-G002 (SiFive)

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 04.06.2021

  Description : Interrupt vector table implementation

******************************************************************************************************/

__asm(".option arch, +zicsr");

#include <stdint.h>

typedef void (*InterruptHandler)();

static void UndefinedHandler();
void DirectModeInterruptHandler() __attribute__ ((interrupt ("machine")));
void Isr_MachineExternalInterrupt();

void Isr_InstructionAddressMisaligned () __attribute__((weak, alias("UndefinedHandler")));
void Isr_InstructionAccessFault       () __attribute__((weak, alias("UndefinedHandler")));
void Isr_IllegalInstruction           () __attribute__((weak, alias("UndefinedHandler")));
void Isr_Breakpoint                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAddressMisaligned        () __attribute__((weak, alias("UndefinedHandler")));
void Isr_LoadAccessFault              () __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAddressMisaligned       () __attribute__((weak, alias("UndefinedHandler")));
void Isr_StoreAccessFault             () __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromUmode     () __attribute__((weak, alias("UndefinedHandler")));
void Isr_EnvironmentCallFromMmode     () __attribute__((weak, alias("UndefinedHandler")));
void Isr_MachineSoftwareInterrupt     () __attribute__((weak, alias("UndefinedHandler")));
void Isr_MachineTimerInterrupt        () __attribute__((weak, alias("UndefinedHandler")));
void Isr_WATCHDOG_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_RTC_IRQn                     () __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART0_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_UART1_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_QSPI0_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_QSPI1_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_QSPI2_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO0_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO1_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO2_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO3_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO4_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO5_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO6_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO7_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO8_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO9_IRQn                   () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO10_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO11_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO12_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO13_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO14_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO15_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO16_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO17_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO18_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO19_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO20_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO21_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO22_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO23_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO24_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO25_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO26_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO27_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO28_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO29_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO30_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_GPIO31_IRQn                  () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM0CMP0_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM0CMP1_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM0CMP2_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM0CMP3_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM1CMP0_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM1CMP1_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM1CMP2_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM1CMP3_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM2CMP0_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM2CMP1_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM2CMP2_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_PWM2CMP3_IRQn                () __attribute__((weak, alias("UndefinedHandler")));
void Isr_I2C0_IRQn                    () __attribute__((weak, alias("UndefinedHandler")));

#if __riscv_xlen==32
typedef uint32_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint32_t uint_csr64_t;
#elif __riscv_xlen==64
typedef uint64_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint64_t uint_csr64_t;
#else
#error "Unknown XLEN"
#endif

static inline uint_xlen_t csr_read_mcause()
{
  uint_xlen_t value;

  __asm volatile ("csrr    %0, mcause" 
                  : "=r" (value)  /* output : register */
                  : /* input : none */
                  : /* clobbers: none */);

  return value;
}

//=====================================================================================================
// Platform-Level Interrupts vector table
//=====================================================================================================
const InterruptHandler __attribute__((section(".intvect"), aligned(4), used)) PLIVT[] =
{
    (InterruptHandler)&Isr_WATCHDOG_IRQn,   /* IRQ 01  WATCHDOG  */
    (InterruptHandler)&Isr_RTC_IRQn,        /* IRQ 02  RTC       */
    (InterruptHandler)&Isr_UART0_IRQn,      /* IRQ 03  UART0     */
    (InterruptHandler)&Isr_UART1_IRQn,      /* IRQ 04  UART1     */
    (InterruptHandler)&Isr_QSPI0_IRQn,      /* IRQ 05  QSPI0     */
    (InterruptHandler)&Isr_QSPI1_IRQn,      /* IRQ 06  QSPI1     */
    (InterruptHandler)&Isr_QSPI2_IRQn,      /* IRQ 07  QSPI2     */
    (InterruptHandler)&Isr_GPIO0_IRQn,      /* IRQ 08  GPIO0     */
    (InterruptHandler)&Isr_GPIO1_IRQn,      /* IRQ 09  GPIO1     */
    (InterruptHandler)&Isr_GPIO2_IRQn,      /* IRQ 10  GPIO2     */
    (InterruptHandler)&Isr_GPIO3_IRQn,      /* IRQ 11  GPIO3     */
    (InterruptHandler)&Isr_GPIO4_IRQn,      /* IRQ 12  GPIO4     */
    (InterruptHandler)&Isr_GPIO5_IRQn,      /* IRQ 13  GPIO5     */
    (InterruptHandler)&Isr_GPIO6_IRQn,      /* IRQ 14  GPIO6     */
    (InterruptHandler)&Isr_GPIO7_IRQn,      /* IRQ 15  GPIO7     */
    (InterruptHandler)&Isr_GPIO8_IRQn,      /* IRQ 16  GPIO8     */
    (InterruptHandler)&Isr_GPIO9_IRQn,      /* IRQ 17  GPIO9     */
    (InterruptHandler)&Isr_GPIO10_IRQn,     /* IRQ 18  GPIO10    */
    (InterruptHandler)&Isr_GPIO11_IRQn,     /* IRQ 19  GPIO11    */
    (InterruptHandler)&Isr_GPIO12_IRQn,     /* IRQ 20  GPIO12    */
    (InterruptHandler)&Isr_GPIO13_IRQn,     /* IRQ 21  GPIO13    */
    (InterruptHandler)&Isr_GPIO14_IRQn,     /* IRQ 22  GPIO14    */
    (InterruptHandler)&Isr_GPIO15_IRQn,     /* IRQ 23  GPIO15    */
    (InterruptHandler)&Isr_GPIO16_IRQn,     /* IRQ 24  GPIO16    */
    (InterruptHandler)&Isr_GPIO17_IRQn,     /* IRQ 25  GPIO17    */
    (InterruptHandler)&Isr_GPIO18_IRQn,     /* IRQ 26  GPIO18    */
    (InterruptHandler)&Isr_GPIO19_IRQn,     /* IRQ 27  GPIO19    */
    (InterruptHandler)&Isr_GPIO20_IRQn,     /* IRQ 28  GPIO20    */
    (InterruptHandler)&Isr_GPIO21_IRQn,     /* IRQ 29  GPIO21    */
    (InterruptHandler)&Isr_GPIO22_IRQn,     /* IRQ 30  GPIO22    */
    (InterruptHandler)&Isr_GPIO23_IRQn,     /* IRQ 31  GPIO23    */
    (InterruptHandler)&Isr_GPIO24_IRQn,     /* IRQ 32  GPIO24    */
    (InterruptHandler)&Isr_GPIO25_IRQn,     /* IRQ 33  GPIO25    */
    (InterruptHandler)&Isr_GPIO26_IRQn,     /* IRQ 34  GPIO26    */
    (InterruptHandler)&Isr_GPIO27_IRQn,     /* IRQ 35  GPIO27    */
    (InterruptHandler)&Isr_GPIO28_IRQn,     /* IRQ 36  GPIO28    */
    (InterruptHandler)&Isr_GPIO29_IRQn,     /* IRQ 37  GPIO29    */
    (InterruptHandler)&Isr_GPIO30_IRQn,     /* IRQ 38  GPIO30    */
    (InterruptHandler)&Isr_GPIO31_IRQn,     /* IRQ 39  GPIO31    */
    (InterruptHandler)&Isr_PWM0CMP0_IRQn,   /* IRQ 40  PWM0CMP0  */
    (InterruptHandler)&Isr_PWM0CMP1_IRQn,   /* IRQ 41  PWM0CMP1  */
    (InterruptHandler)&Isr_PWM0CMP2_IRQn,   /* IRQ 42  PWM0CMP2  */
    (InterruptHandler)&Isr_PWM0CMP3_IRQn,   /* IRQ 43  PWM0CMP3  */
    (InterruptHandler)&Isr_PWM1CMP0_IRQn,   /* IRQ 44  PWM1CMP0  */
    (InterruptHandler)&Isr_PWM1CMP1_IRQn,   /* IRQ 45  PWM1CMP1  */
    (InterruptHandler)&Isr_PWM1CMP2_IRQn,   /* IRQ 46  PWM1CMP2  */
    (InterruptHandler)&Isr_PWM1CMP3_IRQn,   /* IRQ 47  PWM1CMP3  */
    (InterruptHandler)&Isr_PWM2CMP0_IRQn,   /* IRQ 48  PWM2CMP0  */
    (InterruptHandler)&Isr_PWM2CMP1_IRQn,   /* IRQ 49  PWM2CMP1  */
    (InterruptHandler)&Isr_PWM2CMP2_IRQn,   /* IRQ 50  PWM2CMP2  */
    (InterruptHandler)&Isr_PWM2CMP3_IRQn,   /* IRQ 51  PWM2CMP3  */
    (InterruptHandler)&Isr_I2C0_IRQn        /* IRQ 52  I2C0      */
};

//=====================================================================================================
// Interrupt vector table
//=====================================================================================================
const InterruptHandler __attribute__((section(".intvect"), aligned(64), used)) IVT[] =
{
    /* Core-Local Exceptions */
    (InterruptHandler)&Isr_InstructionAddressMisaligned,  /* 0  - Instruction address misaligned */
    (InterruptHandler)&Isr_InstructionAccessFault,        /* 1  - Instruction access fault       */
    (InterruptHandler)&Isr_IllegalInstruction,            /* 2  - Illegal instruction            */
    (InterruptHandler)&Isr_Breakpoint,                    /* 3  - Breakpoint                     */
    (InterruptHandler)&Isr_LoadAddressMisaligned,         /* 4  - Load address misaligned        */
    (InterruptHandler)&Isr_LoadAccessFault,               /* 5  - Load access fault              */
    (InterruptHandler)&Isr_StoreAddressMisaligned,        /* 6  - Store/AMO address misaligned   */
    (InterruptHandler)&Isr_StoreAccessFault,              /* 7  - Store/AMO access fault         */
    (InterruptHandler)&Isr_EnvironmentCallFromUmode,      /* 8  - Environment call from U-mode   */
    (InterruptHandler)&UndefinedHandler,                  /* 9  - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 10 - Reserved                       */
    (InterruptHandler)&Isr_EnvironmentCallFromMmode,      /* 11 - Environment call from M-mode   */
    /* Core-Local Interrupts */
    (InterruptHandler)&UndefinedHandler,                  /* 12 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 13 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 14 - Reserved                       */
    (InterruptHandler)&Isr_MachineSoftwareInterrupt,      /* 15 - Machine software interrupt     */
    (InterruptHandler)&UndefinedHandler,                  /* 16 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 17 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 18 - Reserved                       */
    (InterruptHandler)&Isr_MachineTimerInterrupt,         /* 19 - Machine timer interrupt        */
    (InterruptHandler)&UndefinedHandler,                  /* 20 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 21 - Reserved                       */
    (InterruptHandler)&UndefinedHandler,                  /* 22 - Reserved                       */
    /* Platform-Level Interrupts */
    (InterruptHandler)&Isr_MachineExternalInterrupt       /* 23 - Machine external interrupt     */
};

//=====================================================================================================
// Implementation
//=====================================================================================================

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UndefinedHandler()
{
  for(;;);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void DirectModeInterruptHandler()
{
  /* get the exception cause number */
  const uint32_t mcause = csr_read_mcause();
  const uint32_t idx    = (mcause & ((1UL<< 10u) - 1u)) + 12 * (mcause >> 31u);

  if(idx < 24u)
  {
    /* call the appropriate interrupt service routine */
    IVT[idx]();
  }

}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void Isr_MachineExternalInterrupt()
{
  /* get the PLIC pending interrupt ID */
  #define PLIC_BASE  UINT32_C(0x0C000000)
  #define PLIC_CLAIM (uint32_t) (PLIC_BASE + UINT32_C(0x00200004))

  //const uint32_t IntId = mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::plic_claim>::reg_get();
  const uint32_t IntId = *(volatile uint32_t*) PLIC_CLAIM;

  if(IntId < 52u)
  {
    /* call the appropriate interrupt service routine */
    PLIVT[IntId]();
  }

  /* set the interrupt as completed */
  //mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::plic_claim, IntId);
  *(volatile uint32_t*) PLIC_CLAIM = IntId;
}
