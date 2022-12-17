#include <cstddef>

#include <mcal_gpt.h>
#include <mcal_led.h>
#include <mcal_port.h>
#include <mcal_reg.h>

#include <mcal_led/mcal_led_port.h>
#include <util/utility/util_time.h>

extern "C" auto appl_main(void) -> void;

namespace
{
  using app_led_timer_type = util::timer<std::uint32_t>;

  app_led_timer_type timer(app_led_timer_type::seconds(1U));
}

extern "C" auto appl_main(void) -> void
{
  mcal::gpt::init(nullptr);

  mcal::led::led0().toggle();

  // Enter an endless loop.
  for(;;)
  {
    // Toggle the LED upon timeout and reset the timer.
    if(timer.timeout())
    {
      mcal::led::led0().toggle();

      timer.start_interval(app_led_timer_type::seconds(1U));
    }
  }
}

void operator delete(void*)        noexcept;
void operator delete(void*, void*) noexcept;
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept;
#endif

void operator delete(void*)              noexcept { }
void operator delete(void*, void*)       noexcept { }
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept { }
#endif

extern "C"
{
  int atexit(void (*)(void)) __attribute__((used, noinline));

  int atexit(void (*)(void)) { return 0; }
}
