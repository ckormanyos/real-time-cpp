/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#include <cstdint>

extern "C"
const volatile std::uint8_t option_bytes[4U] __attribute__((section(".opt_bytes")));

extern "C"
const volatile std::uint8_t option_bytes[4U] __attribute__((section(".opt_bytes"))) =
{
  UINT8_C(0x6E),
  UINT8_C(0xFF),
  UINT8_C(0xE8),
  UINT8_C(0x85)
};
