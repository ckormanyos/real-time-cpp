///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <cstddef>
#include <array>
#include <algorithm>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <am335x_hw_regs.h>
#include <bfx.h>

namespace
{
  typedef std::uint32_t Int_PriorityType;
  typedef std::uint32_t Int_IntNumberType;

  typedef enum enum_Int_FIQnIRQType
  {
    INT_ROUTE_IRQ,     // route to IRQ
    INT_ROUTE_FIQ,     // route to FIQ
  }
  Int_FIQnIRQType;

  constexpr std::uint32_t SYS_INT_EMUINT             =   0UL;
  constexpr std::uint32_t SYS_INT_COMMTX             =   1UL;
  constexpr std::uint32_t SYS_INT_COMMRX             =   2UL;
  constexpr std::uint32_t SYS_INT_BENCH              =   3UL;
  constexpr std::uint32_t SYS_INT_ELM_IRQ            =   4UL;
  constexpr std::uint32_t SYS_INT_SSM_WFI_IRQ        =   5UL;
  constexpr std::uint32_t SYS_INT_SSM_IRQ            =   6UL;
  constexpr std::uint32_t SYS_INT_NMI                =   7UL;
  constexpr std::uint32_t SYS_INT_SEC_EVNT           =   8UL;
  constexpr std::uint32_t SYS_INT_L3DEBUG            =   9UL;
  constexpr std::uint32_t SYS_INT_L3APPINT           =  10UL;
  constexpr std::uint32_t SYS_INT_PRCMINT            =  11UL;
  constexpr std::uint32_t SYS_INT_EDMACOMPINT        =  12UL;
  constexpr std::uint32_t SYS_INT_EDMAMPERR          =  13UL;
  constexpr std::uint32_t SYS_INT_EDMAERRINT         =  14UL;
  constexpr std::uint32_t SYS_INT_WDT0INT            =  15UL;
  constexpr std::uint32_t SYS_INT_ADC_TSC_GENINT     =  16UL;
  constexpr std::uint32_t SYS_INT_USBSSINT           =  17UL;
  constexpr std::uint32_t SYS_INT_USB0               =  18UL;
  constexpr std::uint32_t SYS_INT_USB1               =  19UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT0     =  20UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT1     =  21UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT2     =  22UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT3     =  23UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT4     =  24UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT5     =  25UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT6     =  26UL;
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT7     =  27UL;
  constexpr std::uint32_t SYS_INT_MMCSD1INT          =  28UL;
  constexpr std::uint32_t SYS_INT_MMCSD2INT          =  29UL;
  constexpr std::uint32_t SYS_INT_I2C2INT            =  30UL;
  constexpr std::uint32_t SYS_INT_eCAP0INT           =  31UL;
  constexpr std::uint32_t SYS_INT_GPIOINT2A          =  32UL;
  constexpr std::uint32_t SYS_INT_GPIOINT2B          =  33UL;
  constexpr std::uint32_t SYS_INT_USBWAKEUP          =  34UL;
  constexpr std::uint32_t SYS_INT_LCDCINT            =  36UL;
  constexpr std::uint32_t SYS_INT_GFXINT             =  37UL;
  constexpr std::uint32_t SYS_INT_2DHWAINT           =  38UL;
  constexpr std::uint32_t SYS_INT_ePWM2INT           =  39UL;
  constexpr std::uint32_t SYS_INT_3PGSWRXTHR0        =  40UL;
  constexpr std::uint32_t SYS_INT_3PGSWRXINT0        =  41UL;
  constexpr std::uint32_t SYS_INT_3PGSWTXINT0        =  42UL;
  constexpr std::uint32_t SYS_INT_3PGSWMISC0         =  43UL;
  constexpr std::uint32_t SYS_INT_UART3INT           =  44UL;
  constexpr std::uint32_t SYS_INT_UART4INT           =  45UL;
  constexpr std::uint32_t SYS_INT_UART5INT           =  46UL;
  constexpr std::uint32_t SYS_INT_eCAP1INT           =  47UL;
  constexpr std::uint32_t SYS_INT_DCAN0_INT0         =  52UL;
  constexpr std::uint32_t SYS_INT_DCAN0_INT1         =  53UL;
  constexpr std::uint32_t SYS_INT_DCAN0_PARITY       =  54UL;
  constexpr std::uint32_t SYS_INT_DCAN1_INT0         =  55UL;
  constexpr std::uint32_t SYS_INT_DCAN1_INT1         =  56UL;
  constexpr std::uint32_t SYS_INT_DCAN1_PARITY       =  57UL;
  constexpr std::uint32_t SYS_INT_ePWM0_TZINT        =  58UL;
  constexpr std::uint32_t SYS_INT_ePWM1_TZINT        =  59UL;
  constexpr std::uint32_t SYS_INT_ePWM2_TZINT        =  60UL;
  constexpr std::uint32_t SYS_INT_eCAP2INT           =  61UL;
  constexpr std::uint32_t SYS_INT_GPIOINT3A          =  62UL;
  constexpr std::uint32_t SYS_INT_GPIOINT3B          =  63UL;
  constexpr std::uint32_t SYS_INT_MMCSD0INT          =  64UL;
  constexpr std::uint32_t SYS_INT_SPI0INT            =  65UL;
  constexpr std::uint32_t SYS_INT_TINT0              =  66UL;
  constexpr std::uint32_t SYS_INT_TINT1_1MS          =  67UL;
  constexpr std::uint32_t SYS_INT_TINT2              =  68UL;
  constexpr std::uint32_t SYS_INT_TINT3              =  69UL;
  constexpr std::uint32_t SYS_INT_I2C0INT            =  70UL;
  constexpr std::uint32_t SYS_INT_I2C1INT            =  71UL;
  constexpr std::uint32_t SYS_INT_UART0INT           =  72UL;
  constexpr std::uint32_t SYS_INT_UART1INT           =  73UL;
  constexpr std::uint32_t SYS_INT_UART2INT           =  74UL;
  constexpr std::uint32_t SYS_INT_RTCINT             =  75UL;
  constexpr std::uint32_t SYS_INT_RTCALARMINT        =  76UL;
  constexpr std::uint32_t SYS_INT_MBINT0             =  77UL;
  constexpr std::uint32_t SYS_INT_M3_TXEV            =  78UL;
  constexpr std::uint32_t SYS_INT_eQEP0INT           =  79UL;
  constexpr std::uint32_t SYS_INT_MCATXINT0          =  80UL;
  constexpr std::uint32_t SYS_INT_MCARXINT0          =  81UL;
  constexpr std::uint32_t SYS_INT_MCATXINT1          =  82UL;
  constexpr std::uint32_t SYS_INT_MCARXINT1          =  83UL;
  constexpr std::uint32_t SYS_INT_ePWM0INT           =  86UL;
  constexpr std::uint32_t SYS_INT_ePWM1INT           =  87UL;
  constexpr std::uint32_t SYS_INT_eQEP1INT           =  88UL;
  constexpr std::uint32_t SYS_INT_eQEP2INT           =  89UL;
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN2      =  90UL;
  constexpr std::uint32_t SYS_INT_WDT1INT            =  91UL;
  constexpr std::uint32_t SYS_INT_TINT4              =  92UL;
  constexpr std::uint32_t SYS_INT_TINT5              =  93UL;
  constexpr std::uint32_t SYS_INT_TINT6              =  94UL;
  constexpr std::uint32_t SYS_INT_TINT7              =  95UL;
  constexpr std::uint32_t SYS_INT_GPIOINT0A          =  96UL;
  constexpr std::uint32_t SYS_INT_GPIOINT0B          =  97UL;
  constexpr std::uint32_t SYS_INT_GPIOINT1A          =  98UL;
  constexpr std::uint32_t SYS_INT_GPIOINT1B          =  99UL;
  constexpr std::uint32_t SYS_INT_GPMCINT            = 100UL;
  constexpr std::uint32_t SYS_INT_DDRERR0            = 101UL;
  constexpr std::uint32_t SYS_INT_AES0_IRQ_S         = 102UL;
  constexpr std::uint32_t SYS_INT_AES0_IRQ_P         = 103UL;
  constexpr std::uint32_t SYS_INT_SHA_IRQ_S          = 108UL;
  constexpr std::uint32_t SYS_INT_SHA_IRQ_P          = 109UL;
  constexpr std::uint32_t SYS_INT_FPKA_SINTREQUEST_S = 110UL;
  constexpr std::uint32_t SYS_INT_RNG_IRQ            = 111UL;
  constexpr std::uint32_t SYS_INT_TCERRINT0          = 112UL;
  constexpr std::uint32_t SYS_INT_TCERRINT1          = 113UL;
  constexpr std::uint32_t SYS_INT_TCERRINT2          = 114UL;
  constexpr std::uint32_t SYS_INT_SMRFLX_Sabertooth  = 120UL;
  constexpr std::uint32_t SYS_INT_SMRFLX_Core        = 121UL;
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN0      = 123UL;
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN1      = 124UL;
  constexpr std::uint32_t SYS_INT_SPI1INT            = 125UL;

