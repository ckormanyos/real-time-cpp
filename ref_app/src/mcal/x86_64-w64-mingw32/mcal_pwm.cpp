///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal_pwm_template.h>
#include <mcal_port.h>

namespace
{
  using pwm_type = mcal::pwm::pwm_template<mcal::port::port_pin, 255U>;

  pwm_type pwm0;
  pwm_type pwm1;
}
