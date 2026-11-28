///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>

auto mcal::port::init(const config_type*) -> void
{
}

extern "C"
auto port_init(void) -> void;

extern "C"
auto port_init(void) -> void
{
  mcal::port::init(nullptr);
}
