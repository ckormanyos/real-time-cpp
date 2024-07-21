///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

extern "C"
{
  extern void RP2040_InitCore(void);

  static void Startup_InitCore(void);

  static void Startup_InitCore(void)
  {
    ::RP2040_InitCore();
  }
}

void mcal::cpu::init()
{
  ::Startup_InitCore();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
