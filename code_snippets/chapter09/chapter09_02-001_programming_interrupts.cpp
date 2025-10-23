///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_02-001_programming_interrupts.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

extern "C" auto __vector_simulated_timer() -> void;
extern "C" auto __unused_simulated_isr  () -> void;

extern "C" auto __vector_simulated_timer(void) -> void
{
  std::cout << "we are in: system__vector_simulated_timer()" << std::endl;
}

// The simulated unused interrupt handler.
extern "C" auto __unused_simulated_isr() -> void
{
  // Indicate that we are here.
  std::cout << "we are in: __unused_simulated_isr()" << std::endl;
}

using simulated_isr_type = void(*)(void);

std::array<simulated_isr_type, std::size_t { UINT8_C(4) }> simulated_isr_vectors
{{
  __unused_simulated_isr,
  __unused_simulated_isr,
  __vector_simulated_timer,
  __unused_simulated_isr,
}};

auto main() -> int;

auto main() -> int
{
  for(auto& pfn : simulated_isr_vectors)
  {
    if(pfn != nullptr)
    {
      pfn();
    }
  }
}
