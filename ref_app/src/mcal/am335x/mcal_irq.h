///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2010_04_10_H_
  #define MCAL_IRQ_2010_04_10_H_

  #include <cstdint>
  #include <cstddef>

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;

      void init(const config_type*);

      inline void enable_all()
      {
        // Enable all maskable interrupts.
        asm volatile("mrs r0, cpsr");
        asm volatile("bic r0, #0x80");
        asm volatile("msr cpsr, r0");
      }

      inline void disable_all()
      {
        // Disable all maskable interrupts.
        asm volatile("mrs r0, cpsr");
        asm volatile("orr r0, #0x80");
        asm volatile("msr cpsr, r0");
      }

      struct interrupt_descriptor
      {
        typedef std::size_t   number_type;
        typedef std::uint32_t priority_type;

        typedef enum enum_routing_type
        {
          route_to_irq,
          route_to_fiq
        }
        routing_type;

        template<const number_type   isr_number,
                 const priority_type isr_priority,
                 const routing_type  isr_routing>
        static void register_interrupt()
        {
          static_assert(isr_number < number_of_interrupts,
                        "The registered ISR number exceeds the maximum allowed index!");

          // Set the interrupt priority level and the interrupt routing.
          constexpr std::uint32_t priority_bits     = std::uint32_t(std::uint32_t(isr_priority << UINT32_C(2)) & UINT32_C(0x01FC));
          constexpr std::uint32_t routing_bits      = std::uint32_t((isr_routing == route_to_irq) ? UINT32_C(0) : UINT32_C(1));
          constexpr std::uint32_t intc_ilr_reg_addr = std::uint32_t(  mcal::reg::intc::ilr_base_0x80
                                                                    + std::uint32_t(isr_number * UINT32_C(4)));

          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       intc_ilr_reg_addr,
                                       std::uint32_t(priority_bits | routing_bits)>::reg_set();

          // Enable the interrupt by setting the appropriate bits
          // in the corresponding mir_clear register.
          constexpr number_type   intc_sys_reg_index = number_type(number_type(isr_number >> 5U) & number_type(3U));
          constexpr std::uint32_t intc_sys_reg_bpos  = std::uint32_t(std::uint32_t(isr_number) & UINT32_C(0x01F));
          constexpr std::uint32_t intc_sys_reg_addr  = std::uint32_t(  mcal::reg::intc::sys_base_0x04
                                                                     + std::uint32_t(intc_sys_reg_index * UINT32_C(0x20))
                                                                     + mcal::reg::intc::sys::mir_clear);

          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       intc_sys_reg_addr,
                                       intc_sys_reg_bpos>::bit_set();
        }

        static constexpr number_type isr_id_emuint             = number_type(  0U);
        static constexpr number_type isr_id_commtx             = number_type(  1U);
        static constexpr number_type isr_id_commrx             = number_type(  2U);
        static constexpr number_type isr_id_bench              = number_type(  3U);
        static constexpr number_type isr_id_elm_irq            = number_type(  4U);
        static constexpr number_type isr_id_ssm_wfi_irq        = number_type(  5U);
        static constexpr number_type isr_id_ssm_irq            = number_type(  6U);
        static constexpr number_type isr_id_nmi                = number_type(  7U);
        static constexpr number_type isr_id_sec_evnt           = number_type(  8U);
        static constexpr number_type isr_id_l3debug            = number_type(  9U);
        static constexpr number_type isr_id_l3appint           = number_type( 10U);
        static constexpr number_type isr_id_prcmint            = number_type( 11U);
        static constexpr number_type isr_id_edmacompint        = number_type( 12U);
        static constexpr number_type isr_id_edmamperr          = number_type( 13U);
        static constexpr number_type isr_id_edmaerrint         = number_type( 14U);
        static constexpr number_type isr_id_wdt0int            = number_type( 15U);
        static constexpr number_type isr_id_adc_tsc_genint     = number_type( 16U);
        static constexpr number_type isr_id_usbssint           = number_type( 17U);
        static constexpr number_type isr_id_usb0               = number_type( 18U);
        static constexpr number_type isr_id_usb1               = number_type( 19U);
        static constexpr number_type isr_id_pruss1_evtout0     = number_type( 20U);
        static constexpr number_type isr_id_pruss1_evtout1     = number_type( 21U);
        static constexpr number_type isr_id_pruss1_evtout2     = number_type( 22U);
        static constexpr number_type isr_id_pruss1_evtout3     = number_type( 23U);
        static constexpr number_type isr_id_pruss1_evtout4     = number_type( 24U);
        static constexpr number_type isr_id_pruss1_evtout5     = number_type( 25U);
        static constexpr number_type isr_id_pruss1_evtout6     = number_type( 26U);
        static constexpr number_type isr_id_pruss1_evtout7     = number_type( 27U);
        static constexpr number_type isr_id_mmcsd1int          = number_type( 28U);
        static constexpr number_type isr_id_mmcsd2int          = number_type( 29U);
        static constexpr number_type isr_id_i2c2int            = number_type( 30U);
        static constexpr number_type isr_id_ecap0int           = number_type( 31U);
        static constexpr number_type isr_id_gpioint2a          = number_type( 32U);
        static constexpr number_type isr_id_gpioint2b          = number_type( 33U);
        static constexpr number_type isr_id_usbwakeup          = number_type( 34U);
        static constexpr number_type isr_id_unused_35          = number_type( 35U);
        static constexpr number_type isr_id_lcdcint            = number_type( 36U);
        static constexpr number_type isr_id_gfxint             = number_type( 37U);
        static constexpr number_type isr_id_2dhwaint           = number_type( 38U);
        static constexpr number_type isr_id_epwm2int           = number_type( 39U);
        static constexpr number_type isr_id_3pgswrxthr0        = number_type( 40U);
        static constexpr number_type isr_id_3pgswrxint0        = number_type( 41U);
        static constexpr number_type isr_id_3pgswtxint0        = number_type( 42U);
        static constexpr number_type isr_id_3pgswmisc0         = number_type( 43U);
        static constexpr number_type isr_id_uart3int           = number_type( 44U);
        static constexpr number_type isr_id_uart4int           = number_type( 45U);
        static constexpr number_type isr_id_uart5int           = number_type( 46U);
        static constexpr number_type isr_id_ecap1int           = number_type( 47U);
        static constexpr number_type isr_id_unused_48          = number_type( 48U);
        static constexpr number_type isr_id_unused_49          = number_type( 49U);
        static constexpr number_type isr_id_unused_50          = number_type( 50U);
        static constexpr number_type isr_id_unused_51          = number_type( 51U);
        static constexpr number_type isr_id_dcan0_int0         = number_type( 52U);
        static constexpr number_type isr_id_dcan0_int1         = number_type( 53U);
        static constexpr number_type isr_id_dcan0_parity       = number_type( 54U);
        static constexpr number_type isr_id_dcan1_int0         = number_type( 55U);
        static constexpr number_type isr_id_dcan1_int1         = number_type( 56U);
        static constexpr number_type isr_id_dcan1_parity       = number_type( 57U);
        static constexpr number_type isr_id_epwm0_tzint        = number_type( 58U);
        static constexpr number_type isr_id_epwm1_tzint        = number_type( 59U);
        static constexpr number_type isr_id_epwm2_tzint        = number_type( 60U);
        static constexpr number_type isr_id_ecap2int           = number_type( 61U);
        static constexpr number_type isr_id_gpioint3a          = number_type( 62U);
        static constexpr number_type isr_id_gpioint3b          = number_type( 63U);
        static constexpr number_type isr_id_mmcsd0int          = number_type( 64U);
        static constexpr number_type isr_id_spi0int            = number_type( 65U);
        static constexpr number_type isr_id_tint0              = number_type( 66U);
        static constexpr number_type isr_id_tint1_1ms          = number_type( 67U);
        static constexpr number_type isr_id_tint2              = number_type( 68U);
        static constexpr number_type isr_id_tint3              = number_type( 69U);
        static constexpr number_type isr_id_i2c0int            = number_type( 70U);
        static constexpr number_type isr_id_i2c1int            = number_type( 71U);
        static constexpr number_type isr_id_uart0int           = number_type( 72U);
        static constexpr number_type isr_id_uart1int           = number_type( 73U);
        static constexpr number_type isr_id_uart2int           = number_type( 74U);
        static constexpr number_type isr_id_rtcint             = number_type( 75U);
        static constexpr number_type isr_id_rtcalarmint        = number_type( 76U);
        static constexpr number_type isr_id_mbint0             = number_type( 77U);
        static constexpr number_type isr_id_m3_txev            = number_type( 78U);
        static constexpr number_type isr_id_eqep0int           = number_type( 79U);
        static constexpr number_type isr_id_mcatxint0          = number_type( 80U);
        static constexpr number_type isr_id_mcarxint0          = number_type( 81U);
        static constexpr number_type isr_id_mcatxint1          = number_type( 82U);
        static constexpr number_type isr_id_mcarxint1          = number_type( 83U);
        static constexpr number_type isr_id_unused_84          = number_type( 84U);
        static constexpr number_type isr_id_unused_85          = number_type( 85U);
        static constexpr number_type isr_id_epwm0int           = number_type( 86U);
        static constexpr number_type isr_id_epwm1int           = number_type( 87U);
        static constexpr number_type isr_id_eqep1int           = number_type( 88U);
        static constexpr number_type isr_id_eqep2int           = number_type( 89U);
        static constexpr number_type isr_id_dma_intr_pin2      = number_type( 90U);
        static constexpr number_type isr_id_wdt1int            = number_type( 91U);
        static constexpr number_type isr_id_tint4              = number_type( 92U);
        static constexpr number_type isr_id_tint5              = number_type( 93U);
        static constexpr number_type isr_id_tint6              = number_type( 94U);
        static constexpr number_type isr_id_tint7              = number_type( 95U);
        static constexpr number_type isr_id_gpioint0a          = number_type( 96U);
        static constexpr number_type isr_id_gpioint0b          = number_type( 97U);
        static constexpr number_type isr_id_gpioint1a          = number_type( 98U);
        static constexpr number_type isr_id_gpioint1b          = number_type( 99U);
        static constexpr number_type isr_id_gpmcint            = number_type(100U);
        static constexpr number_type isr_id_ddrerr0            = number_type(101U);
        static constexpr number_type isr_id_aes0_irq_s         = number_type(102U);
        static constexpr number_type isr_id_aes0_irq_p         = number_type(103U);
        static constexpr number_type isr_id_unused_104         = number_type(104U);
        static constexpr number_type isr_id_unused_105         = number_type(105U);
        static constexpr number_type isr_id_unused_106         = number_type(106U);
        static constexpr number_type isr_id_unused_107         = number_type(107U);
        static constexpr number_type isr_id_sha_irq_s          = number_type(108U);
        static constexpr number_type isr_id_sha_irq_p          = number_type(109U);
        static constexpr number_type isr_id_fpka_sintrequest_s = number_type(110U);
        static constexpr number_type isr_id_rng_irq            = number_type(111U);
        static constexpr number_type isr_id_tcerrint0          = number_type(112U);
        static constexpr number_type isr_id_tcerrint1          = number_type(113U);
        static constexpr number_type isr_id_tcerrint2          = number_type(114U);
        static constexpr number_type isr_id_unused_115         = number_type(115U);
        static constexpr number_type isr_id_unused_116         = number_type(116U);
        static constexpr number_type isr_id_unused_117         = number_type(117U);
        static constexpr number_type isr_id_unused_118         = number_type(118U);
        static constexpr number_type isr_id_unused_119         = number_type(119U);
        static constexpr number_type isr_id_smrflx_sabertooth  = number_type(120U);
        static constexpr number_type isr_id_smrflx_core        = number_type(121U);
        static constexpr number_type isr_id_unused_122         = number_type(122U);
        static constexpr number_type isr_id_dma_intr_pin0      = number_type(123U);
        static constexpr number_type isr_id_dma_intr_pin1      = number_type(124U);
        static constexpr number_type isr_id_spi1int            = number_type(125U);
        static constexpr number_type isr_id_unused_126         = number_type(126U);
        static constexpr number_type isr_id_unused_127         = number_type(127U);
        static constexpr number_type number_of_interrupts      = number_type(128U);
      };
    }
  }

#endif // MCAL_IRQ_2010_04_10_H_
