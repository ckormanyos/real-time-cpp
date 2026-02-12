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
  extern auto osGetActiveCore(void) -> std::uint32_t;

  auto main_core0() -> void;
  auto main_core1() -> void;
}

auto main(void) -> int __attribute__((used,noinline));

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

extern "C"
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

extern "C"
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
