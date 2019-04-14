///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_02-002_static_init_bss.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>

// Structure for simulated .bss section.
typedef struct simulated_bss_type
{
  std::uint8_t _bss[16U];
}
simulated_bss_type;

static simulated_bss_type simulated_bss;

void init_bss()
{
  // Clear the bss segment.
  std::fill(&simulated_bss._bss[0U],
            &simulated_bss._bss[0U] + sizeof(simulated_bss._bss),
            0U);
}

int main()
{
  init_bss();

  std::cout << "simulated_bss._bss[0U]: "
    << static_cast<std::uint32_t>(simulated_bss._bss[0U])
    << std::endl;
}
