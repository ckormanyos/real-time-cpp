///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>

namespace
{
  void set_the_system_clock()
  {
    // Do nothing.
    // TBD: Is this correct for 32MHz clock?
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 32MHz.
  set_the_system_clock();
}
