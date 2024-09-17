///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

namespace local
{
  auto core_1_run_flag() -> bool&;

  auto core_1_run_flag() -> bool&
  {
    static bool run_flag { false };

    return run_flag;
  }
}

extern "C"
{
  auto core_1_run_flag_set(bool setting) -> void;
  auto core_1_run_flag_get(void) -> bool;

  auto core_1_run_flag_set(bool setting) -> void
  {
    local::core_1_run_flag() = setting;
  }

  auto core_1_run_flag_get(void) -> bool
  {
    const bool result { local::core_1_run_flag() };

    return result;
  }
}
