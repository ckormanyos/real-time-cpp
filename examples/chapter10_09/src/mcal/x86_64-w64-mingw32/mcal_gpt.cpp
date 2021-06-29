///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstdint>
#include <thread>

#include <mcal_gpt.h>

namespace
{
  using mcal_gpt_time_point_type =
    std::chrono::high_resolution_clock::time_point;

  const mcal_gpt_time_point_type& mcal_gpt_time_point_init()
  {
    static const mcal_gpt_time_point_type init =
      std::chrono::high_resolution_clock::now();

    return init;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  const std::chrono::microseconds duration_in_microseconds =
    std::chrono::duration_cast<std::chrono::microseconds>
      (std::chrono::high_resolution_clock::now() - mcal_gpt_time_point_init());

  // Return the system tick with a resolution of 1us.
  return static_cast<mcal::gpt::value_type>(duration_in_microseconds.count());
}
