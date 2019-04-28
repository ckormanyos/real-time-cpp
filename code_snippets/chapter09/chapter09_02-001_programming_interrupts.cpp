///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_02-001_programming_interrupts.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

extern "C"
void __vector_simulated_timer(void)
{
  std::cout << "we are in: system__vector_simulated_timer()" << std::endl;
}

extern "C" void __unused_simulated_isr();

// The simulated unused interrupt handler.
extern "C" void __unused_simulated_isr(void)
{
  // Generate a loud error.
  std::cout << "we are in: __unused_simulated_isr()" << std::endl;
}

using simulated_isr_type = void(*)(void);

std::array<simulated_isr_type, 4U> simulated_isr_vectors
{{
  __unused_simulated_isr,
  __unused_simulated_isr,
  __vector_simulated_timer,
  __unused_simulated_isr,
}};

int main()
{
  std::for_each(simulated_isr_vectors.cbegin(),
                simulated_isr_vectors.cend(),
                [](const simulated_isr_type& pfn)
                {
                  pfn();
                });
}
