///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

extern "C"
const volatile std::uint32_t configuration_dwords[4U] __attribute__((section(".config")));

extern "C"
const volatile std::uint32_t configuration_dwords[4U] =
{
  UINT32_C(0xFFFFFFFF), // config at 0xBFC02FF0: TBD: Describe the meanings of the bits.
  UINT32_C(0xFFF97FD9), // config at 0xBFC02FF4: TBD: Describe the meanings of the bits.
  UINT32_C(0xFF7FCB59), // config at 0xBFC02FF8: TBD: Describe the meanings of the bits.
  UINT32_C(0x7FFFFFF6), // config at 0xBFC02FFC: TBD: Describe the meanings of the bits.
};

namespace crt
{
  bool do_not_optimize_the_config_dwords_away();

  bool do_not_optimize_the_config_dwords_away()
  {
    return (configuration_dwords[3U] != UINT32_C(0));
  }
}
