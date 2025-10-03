///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_04-001_namespaces.cpp

#include <cstdint>
#include <iostream>

// Namespace for the microcontroller abstraction layer.
namespace mcal
{
  // The mcal initialization.
  auto init() -> void;

  // The general purpose timer stuff in the mcal.
  namespace gpt
  {
    auto init() -> void { std::cout << "in gpt::init()" << std::endl; }

    auto get_time_elapsed() -> std::uint32_t { return UINT32_C(0); }
  }

  // The ADC stuff in the mcal.
  namespace adc
  {
    auto init() -> void { std::cout << "in adc::init()" << std::endl; }

    auto read_value(const unsigned) -> std::uint16_t { return UINT16_C(0); }
  }
}

// Initialize the mcal.
// Note the clean organization with namespaces.
auto mcal::init() -> void
{
  mcal::gpt::init();
  mcal::adc::init();
}

auto main() -> int
{
  mcal::init();
}
