///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

void mcal::cpu::post_init()
{
}
