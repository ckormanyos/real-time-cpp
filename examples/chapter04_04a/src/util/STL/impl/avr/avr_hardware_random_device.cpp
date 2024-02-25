///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <random>

#include <math/checksums/crc/crc32.h>
#include <mcal_gpt.h>
#include <util/utility/util_time.h>
#include <util/utility/util_two_part_data_manipulation.h>

auto my_hardware_random_device_generator(void) -> unsigned int
{
  using timer_type = util::timer<std::uint64_t>;

  const auto t_now = timer_type::get_mark();

  const auto pseudo_random1 =
    math::checksums::crc::crc32_mpeg2
    (
      reinterpret_cast<const std::uint8_t*>(&t_now),
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint32_t)
    );

  const auto pseudo_random2 =
    math::checksums::crc::crc32_mpeg2
    (
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint32_t),
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint64_t)
    );

  return static_cast<unsigned int>(util::make_long(pseudo_random1, pseudo_random2));
}

extern "C" unsigned char my_hardware_random_device_entropy(void)
{
  return 1U;
}
