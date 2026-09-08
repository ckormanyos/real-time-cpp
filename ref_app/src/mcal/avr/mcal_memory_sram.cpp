///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_memory_sram.h>

auto mcal::memory::sram::mcal_memory_sram_device() -> mcal::memory::sram::mcal_memory_sram_device_type&
{
  static mcal_memory_sram_device_type my_device;

  return my_device;
}
