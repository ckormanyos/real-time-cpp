///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_2011_10_20_H
  #define MCAL_2011_10_20_H

  #include <mcal_cpu.h>
  #include <mcal_eep.h>
  #include <mcal_gpt.h>
  #include <mcal_irq.h>
  #include <mcal_led.h>
  #include <mcal_port.h>
  #include <mcal_pwm.h>
  #include <mcal_ser.h>
  #include <mcal_spi.h>
  #include <mcal_wdg.h>

  #include <cstdint>
  #include <limits>

  static_assert(    (std::numeric_limits<mcal::gpt::value_type>::digits >= static_cast<int>(INT8_C(64)))
                &&   std::numeric_limits<mcal::gpt::value_type>::is_integer
                && (!std::numeric_limits<mcal::gpt::value_type>::is_signed),
                "The gpt value type must be an unsigned integer type having at least 64 bits.");

  namespace mcal
  {
    auto init() -> void;
  } // namespace mcal

#endif // MCAL_2011_10_20_H
