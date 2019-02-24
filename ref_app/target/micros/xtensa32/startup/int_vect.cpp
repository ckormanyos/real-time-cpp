///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>

extern "C"
const volatile std::array<std::uint32_t, 1U> __isr_vector __attribute__((section(".isr_vector")));

extern "C"
const volatile std::array<std::uint32_t, 1U> __isr_vector =
{{
  0U // dummy
}};
