///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include "util_time.h"

mcal::gpt::value_type util::timer_base::my_now()
{
  typedef std::chrono::high_resolution_clock clock_type;

  // Return the elapsed time count computed from now() and the initial zero time.
  return std::uint32_t(std::chrono::duration_cast<std::chrono::microseconds>(clock_type::now() - clock_type::time_point()).count());
}
