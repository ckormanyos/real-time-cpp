///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <random>

#include <math/checksums/crc/crc32.h>
#include <mcal_gpt.h>
#include <util/utility/util_time.h>

extern "C" unsigned int  my_hardware_random_device_generator(void)
{
  using timer_type = util::timer<mcal::gpt::value_type>;

  const timer_type::tick_type t_now = timer_type::get_mark();

  const std::uint32_t pseudo_random =
    math::checksums::crc::crc32_mpeg2( (std::uint8_t*) &t_now,
                                      ((std::uint8_t*) &t_now) + sizeof(timer_type::tick_type));

  return static_cast<unsigned int>(pseudo_random);
}

extern "C" unsigned char my_hardware_random_device_entropy(void)
{
  return 1U;
}
