///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_2011_10_20_H_
  #define _MCAL_2011_10_20_H_

  #include <mcal_reg_access.h>
  #include <mcal_cpu.h>
  #include <mcal_gpt.h>
  #include <mcal_irq.h>
  #include <mcal_led.h>
  #include <mcal_wdg.h>

  static_assert(   (std::numeric_limits<mcal::gpt::value_type>::digits >= 32)
                && (std::numeric_limits<mcal::gpt::value_type>::is_integer == true)
                && (std::numeric_limits<mcal::gpt::value_type>::is_signed  == false),
                "the gpt value type must be an unsigned integer type having at least 32 bits");

  namespace mcal
  {
    void init();
  }

#endif // _MCAL_2011_10_20_H_
