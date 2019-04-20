///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_16-001_operator_new.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>

std::uint8_t* local_buffer { nullptr };

void do_something()
{
  // Allocate 32 bytes for local_buffer
  // using global operator new.
  // This allocation might be problematic.

  local_buffer = new std::uint8_t[32U];

  std::fill(local_buffer,
            local_buffer + 32U,
            0x55U);
}

void cleanup()
{
  // Cleanup the local_buffer memory
  // using global operator delete.
  delete [] local_buffer;

  local_buffer = nullptr;
}

int main()
{
  do_something();

  std::cout << std::hex
            << "local_buffer[0U]: 0x"
            << static_cast<unsigned>(local_buffer[0U])
            << std::endl;

  cleanup();
}
