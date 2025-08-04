///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <core_macros.h>
#include <mcal_led_am6254_soc.h>

#include <util/utility/util_time.h>

#include <cstdint>

extern "C" void main_core0(void);
extern "C" void main_core1(void);
extern "C" void main_core2(void);
extern "C" void main_core3(void);

extern "C" void main_core0(void) { mcal::led::main_core_worker<LED_1>(); }
extern "C" void main_core1(void) { mcal::led::main_core_worker<LED_2>(); }
extern "C" void main_core2(void) { mcal::led::main_core_worker<LED_3>(); }
extern "C" void main_core3(void) { mcal::led::main_core_worker<LED_4>(); }
