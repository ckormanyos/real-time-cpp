///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

namespace
{
  // Configuration bytes having byte order:     0 1 2 3.
  constexpr std::uint32_t config3 = UINT32_C(0xFFFFFFFF);
  constexpr std::uint32_t config2 = UINT32_C(0xFFF97FD9);
  constexpr std::uint32_t config1 = UINT32_C(0xFF7FCB59);
  constexpr std::uint32_t config0 = UINT32_C(0x7FFFFFF7);
}

extern "C" volatile const std::uint32_t config3_at_0xBFC02FF0 __attribute__((section(".config3"))) = config3;
extern "C" volatile const std::uint32_t config2_at_0xBFC02FF4 __attribute__((section(".config2"))) = config2;
extern "C" volatile const std::uint32_t config1_at_0xBFC02FF8 __attribute__((section(".config1"))) = config1;
extern "C" volatile const std::uint32_t config0_at_0xBFC02FFC __attribute__((section(".config0"))) = config0;

namespace crt
{
  bool do_not_optimize_the_configuration_away();

  bool do_not_optimize_the_configuration_away()
  {
    // Ensure that the configuration bytes are not optimized away.
    return (   (config3_at_0xBFC02FF0 != UINT32_C(0))
            && (config2_at_0xBFC02FF4 != UINT32_C(0))
            && (config1_at_0xBFC02FF8 != UINT32_C(0))
            && (config0_at_0xBFC02FFC != UINT32_C(0)));
  }
}
