/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <gpio.h>

#include <mcal_gpt.h>

#include <util/utility/util_time.h>

extern "C"
{
  uint32_t osGetActiveCore(void);
}

auto main_core0() -> void;
auto main_core1() -> void;

auto main(void) -> int __attribute__((used,noinline));

auto main(void) -> int
{
  const bool core_id_is_zero { (std::uint32_t { UINT8_C(0) } == osGetActiveCore()) };

  if(core_id_is_zero)
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
  if(core_id_is_zero)
  {
    ::main_core0();
  }
  else
  {
    ::main_core1();
  }
}

namespace local
{
  struct timer_core1_backend
  {
    using tick_type = std::uint64_t;

    static auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core1()); }
  };

  using timer_type = util::timer<std::uint64_t>;

  constexpr typename timer_type::tick_type
    led_timeout
    {
      static_cast<typename timer_type::tick_type>(timer_type::seconds(UINT8_C(1)))
    };

  using timer_core1_type = util::timer<std::uint64_t, timer_core1_backend>;
} // namespace local

auto main_core0() -> void
{
  gpio_toggle_output_level(54);

  mcal::gpt::init(nullptr);

  local::timer_type local_led_timer(local::led_timeout);

  // Endless LED tollge-loop: Never return or break.
  for(;;)
  {
    if(local_led_timer.timeout())
    {
      gpio_toggle_output_level(54);

      local_led_timer.start_interval(local::led_timeout);
    }
  }
}

auto main_core1() -> void
{
  gpio_toggle_output_level(19);

  mcal::gpt::init(nullptr);

  local::timer_core1_type local_led_timer(local::led_timeout);

  // Endless LED tollge-loop: Never return or break.
  for(;;)
  {
    if(local_led_timer.timeout())
    {
      gpio_toggle_output_level(19);

      local_led_timer.start_interval(local::led_timeout);
    }
  }
}
