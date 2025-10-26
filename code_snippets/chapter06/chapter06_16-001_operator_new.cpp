///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_16-001_operator_new.cpp

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>

std::uint8_t* local_buffer { nullptr };

auto do_something() -> void;

auto do_something() -> void
{
  // Allocate 32 bytes for local_buffer
  // using global operator new.
  // This allocation might be problematic.

  local_buffer = new std::uint8_t[std::size_t { UINT8_C(32) }];

  std::fill(local_buffer,
            local_buffer + 32U,
            0x55U);
}

auto cleanup() -> void;

auto cleanup() -> void
{
  // Cleanup the local_buffer memory
  // using global operator delete.
  delete [] local_buffer;

  local_buffer = nullptr;
}

auto main() -> int;

auto main() -> int
{
  do_something();

  std::stringstream strm { };

  strm << "local_buffer[0U]: 0x"
       << std::hex
       << static_cast<unsigned>(local_buffer[0U]);

  std::cout << strm.str() << std::endl;

  cleanup();
}
