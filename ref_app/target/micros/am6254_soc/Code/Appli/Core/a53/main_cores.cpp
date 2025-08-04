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

extern "C" void main_core1(void);
extern "C" void main_core2(void);
extern "C" void main_core3(void);

extern "C" void main_core1(void) { using namespace mcal::led; led_am6254_soc<LED_2>::main_core_worker(); }
extern "C" void main_core2(void) { using namespace mcal::led; led_am6254_soc<LED_3>::main_core_worker(); }
extern "C" void main_core3(void) { using namespace mcal::led; led_am6254_soc<LED_4>::main_core_worker(); }
