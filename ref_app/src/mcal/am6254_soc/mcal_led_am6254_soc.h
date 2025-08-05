///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Parts of this file originate from the file Mcal/Gpio/led.h in:
// https://github.com/Chalandi/Baremetal_TI_AM6254_multicore_nosdk

#ifndef MCAL_LED_AM6254_SOC_2025_08_04_H
  #define MCAL_LED_AM6254_SOC_2025_08_04_H

  #include <mcal_led/mcal_led_port.h>
  #include <mcal_port.h>

  #include <util/utility/util_time.h>

  #include <cstdint>

  namespace mcal
  {
    namespace led
    {
      constexpr unsigned LED_1 { UINT8_C(6) };
      constexpr unsigned LED_2 { UINT8_C(5) };
      constexpr unsigned LED_3 { UINT8_C(4) };
      constexpr unsigned LED_4 { UINT8_C(3) };

      template<typename PortType>
      class led_am6254_soc final : public mcal::led::led_port<PortType>
      {
      public:
        led_am6254_soc() noexcept = default;

        ~led_am6254_soc() override = default;

        static auto main_core_worker() -> void
        {
          using local_timer_type = util::timer<std::uint64_t>;
          using local_tick_type = typename local_timer_type::tick_type;
          using port_type = PortType;
          using local_led_type = led_am6254_soc<port_type>;

          local_led_type my_led { };

          local_timer_type led_timer(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));

          my_led.toggle();

          for(;;)
          {
            while(!led_timer.timeout()) { asm volatile("nop"); }

            my_led.toggle();

            led_timer.start_interval(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));
          }
        }
      };
    } // namespace led
  } // namespace mcal

#endif // MCAL_LED_AM6254_SOC_2025_08_04_H
