/////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Repaired in: https://github.com/ckormanyos/real-time-cpp/issues/658

// chapter03_21-001_span.cpp

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <span>
#include <sstream>

namespace
{
  void clear_buffer(std::span<std::uint8_t> buf)
  {
    for(auto& next_byte : buf)
    {
      next_byte = static_cast<std::uint8_t>(UINT8_C(0));
    }
  }
}

#define LEGACY_BUF_LEN 64U

std::uint8_t legacy_buffer[LEGACY_BUF_LEN];

void do_something()
{
  std::span<std::uint8_t> buf_span(legacy_buffer);

  // First off, fill the legacy buffer with a pattern.
  std::fill(buf_span.begin(), buf_span.end(), UINT8_C(0x5A));

  std::stringstream strm { };

  // Ensure that the buffer has the pattern.
  strm << "filled:  " << std::hex << std::uppercase << std::setw(std::streamsize { 2 }) << std::setfill('0') << unsigned(buf_span.back());

  // Now clear the buffer and the buffer has been cleared to 0.
  clear_buffer(buf_span);

  strm << "\ncleared: " << std::hex << std::uppercase << std::setw(std::streamsize { 2 }) << std::setfill('0') << unsigned(buf_span.back());

  std::cout << strm.str() << std::endl;
}

int main()
{
  do_something();
}
