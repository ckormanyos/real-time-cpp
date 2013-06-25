///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_IRQ_2010_04_10_H_
  #define _MCAL_IRQ_2010_04_10_H_

  #include <cstdint>
  #include <cstddef>

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;

      void init(const config_type*);

      inline void enable_all()
      {
        // Enable all IRQ.
        asm volatile("mrs r0, CPSR");
        asm volatile("bic r0, #0x80");
        asm volatile("msr CPSR, r0");
      }

      inline void disable_all()
      {
        // Disable all IRQ.
        asm volatile("mrs r0, CPSR");
        asm volatile("orr r0, #0x80");
        asm volatile("msr CPSR, r0");
      }

      extern "C" typedef void(*isr_handler_type)();

      struct interrupt_descriptor
      {
        typedef enum enum_routing_type
        {
          route_to_irq,
          route_to_fiq
        }
        routing_type;

        typedef std::uint32_t priority_type;
        typedef std::size_t   number_type;

        const priority_type    priority;
        const number_type      number;
        const routing_type     routing;

        interrupt_descriptor(const priority_type    prio,
                             const number_type      num,
                             const routing_type     route) : priority(prio),
                                                             number  (num),
                                                             routing (route) { }

        static constexpr std::uint32_t isr_id_emuint             =   0UL;
        static constexpr std::uint32_t isr_id_commtx             =   1UL;
        static constexpr std::uint32_t isr_id_commrx             =   2UL;
        static constexpr std::uint32_t isr_id_bench              =   3UL;
        static constexpr std::uint32_t isr_id_elm_irq            =   4UL;
        static constexpr std::uint32_t isr_id_ssm_wfi_irq        =   5UL;
        static constexpr std::uint32_t isr_id_ssm_irq            =   6UL;
        static constexpr std::uint32_t isr_id_nmi                =   7UL;
        static constexpr std::uint32_t isr_id_sec_evnt           =   8UL;
        static constexpr std::uint32_t isr_id_l3debug            =   9UL;
        static constexpr std::uint32_t isr_id_l3appint           =  10UL;
        static constexpr std::uint32_t isr_id_prcmint            =  11UL;
        static constexpr std::uint32_t isr_id_edmacompint        =  12UL;
        static constexpr std::uint32_t isr_id_edmamperr          =  13UL;
        static constexpr std::uint32_t isr_id_edmaerrint         =  14UL;
        static constexpr std::uint32_t isr_id_wdt0int            =  15UL;
        static constexpr std::uint32_t isr_id_adc_tsc_genint     =  16UL;
        static constexpr std::uint32_t isr_id_usbssint           =  17UL;
        static constexpr std::uint32_t isr_id_usb0               =  18UL;
        static constexpr std::uint32_t isr_id_usb1               =  19UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout0     =  20UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout1     =  21UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout2     =  22UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout3     =  23UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout4     =  24UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout5     =  25UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout6     =  26UL;
        static constexpr std::uint32_t isr_id_pruss1_evtout7     =  27UL;
        static constexpr std::uint32_t isr_id_mmcsd1int          =  28UL;
        static constexpr std::uint32_t isr_id_mmcsd2int          =  29UL;
        static constexpr std::uint32_t isr_id_i2c2int            =  30UL;
        static constexpr std::uint32_t isr_id_ecap0int           =  31UL;
        static constexpr std::uint32_t isr_id_gpioint2a          =  32UL;
        static constexpr std::uint32_t isr_id_gpioint2b          =  33UL;
        static constexpr std::uint32_t isr_id_usbwakeup          =  34UL;
        static constexpr std::uint32_t isr_id_lcdcint            =  36UL;
        static constexpr std::uint32_t isr_id_gfxint             =  37UL;
        static constexpr std::uint32_t isr_id_2dhwaint           =  38UL;
        static constexpr std::uint32_t isr_id_epwm2int           =  39UL;
        static constexpr std::uint32_t isr_id_3pgswrxthr0        =  40UL;
        static constexpr std::uint32_t isr_id_3pgswrxint0        =  41UL;
        static constexpr std::uint32_t isr_id_3pgswtxint0        =  42UL;
        static constexpr std::uint32_t isr_id_3pgswmisc0         =  43UL;
        static constexpr std::uint32_t isr_id_uart3int           =  44UL;
        static constexpr std::uint32_t isr_id_uart4int           =  45UL;
        static constexpr std::uint32_t isr_id_uart5int           =  46UL;
        static constexpr std::uint32_t isr_id_ecap1int           =  47UL;
        static constexpr std::uint32_t isr_id_dcan0_int0         =  52UL;
        static constexpr std::uint32_t isr_id_dcan0_int1         =  53UL;
        static constexpr std::uint32_t isr_id_dcan0_parity       =  54UL;
        static constexpr std::uint32_t isr_id_dcan1_int0         =  55UL;
        static constexpr std::uint32_t isr_id_dcan1_int1         =  56UL;
        static constexpr std::uint32_t isr_id_dcan1_parity       =  57UL;
        static constexpr std::uint32_t isr_id_epwm0_tzint        =  58UL;
        static constexpr std::uint32_t isr_id_epwm1_tzint        =  59UL;
        static constexpr std::uint32_t isr_id_epwm2_tzint        =  60UL;
        static constexpr std::uint32_t isr_id_ecap2int           =  61UL;
        static constexpr std::uint32_t isr_id_gpioint3a          =  62UL;
        static constexpr std::uint32_t isr_id_gpioint3b          =  63UL;
        static constexpr std::uint32_t isr_id_mmcsd0int          =  64UL;
        static constexpr std::uint32_t isr_id_spi0int            =  65UL;
        static constexpr std::uint32_t isr_id_tint0              =  66UL;
        static constexpr std::uint32_t isr_id_tint1_1ms          =  67UL;
        static constexpr std::uint32_t isr_id_tint2              =  68UL;
        static constexpr std::uint32_t isr_id_tint3              =  69UL;
        static constexpr std::uint32_t isr_id_i2c0int            =  70UL;
        static constexpr std::uint32_t isr_id_i2c1int            =  71UL;
        static constexpr std::uint32_t isr_id_uart0int           =  72UL;
        static constexpr std::uint32_t isr_id_uart1int           =  73UL;
        static constexpr std::uint32_t isr_id_uart2int           =  74UL;
        static constexpr std::uint32_t isr_id_rtcint             =  75UL;
        static constexpr std::uint32_t isr_id_rtcalarmint        =  76UL;
        static constexpr std::uint32_t isr_id_mbint0             =  77UL;
        static constexpr std::uint32_t isr_id_m3_txev            =  78UL;
        static constexpr std::uint32_t isr_id_eqep0int           =  79UL;
        static constexpr std::uint32_t isr_id_mcatxint0          =  80UL;
        static constexpr std::uint32_t isr_id_mcarxint0          =  81UL;
        static constexpr std::uint32_t isr_id_mcatxint1          =  82UL;
        static constexpr std::uint32_t isr_id_mcarxint1          =  83UL;
        static constexpr std::uint32_t isr_id_epwm0int           =  86UL;
        static constexpr std::uint32_t isr_id_epwm1int           =  87UL;
        static constexpr std::uint32_t isr_id_eqep1int           =  88UL;
        static constexpr std::uint32_t isr_id_eqep2int           =  89UL;
        static constexpr std::uint32_t isr_id_dma_intr_pin2      =  90UL;
        static constexpr std::uint32_t isr_id_wdt1int            =  91UL;
        static constexpr std::uint32_t isr_id_tint4              =  92UL;
        static constexpr std::uint32_t isr_id_tint5              =  93UL;
        static constexpr std::uint32_t isr_id_tint6              =  94UL;
        static constexpr std::uint32_t isr_id_tint7              =  95UL;
        static constexpr std::uint32_t isr_id_gpioint0a          =  96UL;
        static constexpr std::uint32_t isr_id_gpioint0b          =  97UL;
        static constexpr std::uint32_t isr_id_gpioint1a          =  98UL;
        static constexpr std::uint32_t isr_id_gpioint1b          =  99UL;
        static constexpr std::uint32_t isr_id_gpmcint            = 100UL;
        static constexpr std::uint32_t isr_id_ddrerr0            = 101UL;
        static constexpr std::uint32_t isr_id_aes0_irq_s         = 102UL;
        static constexpr std::uint32_t isr_id_aes0_irq_p         = 103UL;
        static constexpr std::uint32_t isr_id_sha_irq_s          = 108UL;
        static constexpr std::uint32_t isr_id_sha_irq_p          = 109UL;
        static constexpr std::uint32_t isr_id_fpka_sintrequest_s = 110UL;
        static constexpr std::uint32_t isr_id_rng_irq            = 111UL;
        static constexpr std::uint32_t isr_id_tcerrint0          = 112UL;
        static constexpr std::uint32_t isr_id_tcerrint1          = 113UL;
        static constexpr std::uint32_t isr_id_tcerrint2          = 114UL;
        static constexpr std::uint32_t isr_id_smrflx_sabertooth  = 120UL;
        static constexpr std::uint32_t isr_id_smrflx_core        = 121UL;
        static constexpr std::uint32_t isr_id_dma_intr_pin0      = 123UL;
        static constexpr std::uint32_t isr_id_dma_intr_pin1      = 124UL;
        static constexpr std::uint32_t isr_id_spi1int            = 125UL;

        static constexpr std::size_t number_of_interrupts         = 128U;
      };

      void register_interrupt(const interrupt_descriptor& isr_descriptor);
    }
  }

#endif // _MCAL_IRQ_2010_04_10_H_
