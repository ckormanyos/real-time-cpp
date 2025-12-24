///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PI_CALC_CFG_2023_05_09_H
  #define PI_CALC_CFG_2023_05_09_H

  // In this embedded software adaptation of this work,
  // we limit the decimal digit count to about 100k or fewer.

  #define PI_CRUNCH_METAL_PI_SPIGOT_USE_100_DIGITS      100
  #define PI_CRUNCH_METAL_PI_SPIGOT_USE_1K_DIGITS      1000
  #define PI_CRUNCH_METAL_PI_SPIGOT_USE_10K_DIGITS    10000
  #define PI_CRUNCH_METAL_PI_SPIGOT_USE_100K_DIGITS  100000

  #if !defined(PI_CRUNCH_METAL_PI_SPIGOT_DIGITS)
  #define PI_CRUNCH_METAL_PI_SPIGOT_DIGITS  PI_CRUNCH_METAL_PI_SPIGOT_USE_10K_DIGITS
  #endif

#endif // PI_CALC_CFG_2023_05_09_H
