///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
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
  void init();

  // The general purpose timer stuff in the mcal.
  namespace gpt
  {
    void init() { std::cout << "in gpt::init()" << std::endl; }

    std::uint32_t get_time_elapsed() { return UINT32_C(0); }
  }

  // The ADC stuff in the mcal.
  namespace adc
  {
    void init() { std::cout << "in adc::init()" << std::endl; }

    std::uint16_t read_value(const unsigned) { return UINT16_C(0); }
  }
}

// Initialize the mcal.
// Note the clean organization with namespaces.
void mcal::init()
{
  mcal::gpt::init();
  mcal::adc::init();
}

int main()
{
  mcal::init();
}
