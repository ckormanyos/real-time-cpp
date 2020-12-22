///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_OSC_SHARED_2013_07_09_H_
  #define MCAL_OSC_SHARED_2013_07_09_H_

  #include <cstdint>

  struct mcal_osc_shared
  {
    static constexpr std::uint32_t modulemode_enable = UINT32_C(0x02);
    static constexpr std::uint32_t modulemode_mask   = UINT32_C(0x03);
    static constexpr std::uint32_t idlest_func       = UINT32_C(0x00000000);
    static constexpr std::uint32_t idlest_mask       = UINT32_C(0x00030000);
  };

#endif // MCAL_OSC_SHARED_2013_07_09_H_
