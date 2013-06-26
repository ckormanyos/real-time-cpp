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
        asm volatile("mrs r0, cpsr");
        asm volatile("bic r0, #0x80");
        asm volatile("msr cpsr, r0");
      }

      inline void disable_all()
      {
        // Disable all IRQ.
        asm volatile("mrs r0, cpsr");
        asm volatile("orr r0, #0x80");
        asm volatile("msr cpsr, r0");
      }

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

        const number_type     number;
        const priority_type   priority;
        const routing_type    routing;

        interrupt_descriptor(const number_type   num,
                             const priority_type prio,
                             const routing_type  route) : number  (num),
                                                          priority(prio),
                                                          routing (route) { }

        static constexpr std::size_t isr_id_emuint             =   0U;
        static constexpr std::size_t isr_id_commtx             =   1U;
        static constexpr std::size_t isr_id_commrx             =   2U;
        static constexpr std::size_t isr_id_bench              =   3U;
        static constexpr std::size_t isr_id_elm_irq            =   4U;
        static constexpr std::size_t isr_id_ssm_wfi_irq        =   5U;
        static constexpr std::size_t isr_id_ssm_irq            =   6U;
        static constexpr std::size_t isr_id_nmi                =   7U;
        static constexpr std::size_t isr_id_sec_evnt           =   8U;
        static constexpr std::size_t isr_id_l3debug            =   9U;
        static constexpr std::size_t isr_id_l3appint           =  10U;
        static constexpr std::size_t isr_id_prcmint            =  11U;
        static constexpr std::size_t isr_id_edmacompint        =  12U;
        static constexpr std::size_t isr_id_edmamperr          =  13U;
        static constexpr std::size_t isr_id_edmaerrint         =  14U;
        static constexpr std::size_t isr_id_wdt0int            =  15U;
        static constexpr std::size_t isr_id_adc_tsc_genint     =  16U;
        static constexpr std::size_t isr_id_usbssint           =  17U;
        static constexpr std::size_t isr_id_usb0               =  18U;
        static constexpr std::size_t isr_id_usb1               =  19U;
        static constexpr std::size_t isr_id_pruss1_evtout0     =  20U;
        static constexpr std::size_t isr_id_pruss1_evtout1     =  21U;
        static constexpr std::size_t isr_id_pruss1_evtout2     =  22U;
        static constexpr std::size_t isr_id_pruss1_evtout3     =  23U;
        static constexpr std::size_t isr_id_pruss1_evtout4     =  24U;
        static constexpr std::size_t isr_id_pruss1_evtout5     =  25U;
        static constexpr std::size_t isr_id_pruss1_evtout6     =  26U;
        static constexpr std::size_t isr_id_pruss1_evtout7     =  27U;
        static constexpr std::size_t isr_id_mmcsd1int          =  28U;
        static constexpr std::size_t isr_id_mmcsd2int          =  29U;
        static constexpr std::size_t isr_id_i2c2int            =  30U;
        static constexpr std::size_t isr_id_ecap0int           =  31U;
        static constexpr std::size_t isr_id_gpioint2a          =  32U;
        static constexpr std::size_t isr_id_gpioint2b          =  33U;
        static constexpr std::size_t isr_id_usbwakeup          =  34U;
        static constexpr std::size_t isr_id_lcdcint            =  36U;
        static constexpr std::size_t isr_id_gfxint             =  37U;
        static constexpr std::size_t isr_id_2dhwaint           =  38U;
        static constexpr std::size_t isr_id_epwm2int           =  39U;
        static constexpr std::size_t isr_id_3pgswrxthr0        =  40U;
        static constexpr std::size_t isr_id_3pgswrxint0        =  41U;
        static constexpr std::size_t isr_id_3pgswtxint0        =  42U;
        static constexpr std::size_t isr_id_3pgswmisc0         =  43U;
        static constexpr std::size_t isr_id_uart3int           =  44U;
        static constexpr std::size_t isr_id_uart4int           =  45U;
        static constexpr std::size_t isr_id_uart5int           =  46U;
        static constexpr std::size_t isr_id_ecap1int           =  47U;
        static constexpr std::size_t isr_id_dcan0_int0         =  52U;
        static constexpr std::size_t isr_id_dcan0_int1         =  53U;
        static constexpr std::size_t isr_id_dcan0_parity       =  54U;
        static constexpr std::size_t isr_id_dcan1_int0         =  55U;
        static constexpr std::size_t isr_id_dcan1_int1         =  56U;
        static constexpr std::size_t isr_id_dcan1_parity       =  57U;
        static constexpr std::size_t isr_id_epwm0_tzint        =  58U;
        static constexpr std::size_t isr_id_epwm1_tzint        =  59U;
        static constexpr std::size_t isr_id_epwm2_tzint        =  60U;
        static constexpr std::size_t isr_id_ecap2int           =  61U;
        static constexpr std::size_t isr_id_gpioint3a          =  62U;
        static constexpr std::size_t isr_id_gpioint3b          =  63U;
        static constexpr std::size_t isr_id_mmcsd0int          =  64U;
        static constexpr std::size_t isr_id_spi0int            =  65U;
        static constexpr std::size_t isr_id_tint0              =  66U;
        static constexpr std::size_t isr_id_tint1_1ms          =  67U;
        static constexpr std::size_t isr_id_tint2              =  68U;
        static constexpr std::size_t isr_id_tint3              =  69U;
        static constexpr std::size_t isr_id_i2c0int            =  70U;
        static constexpr std::size_t isr_id_i2c1int            =  71U;
        static constexpr std::size_t isr_id_uart0int           =  72U;
        static constexpr std::size_t isr_id_uart1int           =  73U;
        static constexpr std::size_t isr_id_uart2int           =  74U;
        static constexpr std::size_t isr_id_rtcint             =  75U;
        static constexpr std::size_t isr_id_rtcalarmint        =  76U;
        static constexpr std::size_t isr_id_mbint0             =  77U;
        static constexpr std::size_t isr_id_m3_txev            =  78U;
        static constexpr std::size_t isr_id_eqep0int           =  79U;
        static constexpr std::size_t isr_id_mcatxint0          =  80U;
        static constexpr std::size_t isr_id_mcarxint0          =  81U;
        static constexpr std::size_t isr_id_mcatxint1          =  82U;
        static constexpr std::size_t isr_id_mcarxint1          =  83U;
        static constexpr std::size_t isr_id_epwm0int           =  86U;
        static constexpr std::size_t isr_id_epwm1int           =  87U;
        static constexpr std::size_t isr_id_eqep1int           =  88U;
        static constexpr std::size_t isr_id_eqep2int           =  89U;
        static constexpr std::size_t isr_id_dma_intr_pin2      =  90U;
        static constexpr std::size_t isr_id_wdt1int            =  91U;
        static constexpr std::size_t isr_id_tint4              =  92U;
        static constexpr std::size_t isr_id_tint5              =  93U;
        static constexpr std::size_t isr_id_tint6              =  94U;
        static constexpr std::size_t isr_id_tint7              =  95U;
        static constexpr std::size_t isr_id_gpioint0a          =  96U;
        static constexpr std::size_t isr_id_gpioint0b          =  97U;
        static constexpr std::size_t isr_id_gpioint1a          =  98U;
        static constexpr std::size_t isr_id_gpioint1b          =  99U;
        static constexpr std::size_t isr_id_gpmcint            = 100U;
        static constexpr std::size_t isr_id_ddrerr0            = 101U;
        static constexpr std::size_t isr_id_aes0_irq_s         = 102U;
        static constexpr std::size_t isr_id_aes0_irq_p         = 103U;
        static constexpr std::size_t isr_id_sha_irq_s          = 108U;
        static constexpr std::size_t isr_id_sha_irq_p          = 109U;
        static constexpr std::size_t isr_id_fpka_sintrequest_s = 110U;
        static constexpr std::size_t isr_id_rng_irq            = 111U;
        static constexpr std::size_t isr_id_tcerrint0          = 112U;
        static constexpr std::size_t isr_id_tcerrint1          = 113U;
        static constexpr std::size_t isr_id_tcerrint2          = 114U;
        static constexpr std::size_t isr_id_smrflx_sabertooth  = 120U;
        static constexpr std::size_t isr_id_smrflx_core        = 121U;
        static constexpr std::size_t isr_id_dma_intr_pin0      = 123U;
        static constexpr std::size_t isr_id_dma_intr_pin1      = 124U;
        static constexpr std::size_t isr_id_spi1int            = 125U;

        static constexpr std::size_t number_of_interrupts         = 128U;
      };

      void register_interrupt(const interrupt_descriptor& isr_descriptor);
    }
  }

#endif // _MCAL_IRQ_2010_04_10_H_
