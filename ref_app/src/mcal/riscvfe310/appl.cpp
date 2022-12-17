#include <cstddef>

#include <mcal_gpt.h>
#include <mcal_port.h>
#include <mcal_reg.h>

#include <mcal_led/mcal_led_port.h>
#include <util/utility/util_time.h>

extern "C" auto appl_main(void) -> void;

namespace
{
  using led0_port_type = mcal::port::port_pin<std::uint32_t,
                                              std::uint32_t,
                                              mcal::reg::gpio0_base,
                                              UINT8_C(5)>;

  using app_led_timer_type = util::timer<std::uint32_t>;

  app_led_timer_type timer(app_led_timer_type::seconds(1U));
}

extern "C" auto appl_main(void) -> void
{
  led0_port_type::set_pin_high();
  led0_port_type::set_direction_output();

  /* endless loop*/
  for(;;)
  {
    if(timer.timeout())
    {
      led0_port_type::toggle_pin();

      timer.start_interval(app_led_timer_type::seconds(1U));
    }
  }
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  const auto tick_unscaled =
    mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtime>::reg_get();

  const auto microsecond_tick =
    static_cast<std::uint64_t>
    (
        static_cast<std::uint64_t>(tick_unscaled * static_cast<std::uint8_t>(UINT8_C(61)))
      / static_cast<std::uint8_t>(UINT8_C(2))
    );

  return static_cast<mcal::gpt::value_type>(microsecond_tick);
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
