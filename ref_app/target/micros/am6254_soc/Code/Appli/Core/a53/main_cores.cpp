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

extern "C" void main_core1(void) { using local_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_2>; mcal::led::led_am6254_soc<local_port_type>::main_core_worker(); }
extern "C" void main_core2(void) { using local_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_3>; mcal::led::led_am6254_soc<local_port_type>::main_core_worker(); }
extern "C" void main_core3(void) { using local_port_type = mcal::port::port_pin<mcal::reg::gpio0, mcal::led::LED_4>; mcal::led::led_am6254_soc<local_port_type>::main_core_worker(); }
