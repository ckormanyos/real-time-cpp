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
const volatile std::uint8_t option_bytes[4U] __attribute__((section(".opt")));

extern "C"
const volatile std::uint8_t option_bytes[4U] __attribute__((section(".opt"))) =
{
  0x6E,
  0xFF,
  0xE8,
  0x85
};
