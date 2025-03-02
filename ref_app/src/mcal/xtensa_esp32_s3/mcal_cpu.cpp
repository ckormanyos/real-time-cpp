///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_led.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

extern "C"
{
  auto main_c1() -> void;
  auto Mcu_StartCore1() -> void;

  extern auto set_cpu_private_timer1(uint32_t) -> void;
  extern auto _start() -> void;
}

extern "C"
void Mcu_StartCore1()
{
  // Unstall core 1.

  // RTC_CNTL->OPTIONS0.bit.SW_STALL_APPCPU_C0            = 0;
  // RTC_CNTL->SW_CPU_STALL.bit.SW_STALL_APPCPU_C1        = 0;
  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_RUNSTALL = 0;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rtc_cntl::options0,
                               std::uint32_t { UINT32_C(0) << 0U }>::template reg_msk<std::uint32_t { UINT32_C(0x3) << 0U }>();

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rtc_cntl::sw_cpu_stall,
                               std::uint32_t { UINT32_C(0) << 20U }>::template reg_msk<std::uint32_t { UINT32_C(0x3F) << 0U }>();

  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(0))>::bit_clr();

  // Enable the clock for core 1.

  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_CLKGATE_EN = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(1))>::bit_set();

  // Reset core 1.

  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_RESETING   = 1;
  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_RESETING   = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(2))>::bit_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(2))>::bit_clr();

  // Note: In ESP32-S3, when the reset of the core1 is released,
  // the core1 starts executing the bootROM code and it gets stuck
  // in a trap waiting for the entry address to be received
  // from core0. This is can be achieved by writing the core1 entry
  // address to the register SYSTEM_CORE_1_CONTROL_1_REG from core0.

  // Set the core1 entry address.

  // SYSTEM->CORE_1_CONTROL_1.reg = (uint32_t) &_start;
  {
    const std::uint32_t start_addr { reinterpret_cast<std::uint32_t>(&_start) };

    mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::system::core_1_control_1, start_addr);
  }
}

extern "C"
void main_c1()
{
  // Set the private cpu timer1 for core 1.
  set_cpu_private_timer1(mcal::gpt::timer1_reload());

  // Enable all interrupts on core 1.
  mcal::irq::init(nullptr);

  // GPIO->OUT.reg |= CORE1_LED;
  mcal::led::led1().toggle();

  for(;;) { mcal::cpu::nop(); }
}

auto mcal::cpu::post_init() noexcept -> void
{
  // Set the private cpu timer1 for core 0.
  set_cpu_private_timer1(mcal::gpt::timer1_reload());

  // Use core 0 to start core 1.
  Mcu_StartCore1();
}

auto mcal::cpu::init() -> void
{
  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
