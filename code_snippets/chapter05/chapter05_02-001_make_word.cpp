///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_02-001_make_word.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

#define MAKE_WORD(lo, hi) \
          (uint16_t) (((uint16_t) (hi) << 8) | (lo))

#define MAKE_DWORD(lo, hi) \
          (uint32_t) (((uint32_t) (hi) << 16) | (lo))

#define MAKE_QWORD(lo, hi) \
          (uint64_t) (((uint64_t) (hi) << 32) | (lo))

int main()
{
  std::uint8_t  lo8  = UINT8_C(0x34);
  std::uint8_t  hi8  = UINT8_C(0x12);
  std::uint16_t u16
    = MAKE_WORD(lo8, hi8);

  std::uint16_t lo16 = UINT16_C(0x5678);
  std::uint16_t hi16 = UINT16_C(0x1234);
  std::uint32_t u32
    = MAKE_DWORD(lo16, hi16);

  std::uint32_t lo32 = UINT32_C(0x9ABC'DEF0);
  std::uint32_t hi32 = UINT32_C(0x1234'5678);
  std::uint64_t u64
    = MAKE_QWORD(lo32, hi32);

  std::cout << std::hex << std::showbase << std::uppercase << u16 << std::endl;
  std::cout << std::hex << std::showbase << std::uppercase << u32 << std::endl;
  std::cout << std::hex << std::showbase << std::uppercase << u64 << std::endl;
}
