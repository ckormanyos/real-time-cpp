///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_2011_10_20_H_
  #define MCAL_2011_10_20_H_

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

  static_assert(   (std::numeric_limits<mcal::gpt::value_type>::digits >= 32)
                && (std::numeric_limits<mcal::gpt::value_type>::is_integer == true)
                && (std::numeric_limits<mcal::gpt::value_type>::is_signed  == false),
                "The gpt value type must be an unsigned integer type having at least 32 bits.");

  namespace mcal
  {
    void init();
  }

#endif // MCAL_2011_10_20_H_
