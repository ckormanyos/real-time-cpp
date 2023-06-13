///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>

#include <mcal_gpt.h>

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  // Return the system tick with a resolution of 1us.
  const auto epoch_now_micro_sec =
    std::chrono::duration_cast<std::chrono::microseconds>
    (
      std::chrono::high_resolution_clock::now().time_since_epoch()
    );

  return static_cast<mcal::gpt::value_type>(epoch_now_micro_sec.count());
}
