/////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_21-001_span.cpp

#include <cstdint>
#include <iostream>
#include <iterator>
#include <span>

void clear_buffer(std::span<std::uint8_t> pb)
{
  for(auto u : pb)
  {
    u = static_cast<std::uint8_t>(UINT8_C(0));

    static_cast<void>(u);
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
  // 0
  std::cout << unsigned(*(std::cend(legacy_buffer) - 1U)) << std::endl;
}