  constexpr std::size_t number_of_interrupts = 128U;
}

extern "C"
{
  void __vector_unused_irq() { for(;;) { ; } }

  typedef void(*isr_handler)();

  // Declare the RAM ISR vectors.
  volatile isr_handler isr_ram_vectors[number_of_interrupts];
}

namespace mcal
{
  namespace irq
  {
    void vector_base_address_set(const std::uint32_t addr);

    void register_interrupt(Int_IntNumberType intrNum,
                            isr_handler the_isr_handler,
                            Int_PriorityType priority,
                            Int_FIQnIRQType hostIntRoute);
  }
}

void mcal::irq::vector_base_address_set(const std::uint32_t addr)
{
  asm("mcr p15, #0, %[value], c12, c0, 0":: [value] "r" (addr));
}

void mcal::irq::register_interrupt(Int_IntNumberType intrNum,
                                   isr_handler the_isr_handler,
                                   Int_PriorityType priority,
                                   Int_FIQnIRQType hostIntRoute)
{
  if(intrNum < number_of_interrupts)
  {
    // Assign the ISR.
    isr_ram_vectors[intrNum] = the_isr_handler;

    INTC->ILR[intrNum] = ((priority << 2) & 0x01FCUL) | ((hostIntRoute == INT_ROUTE_IRQ) ? 0UL : 1UL);

    // Enable the system interrupt in the corresponding MIR_CLEAR register.
    INTC->REG[(intrNum >> 5U) & 3UL].MIR_CLEAR = (1UL << (intrNum & 0x01FUL));
  }
}

void mcal::irq::enable_all()
{
  // Enable IRQ in CPSR.
  mcal::cpu::irqe();
}

void mcal::irq::disable_all()
{
  mcal::cpu::irqd();
}

void mcal::irq::init(const config_type*)
{
  // Initialize all the RAM interrupt vectors.
  std::fill(isr_ram_vectors,
            isr_ram_vectors + number_of_interrupts,
            __vector_unused_irq);

  // Reset the ARM interrupt controller.
  INTC->SYSCONFIG = 2UL;

  // Wait for the reset to complete
  while(std::uint32_t(INTC->SYSSTATUS & 1U) != std::uint32_t(1UL)) { ; }

  // Enable any interrupt generation by setting priority threshold.
  INTC->THRESHOLD = 0xFFU;

  // Enable IRQ in CPSR.
  mcal::cpu::irqe();
}
