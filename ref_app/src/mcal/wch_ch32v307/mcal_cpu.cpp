///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

#include <CH32V30xxx.h>

void mcal::cpu::init()
{
  /* enable both the global interrupt flag and the FPU */
  asm volatile("li x1, 0x2008");
  asm volatile("csrw mstatus, x1");

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
