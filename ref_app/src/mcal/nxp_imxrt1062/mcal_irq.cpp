///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_irq.h>

namespace local
{
  using register_address_type = std::uint32_t;
  using register_value_type   = std::uint32_t;
}

extern "C"
{
  extern local::register_address_type __IVT_BASE_ADDRESS;
}

auto mcal::irq::init(const config_type*) noexcept -> void
{
  // Set the VTOR register.
  constexpr auto address = static_cast     <local::register_address_type>(UINT32_C(0xE000ED08));
  const     auto value   = reinterpret_cast<local::register_value_type>  (&__IVT_BASE_ADDRESS);

  volatile local::register_value_type* pa = reinterpret_cast<volatile local::register_value_type*>(address);

  *pa = value;

  // Enable all global interrupts.
  mcal::irq::enable_all();
}
