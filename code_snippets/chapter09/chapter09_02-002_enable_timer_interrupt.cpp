///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter09_02-002_enable_timer_interrupt.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

template<typename addr_type,
         typename reg_type>
struct reg_access_dynamic final
{
  static auto reg_get(const addr_type address) -> reg_type { return *reinterpret_cast<volatile reg_type*>(address); }

  static auto reg_set(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address)  = value; }
  static auto reg_and(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) &= value; }
  static auto reg_or (const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) |= value; }
  static auto reg_not(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) &= reg_type(~value); }
  static auto reg_msk(const addr_type address, const reg_type value,
                      const reg_type mask_value)                     -> void { *reinterpret_cast<volatile reg_type*>(address) = reg_type(reg_type(reg_get(address) & reg_type(~mask_value)) | reg_type(value & mask_value)); }

  static auto bit_set(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) |= static_cast<reg_type>(1UL << value); }
  static auto bit_clr(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << value)); }
  static auto bit_not(const addr_type address, const reg_type value) -> void { *reinterpret_cast<volatile reg_type*>(address) ^= static_cast<reg_type>(1UL << value); }
  static auto bit_get(const addr_type address, const reg_type value) -> bool { return (static_cast<volatile reg_type>(reg_get(address) & static_cast<reg_type>(1UL << value)) != static_cast<reg_type>(0U)); }
};

// The simulated timsk0 register.
std::uint8_t simulated_register_timsk0 { };

const std::uintptr_t simulated_address
  { reinterpret_cast<std::uintptr_t>(&simulated_register_timsk0) };

auto do_something() -> void;

auto do_something() -> void
{
  // Simulated: Enable the timer0 compare-match interrupt.
  reg_access_dynamic<std::uintptr_t,
                     std::uint8_t>::reg_set(simulated_address, UINT8_C(0x02));
}

auto main() -> int;

auto main() -> int
{
  do_something();

  std::cout << "simulated_register_timsk0: 0x"
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << std::uint32_t(simulated_register_timsk0) << std::endl;
}
