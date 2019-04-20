///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter08_02-003_static_init_data.cpp

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>

// Structure for simulated .data and .rodata sections.
typedef struct simulated_data_type
{
  std::uint8_t _data[16U];
}
simulated_data_type;

static const simulated_data_type simulated_rodata =
{
  0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U,
  0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU
};

static simulated_data_type simulated_data;

void init_data()
{
  // Calculate the size of the data section.
  const std::size_t count = sizeof(simulated_data._data);

  // Copy the rodata section to the data section.
  std::copy(&simulated_rodata._data[0U],
            &simulated_rodata._data[0U] + count,
            &simulated_data._data[0U]);
}

int main()
{
  std::cout << "simulated_data._data before initialization:\n";

  for(std::size_t i = 0U; i < sizeof(simulated_data._data); ++i)
  {
    std::cout << "0x"
              << std::hex
              << std::setw(2)
              << std::setfill(char('0'))
              << std::uppercase
              << static_cast<std::uint32_t>(simulated_data._data[i])
              << ", ";
  }
  std::cout << std::endl;

  init_data();

  std::cout << "simulated_data._data after initialization:\n";

  for(std::size_t i = 0U; i < sizeof(simulated_data._data); ++i)
  {
    std::cout << "0x"
              << std::hex
              << std::setw(2)
              << std::setfill(char('0'))
              << std::uppercase
              << static_cast<std::uint32_t>(simulated_data._data[i])
              << ", ";
  }
  std::cout << std::endl;
}
