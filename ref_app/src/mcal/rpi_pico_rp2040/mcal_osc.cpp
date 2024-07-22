///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_osc.h>

extern "C"
void RP2040_ClockInit(void);

extern "C"
void Startup_InitSystemClock(void);

extern "C"
void Startup_InitSystemClock(void)
{
  ::RP2040_ClockInit();
}

void mcal::osc::init(const config_type*)
{
  ::Startup_InitSystemClock();
}
