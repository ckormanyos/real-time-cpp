///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>

#include "BL602.h"

namespace local
{
  constexpr std::uint64_t TIMEOUT_1S { UINT64_C(10000000) };

  auto gpt_is_initialized() -> bool& __attribute__((used, noinline));

  auto get_consistent_tick
  {
    []()
    {
      // Return the system tick using a multiple read to ensure data consistency.

      const volatile std::uint64_t time_first  { CLIC_MTIME };
      const volatile std::uint64_t time_second { CLIC_MTIME };

      const bool
        is_steady
        {
          (static_cast<std::uint32_t>(time_second) >= static_cast<std::uint32_t>(time_first))
        };

      return
        static_cast<mcal::gpt::value_type>
        (
          is_steady ? time_first : CLIC_MTIME
        );
    }
  };

  auto gpt_is_initialized() -> bool&
  {
    static bool is_init { };

    return is_init;
  }
} // namespace local

extern "C" auto mcal_gpt_init() -> void;

extern "C" auto mcal_gpt_init() -> void
{
}

auto mcal::gpt::init(const config_type*) -> void { }

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  if(!local::gpt_is_initialized())
  {
    // Set the is-initialized indication flag.
    local::gpt_is_initialized() = true;
  }

  // Convert the consistent tick to microseconds.
  return
    static_cast<mcal::gpt::value_type>
    (
      static_cast<mcal::gpt::value_type>
      (
          static_cast<mcal::gpt::value_type>(local::get_consistent_tick() + UINT32_C(5))
        / UINT32_C(10)
      )
    );
}
