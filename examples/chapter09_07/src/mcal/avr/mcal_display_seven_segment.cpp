///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_display_seven_segment.h>
#include <mcal_display_board.h>

util::device::display_seven_segment& mcal::display::display0()
{
  using portc0_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(0)>;
  using portc1_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(1)>;
  using portc2_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(2)>;
  using portc3_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(3)>;
  using portc4_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(4)>;
  using portc5_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(5)>;
  using portd0_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portd, UINT8_C(0)>;
  using portd1_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portd, UINT8_C(1)>;

  typedef display_board<portc4_type,
                        portc3_type,
                        portc1_type,
                        portc0_type,
                        portc5_type,
                        portd0_type,
                        portd1_type,
                        portc2_type> display_type;

  static display_type the_display;

  return the_display;
}
