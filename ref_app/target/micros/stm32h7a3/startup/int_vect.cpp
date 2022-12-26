///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void __initial_stack_pointer();

extern "C" void __my_startup         () noexcept __attribute__((used, noinline));
extern "C" void __vector_unused_irq  () noexcept __attribute__((used, noinline));
extern "C" void __nmi_handler        () noexcept __attribute__((used, noinline));
extern "C" void __hard_fault_handler () noexcept __attribute__((used, noinline));
extern "C" void __mem_manage_handler () noexcept __attribute__((used, noinline));
extern "C" void __bus_fault_handler  () noexcept __attribute__((used, noinline));
extern "C" void __usage_fault_handler() noexcept __attribute__((used, noinline));
extern "C" void __svc_handler        () noexcept __attribute__((used, noinline));
extern "C" void __debug_mon_handler  () noexcept __attribute__((used, noinline));
extern "C" void __pend_sv_handler    () noexcept __attribute__((used, noinline));
extern "C" void __sys_tick_handler   () noexcept __attribute__((used, noinline));

extern "C" void __vector_unused_irq  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __nmi_handler        () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __hard_fault_handler () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __mem_manage_handler () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __bus_fault_handler  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __usage_fault_handler() noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __svc_handler        () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __debug_mon_handler  () noexcept { for(;;) { mcal::cpu::nop(); } }
extern "C" void __pend_sv_handler    () noexcept { for(;;) { mcal::cpu::nop(); } }

namespace
{
  typedef void(*isr_type)(void);

