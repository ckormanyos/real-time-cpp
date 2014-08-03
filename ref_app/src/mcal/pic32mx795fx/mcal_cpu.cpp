///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

namespace crt
{
  bool do_not_optimize_the_config_dwords_away();
}

void mcal::cpu::post_init()
{
  const bool dummy_do_not_optimize_the_config_dwords_away = crt::do_not_optimize_the_config_dwords_away();

  static_cast<void>(dummy_do_not_optimize_the_config_dwords_away);
}
