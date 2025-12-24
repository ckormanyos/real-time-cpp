///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_2020_04_09_H
  #define MCAL_MEMORY_SRAM_2020_04_09_H

  #include <mcal_memory/mcal_memory_sram_generic_host.h>

  namespace mcal { namespace memory { namespace sram {

  using mcal_memory_sram_device_type =
    mcal_memory_sram_generic_host<static_cast<mcal_sram_uintptr_t>(UINT32_C(0x01000000))>;

  auto mcal_memory_sram_device() -> mcal_memory_sram_device_type&;

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_2020_04_09_H
