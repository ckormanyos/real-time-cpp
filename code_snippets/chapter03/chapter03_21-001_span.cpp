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

#define LEGACY_BUFFER_LENGTH 64U

std::uint8_t legacy_buffer[LEGACY_BUFFER_LENGTH];

void do_something()
{
  clear_buffer(legacy_buffer);
}

int main()
{
  std::span<std::uint8_t> buffer_span(legacy_buffer);

  // First off, fill the legacy buffer with a pattern.
  std::fill(buffer_span.begin(), buffer_span.end(), UINT8_C(0x5A));

  std::stringstream strm { };

  // Ensure that the buffer has the pattern.
  strm << "filled:  " << std::hex << std::uppercase << std::setw(std::streamsize { 2 }) << std::setfill('0') << unsigned(buffer_span.back());

  // Now clear the buffer and the buffer has been cleared to 0.
  do_something(buffer_span);
  strm << "\ncleared: " << std::hex << std::uppercase << std::setw(std::streamsize { 2 }) << std::setfill('0') << unsigned(buffer_span.back());

  std::cout << strm.str() << std::endl;
}
