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

#include <util/utility/util_time.h>

extern "C"
{
  auto main_c1() -> void;
  auto Mcu_StartCore1() -> void;
  auto Mcu_StartCoProcessorRiscV() -> void;

  extern auto set_cpu_private_timer1(uint32_t) -> void;
  extern auto _start() -> void;
}

namespace local
{
  auto main_worker_core1(mcal::led::led_base& my_led) -> void;

  template<typename UnsignedTickType>
  struct timer_core1_backend
  {
    using tick_type = UnsignedTickType;

    constexpr static auto get_now() -> tick_type
    {
      return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core1());
    }
  };
} // namespace local

extern "C"
auto Mcu_StartCore1() -> void
{
  // Note: This subroutine is called from core0.

  // As a first step, we need to un-stall core1.

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

  // Enable the clock for core1.

  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_CLKGATE_EN = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(1))>::bit_set();

  // Reset core1.

  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_RESETING   = 1;
  // SYSTEM->CORE_1_CONTROL_0.bit.CONTROL_CORE_1_RESETING   = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(2))>::bit_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::core_1_control_0, static_cast<std::uint32_t>(UINT8_C(2))>::bit_clr();

  // Note: In ESP32-S3 when the reset of core1 is released,
  // then core1 starts executing the bootROM code. Core1
  // subsequently gets stuck in a trap. It is waiting for
  // the entry address to be received from core0.

  // The send/receive transaction of the entry address is
  // carried out via core0 deliberately writing the core1
  // entry address in the SYSTEM_CORE_1_CONTROL_1_REG register.
  // When this is achieved and done, core1 exits the trap
  // and progresses forward.

  {
    // Set the core1 entry address.

    using mcal_reg_access_dynamic_type = mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>;

    // SYSTEM->CORE_1_CONTROL_1.reg = (uint32_t) &_start;

    mcal_reg_access_dynamic_type::reg_set
    (
      mcal::reg::system::core_1_control_1,
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&_start))
    );
  }
}

extern "C"
auto Mcu_StartCoProcessorRiscV() -> void
{
  // RTC_CNTL->COCPU_CTRL.bit.COCPU_SHUT_RESET_EN     = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::cocpu_ctrl, std::uint32_t { UINT8_C(22) }>::bit_set();

  // RTC_CNTL->ULP_CP_TIMER.reg                       = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::ulp_cp_timer, std::uint32_t { UINT8_C(0) }>::reg_set();

  // RTC_CNTL->COCPU_CTRL.bit.COCPU_CLK_FO            = 1;
  // RTC_CNTL->COCPU_CTRL.bit.COCPU_DONE_FORCE        = 1;
  // RTC_CNTL->COCPU_CTRL.bit.COCPU_CLKGATE_EN        = 1;
  // RTC_CNTL->COCPU_CTRL.bit.COCPU_SEL               = 0;

  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::cocpu_ctrl, std::uint32_t { UINT8_C( 0) }>::bit_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::cocpu_ctrl, std::uint32_t { UINT8_C(24) }>::bit_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::cocpu_ctrl, std::uint32_t { UINT8_C(27) }>::bit_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::cocpu_ctrl, std::uint32_t { UINT8_C(23) }>::bit_clr();

  // RTC_CNTL->ULP_CP_CTRL.bit.ULP_CP_FORCE_START_TOP = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::ulp_cp_ctrl, std::uint32_t { UINT8_C(30) }>::bit_clr();

  // RTC_CNTL->ULP_CP_TIMER.bit.ULP_CP_SLP_TIMER_EN   = 1;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::ulp_cp_timer, std::uint32_t { UINT8_C(31) }>::bit_set();
}

extern "C"
auto main_c1() -> void
{
  // Note: This subroutine executes in core1. It has been called
  // by the core1 branch of the subroutine _start().

  // Set the private cpu timer1 for core1.
  set_cpu_private_timer1(mcal::gpt::detail::timer1_reload());

  // Enable all interrupts on core1.
  mcal::irq::init(nullptr);

  // Perpetually toggle the LED with a flag-based trigger
  // in the for(ever)-loop of main_worker_core1().
  local::main_worker_core1(mcal::led::led1());
}

auto mcal::cpu::post_init() noexcept -> void
{
  // Note: This subroutine is called from core0.

  // Set the private cpu timer1 for core0.
  set_cpu_private_timer1(mcal::gpt::detail::timer1_reload());

  // Use core0 to start the RISC-V core.
  Mcu_StartCoProcessorRiscV();

  // Use core0 to start core1.
  Mcu_StartCore1();
}

auto mcal::cpu::init() -> void
{
  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

auto local::main_worker_core1(mcal::led::led_base& my_led) -> void
{
  my_led.toggle();

  using local_timer_type = util::timer<std::uint32_t, local::timer_core1_backend<std::uint32_t>>;
  using local_tick_type = typename local_timer_type::tick_type;

  constexpr local_tick_type led_time_1sec { local_timer_type::seconds(local_tick_type { UINT8_C(1) }) };

  local_timer_type led_timer { led_time_1sec };

  for(;;)
  {
    while(!led_timer.timeout())
    {
      mcal::cpu::nop();
    }

    my_led.toggle();

    led_timer.start_interval(led_time_1sec);
  }
}
