///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

namespace local
{
  auto core_1_run_flag() noexcept -> bool&;

  auto core_1_run_flag() noexcept -> bool&
  {
    static bool run_flag { };

    return run_flag;
  }
}

extern "C"
{
  auto core_1_run_flag_set(bool setting) noexcept -> void;
  auto core_1_run_flag_get() noexcept -> bool;

  auto core_1_run_flag_set(bool setting) noexcept -> void
  {
    local::core_1_run_flag() = setting;
  }

  auto core_1_run_flag_get() noexcept -> bool
  {
    const bool result { local::core_1_run_flag() };

    return result;
  }
}
