///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Set all debug functions off.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::ddpcon,
                    UINT32_C(0)>::reg_set();

  // Set for multiple interrupt vectors.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::intcon,
                    UINT32_C(12)>::bit_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

namespace crt
{
  bool do_not_optimize_the_configuration_away();
}

void mcal::cpu::post_init()
{
  const volatile bool dummy = crt::do_not_optimize_the_configuration_away();

  static_cast<void>(dummy);
}
