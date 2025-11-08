///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>

namespace sys { namespace idle {

auto task_init() -> void;
auto task_func() -> void;

} // namespace idle
} // namespace sys

auto sys::idle::task_init() -> void { }

auto sys::idle::task_func() -> void
{
  // Service the watchdog.
  mcal::wdg::secure::trigger();
}
