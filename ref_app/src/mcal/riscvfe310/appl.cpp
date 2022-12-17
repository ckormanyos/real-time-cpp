#include <cstddef>

#include <mcal_gpt.h>
#include <mcal_port.h>
#include <mcal_reg.h>

#include <mcal_led/mcal_led_port.h>
#include <util/utility/util_time.h>
#include <util/utility/util_two_part_data_manipulation.h>

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
  mcal::reg::reg_access_static<std::uint32_t, std::uint64_t, mcal::reg::clint_mtimecmp, static_cast<std::uint64_t>(UINT64_C(0xFFFFFFFFFFFFFFFF))>::reg_set();

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
  auto read_lo = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtime >::reg_get(); };
  auto read_hi = [](void) -> std::uint32_t { return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::clint_mtimeh>::reg_get(); };

  auto to_microseconds =
    [](const std::uint32_t tick_val) -> std::uint32_t
    {
      const auto result_non_trimmed =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_val) * static_cast<std::uint8_t>(UINT8_C(61)))
          / static_cast<std::uint8_t>(UINT8_C(2))
        );

      const auto trimming_amount =
        static_cast<std::uint64_t>
        (
            static_cast<std::uint64_t>(static_cast<std::uint64_t>(tick_val) * static_cast<std::uint8_t>(UINT8_C(19)))
          / static_cast<std::uint32_t>(UINT32_C(32768))
        );

      return
        static_cast<std::uint32_t>
        (
          static_cast<std::uint64_t>(result_non_trimmed + trimming_amount)
        );
    };

  const auto mt_lo_1 = to_microseconds(read_lo());
  const auto mt_hi_1 = to_microseconds(read_hi());

  const auto mt_lo_2 = to_microseconds(read_lo());

  const auto consistent_microsecond_tick =
    static_cast<std::uint64_t>
    (
      (mt_lo_2 > mt_lo_1) ? util::make_long(mt_lo_1, mt_hi_1)
                          : util::make_long(mt_lo_2, to_microseconds(read_hi()))
    );

  return static_cast<mcal::gpt::value_type>(consistent_microsecond_tick);
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