  constexpr auto number_of_interrupts = static_cast<std::size_t>(UINT8_C(128) + UINT8_C(48));
}

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<isr_type, number_of_interrupts> __isr_vector =
{{
  __initial_stack_pointer,   // 0x0000, initial stack pointer
  __my_startup,              // 0x0004, reset
  __nmi_handler,             // 0x0008, nmi exception
  __hard_fault_handler,      // 0x000C, hard fault exception
  __mem_manage_handler,      // 0x0010, memory management exception
  __bus_fault_handler,       // 0x0014, bus fault exception
  __usage_fault_handler,     // 0x0018, usage fault exception
  __vector_unused_irq,       // 0x001C, reserved
  __vector_unused_irq,       // 0x0020, reserved
  __vector_unused_irq,       // 0x0024, reserved
  __vector_unused_irq,       // 0x0028, reserved
  __svc_handler,             // 0x002C, svc handler
  __debug_mon_handler,       // 0x0030, debug monitor
  __vector_unused_irq,       // 0x0034, reserved
  __pend_sv_handler,         // 0x0038, pending svc
  __sys_tick_handler,        // 0x003C, system tick handler
  __vector_unused_irq,       // 0x0040, wwdg_irqhandler
  __vector_unused_irq,       // 0x0044, pvd_pvm_irqhandler
  __vector_unused_irq,       // 0x0048, rtc_tamp_stamp_css_lse_irqhandler
  __vector_unused_irq,       // 0x004C, rtc_wkup_irqhandler
  __vector_unused_irq,       // 0x0050, flash_irqhandler
  __vector_unused_irq,       // 0x0054, rcc_irqhandler
  __vector_unused_irq,       // 0x0058, exti0_irqhandler
  __vector_unused_irq,       // 0x005C, exti1_irqhandler
  __vector_unused_irq,       // 0x0060, exti2_irqhandler
  __vector_unused_irq,       // 0x0064, exti3_irqhandler
  __vector_unused_irq,       // 0x0068, exti4_irqhandler
  __vector_unused_irq,       // 0x006C, dma1_stream0_irqhandler
  __vector_unused_irq,       // 0x0070, dma1_stream1_irqhandler
  __vector_unused_irq,       // 0x0074, dma1_stream2_irqhandler
  __vector_unused_irq,       // 0x0078, dma1_stream3_irqhandler
  __vector_unused_irq,       // 0x007C, dma1_stream4_irqhandler
  __vector_unused_irq,       // 0x0080, dma1_stream5_irqhandler
  __vector_unused_irq,       // 0x0084, dma1_stream6_irqhandler
  __vector_unused_irq,       // 0x0088, adc_irqhandler
  __vector_unused_irq,       // 0x008C, fdcan1_it0_irqhandler
  __vector_unused_irq,       // 0x0090, fdcan2_it0_irqhandler
  __vector_unused_irq,       // 0x0094, fdcan1_it1_irqhandler
  __vector_unused_irq,       // 0x0098, fdcan2_it1_irqhandler
  __vector_unused_irq,       // 0x009C, exti9_5_irqhandler
  __vector_unused_irq,       // 0x00A0, tim1_brk_irqhandler
  __vector_unused_irq,       // 0x00A4, tim1_up_irqhandler
  __vector_unused_irq,       // 0x00A8, tim1_trg_com_irqhandler
  __vector_unused_irq,       // 0x00AC, tim1_cc_irqhandler
  __vector_unused_irq,       // 0x00B0, tim2_irqhandler
  __vector_unused_irq,       // 0x00B4, tim3_irqhandler
  __vector_unused_irq,       // 0x00B8, tim4_irqhandler
  __vector_unused_irq,       // 0x00BC, i2c1_ev_irqhandler
  __vector_unused_irq,       // 0x00C0, i2c1_er_irqhandler
  __vector_unused_irq,       // 0x00C4, i2c2_ev_irqhandler
  __vector_unused_irq,       // 0x00C8, i2c2_er_irqhandler
  __vector_unused_irq,       // 0x00CC, spi1_irqhandler
  __vector_unused_irq,       // 0x00D0, spi2_irqhandler
  __vector_unused_irq,       // 0x00D4, usart1_irqhandler
  __vector_unused_irq,       // 0x00D8, usart2_irqhandler
  __vector_unused_irq,       // 0x00DC, usart3_irqhandler
  __vector_unused_irq,       // 0x00E0, exti15_10_irqhandler
  __vector_unused_irq,       // 0x00E4, rtc_alarm_irqhandler
  __vector_unused_irq,       // 0x00E8, dfsdm2_irqhandler
  __vector_unused_irq,       // 0x00EC, tim8_brk_tim12_irqhandler
  __vector_unused_irq,       // 0x00F0, tim8_up_tim13_irqhandler
  __vector_unused_irq,       // 0x00F4, tim8_trg_com_tim14_irqhandler
  __vector_unused_irq,       // 0x00F8, tim8_cc_irqhandler
  __vector_unused_irq,       // 0x00FC, dma1_stream7_irqhandler
  __vector_unused_irq,       // 0x0100, fmc_irqhandler
  __vector_unused_irq,       // 0x0104, sdmmc1_irqhandler
  __vector_unused_irq,       // 0x0108, tim5_irqhandler
  __vector_unused_irq,       // 0x010C, spi3_irqhandler
  __vector_unused_irq,       // 0x0110, uart4_irqhandler
  __vector_unused_irq,       // 0x0114, uart5_irqhandler
  __vector_unused_irq,       // 0x0118, tim6_dac_irqhandler
  __vector_unused_irq,       // 0x011C, tim7_irqhandler
  __vector_unused_irq,       // 0x0120, dma2_stream0_irqhandler
  __vector_unused_irq,       // 0x0124, dma2_stream1_irqhandler
  __vector_unused_irq,       // 0x0128, dma2_stream2_irqhandler
  __vector_unused_irq,       // 0x012C, dma2_stream3_irqhandler
  __vector_unused_irq,       // 0x0130, dma2_stream4_irqhandler
  nullptr,                   // 0x0134, 0
  nullptr,                   // 0x0138, 0
  __vector_unused_irq,       // 0x013C, fdcan_cal_irqhandler
  __vector_unused_irq,       // 0x0140, dfsdm1_flt4_irqhandler
  __vector_unused_irq,       // 0x0144, dfsdm1_flt5_irqhandler
  __vector_unused_irq,       // 0x0148, dfsdm1_flt6_irqhandler
  __vector_unused_irq,       // 0x014C, dfsdm1_flt7_irqhandler
  __vector_unused_irq,       // 0x0150, dma2_stream5_irqhandler
  __vector_unused_irq,       // 0x0154, dma2_stream6_irqhandler
  __vector_unused_irq,       // 0x0158, dma2_stream7_irqhandler
  __vector_unused_irq,       // 0x015C, usart6_irqhandler
  __vector_unused_irq,       // 0x0160, i2c3_ev_irqhandler
  __vector_unused_irq,       // 0x0164, i2c3_er_irqhandler
  __vector_unused_irq,       // 0x0168, otg_hs_ep1_out_irqhandler
  __vector_unused_irq,       // 0x016C, otg_hs_ep1_in_irqhandler
  __vector_unused_irq,       // 0x0170, otg_hs_wkup_irqhandler
  __vector_unused_irq,       // 0x0174, otg_hs_irqhandler
  __vector_unused_irq,       // 0x0178, dcmi_pssi_irqhandler
  nullptr,                   // 0x017C, 0
  __vector_unused_irq,       // 0x0180, rng_irqhandler
  __vector_unused_irq,       // 0x0184, fpu_irqhandler
  __vector_unused_irq,       // 0x0188, uart7_irqhandler
  __vector_unused_irq,       // 0x018C, uart8_irqhandler
  __vector_unused_irq,       // 0x0190, spi4_irqhandler
  __vector_unused_irq,       // 0x0194, spi5_irqhandler
  __vector_unused_irq,       // 0x0198, spi6_irqhandler
  __vector_unused_irq,       // 0x019C, sai1_irqhandler
  __vector_unused_irq,       // 0x01A0, ltdc_irqhandler
  __vector_unused_irq,       // 0x01A4, ltdc_er_irqhandler
  __vector_unused_irq,       // 0x01A8, dma2d_irqhandler
  __vector_unused_irq,       // 0x01AC, sai2_irqhandler
  __vector_unused_irq,       // 0x01B0, octospi1_irqhandler
  __vector_unused_irq,       // 0x01B4, lptim1_irqhandler
  __vector_unused_irq,       // 0x01B8, cec_irqhandler
  __vector_unused_irq,       // 0x01BC, i2c4_ev_irqhandler
  __vector_unused_irq,       // 0x01C0, i2c4_er_irqhandler
  __vector_unused_irq,       // 0x01C4, spdif_rx_irqhandler
  nullptr,                   // 0x01C8, 0
  nullptr,                   // 0x01CC, 0
  nullptr,                   // 0x01D0, 0
  nullptr,                   // 0x01D4, 0
  __vector_unused_irq,       // 0x01D8, dmamux1_ovr_irqhandler
  nullptr,                   // 0x01DC, 0
  nullptr,                   // 0x01E0, 0
  nullptr,                   // 0x01E4, 0
  nullptr,                   // 0x01E8, 0
  nullptr,                   // 0x01EC, 0
  nullptr,                   // 0x01F0, 0
  nullptr,                   // 0x01F4, 0
  __vector_unused_irq,       // 0x01F8, dfsdm1_flt0_irqhandler
  __vector_unused_irq,       // 0x01FC, dfsdm1_flt1_irqhandler
  __vector_unused_irq,       // 0x0200, dfsdm1_flt2_irqhandler
  __vector_unused_irq,       // 0x0204, dfsdm1_flt3_irqhandler
  nullptr,                   // 0x0208, 0
  __vector_unused_irq,       // 0x020C, swpmi1_irqhandler
  __vector_unused_irq,       // 0x0210, tim15_irqhandler
  __vector_unused_irq,       // 0x0214, tim16_irqhandler
  __vector_unused_irq,       // 0x0218, tim17_irqhandler
  __vector_unused_irq,       // 0x021C, mdios_wkup_irqhandler
  __vector_unused_irq,       // 0x0220, mdios_irqhandler
  __vector_unused_irq,       // 0x0224, jpeg_irqhandler
  __vector_unused_irq,       // 0x0228, mdma_irqhandler
  nullptr,                   // 0x022C, 0
  __vector_unused_irq,       // 0x0230, sdmmc2_irqhandler
  __vector_unused_irq,       // 0x0234, hsem1_irqhandler
  nullptr,                   // 0x0238, 0
  __vector_unused_irq,       // 0x023C, dac2_irqhandler
  __vector_unused_irq,       // 0x0240, dmamux2_ovr_irqhandler
  __vector_unused_irq,       // 0x0244, bdma2_channel0_irqhandler
  __vector_unused_irq,       // 0x0248, bdma2_channel1_irqhandler
  __vector_unused_irq,       // 0x024C, bdma2_channel2_irqhandler
  __vector_unused_irq,       // 0x0250, bdma2_channel3_irqhandler
  __vector_unused_irq,       // 0x0254, bdma2_channel4_irqhandler
  __vector_unused_irq,       // 0x0258, bdma2_channel5_irqhandler
  __vector_unused_irq,       // 0x025C, bdma2_channel6_irqhandler
  __vector_unused_irq,       // 0x0260, bdma2_channel7_irqhandler
  __vector_unused_irq,       // 0x0264, comp_irqhandler
  __vector_unused_irq,       // 0x0268, lptim2_irqhandler
  __vector_unused_irq,       // 0x026C, lptim3_irqhandler
  __vector_unused_irq,       // 0x0270, uart9_irqhandler
  __vector_unused_irq,       // 0x0274, usart10_irqhandler
  __vector_unused_irq,       // 0x0278, lpuart1_irqhandler
  nullptr,                   // 0x027C, 0
  __vector_unused_irq,       // 0x0280, crs_irqhandler
  __vector_unused_irq,       // 0x0284, ecc_irqhandler
  nullptr,                   // 0x0288, 0
  __vector_unused_irq,       // 0x028C, dts_irqhandler
  nullptr,                   // 0x0290, 0
  __vector_unused_irq,       // 0x0294, wakeup_pin_irqhandler
  __vector_unused_irq,       // 0x0298, octospi2_irqhandler
  nullptr,                   // 0x029C, 0
  nullptr,                   // 0x02A0, 0
  __vector_unused_irq,       // 0x02A4, gfxmmu_irqhandler
  __vector_unused_irq,       // 0x02A8, bdma1_irqhandler
  nullptr,                   // 0x02AC, not used
  nullptr,                   // 0x02B0, not used
  nullptr,                   // 0x02B4, not used
  nullptr,                   // 0x02B8, not used
  nullptr                    // 0x02BC, not used
}};
