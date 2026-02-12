/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <riscv-csr.h>
#include <interrupt.h>
#include <gpio.h>

#include <mcal_gpt.h>

#include <util/utility/util_time.h>

#include <cstdint>

constexpr unsigned TIMEOUT_500MS { 160000000u };
constexpr unsigned TIMEOUT_1S    { 320000000u };

extern "C"
{
  uint32_t osGetActiveCore(void);
}

auto main_core0() -> void;
auto main_core1() -> void;

auto main(void) -> int __attribute__((used,noinline));

auto main(void) -> int
{
  const std::uint32_t core_id { osGetActiveCore() };

  if(std::uint32_t { UINT8_C(0) } == core_id)
  {
    gpio_cfg_output(7);
    gpio_cfg_output(8);
    gpio_cfg_output(24);
    gpio_cfg_output(25);
    gpio_cfg_output(46);
    gpio_cfg_output(47);
    gpio_cfg_output(48);
    gpio_cfg_output(54);
    gpio_cfg_output(20);
    gpio_cfg_output(19);
    gpio_cfg_output(18);
    gpio_cfg_output(17);
    gpio_cfg_output(16);
    gpio_cfg_output(15);
    gpio_cfg_output(14);
    gpio_cfg_output(33);
    gpio_cfg_output(32);
    gpio_cfg_output(27);
    gpio_cfg_output(26);
    gpio_cfg_output(23);
    gpio_cfg_output(32);
    gpio_cfg_output(21);
  }

  // Go to the core-specific main subroutines.
  if(std::uint32_t { UINT8_C(0) } == core_id)
  {
    mcal::gpt::init(nullptr);

    ::main_core0();
  }
  else
  {
    mcal::gpt::init(nullptr);

    ::main_core1();
  }
}

namespace local
{
  using timer_type = util::timer<std::uint64_t>;

  using timer_core1_type = util::timer<std::uint64_t, mcal::gpt::timer_core1_backend>;
} // namespace local

auto main_core0() -> void
{
  gpio_toggle_output_level(54);

  local::timer_type led_timer(local::timer_type::seconds(1U));

  // Endless loop: Never return or break.
  while(1)
  {
    if(led_timer.timeout())
    {
      gpio_toggle_output_level(54);

      led_timer.start_interval(local::timer_type::seconds(1U));
    }
  }
}

auto main_core1() -> void
{
  gpio_toggle_output_level(19);

  local::timer_core1_type led_timer(local::timer_type::seconds(1U));

  // Endless loop: Never return or break.
  while(1)
  {
    if(led_timer.timeout())
    {
      gpio_toggle_output_level(19);

      led_timer.start_interval(local::timer_type::seconds(1U));
    }
  }
}
