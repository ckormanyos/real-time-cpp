
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <util/utility/util_time.h>
#include <math/checksums/crypto_hash/sha1.h>

namespace app
{
  namespace led
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  typedef util::timer<std::uint32_t> timer_type;
  timer_type app_led_timer(timer_type::milliseconds(100U));

  typedef sha1<std::uint8_t> sha1_type;
  const std::uint32_t              control_value = UINT32_C(0x8029201C);
  sha1_type                        the_sha1;
  sha1_type::result_type_as_dwords the_sha1_result_as_dwords;
  bool                             the_result_is_ok = true;

  timer_type            app_runtime_timer;
  timer_type::tick_type app_runtime_result;

  typedef mcal::port::port_pin<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::portd,
                               UINT8_C(2)> app_runtime_port_type;
}

void app::led::task_init()
{
  mcal::led::led0.toggle();

  app_runtime_port_type::set_direction_output();
}

void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(timer_type::milliseconds(100U));

    static std::uint_least8_t led_toggle_prescaler;

    ++led_toggle_prescaler;

    if(led_toggle_prescaler == static_cast<std::uint_least8_t>(10U))
    {
      mcal::led::led0.toggle();

      led_toggle_prescaler = static_cast<std::uint_least8_t>(0U);
    }

    if(the_result_is_ok)
    {
      app_runtime_port_type::set_pin_high();
      app_runtime_timer.set_mark();
      the_sha1.process_data("creativity", sha1_type::count_type(10U));
      the_sha1_result_as_dwords = the_sha1.get_result_as_dwords_and_finalize_the_state();
      app_runtime_result = app_runtime_timer.get_ticks_since_mark();
      app_runtime_port_type::set_pin_low();

      the_result_is_ok = (the_sha1_result_as_dwords.front() == control_value);
    }
  }
}
