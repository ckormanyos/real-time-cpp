
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg.h>

#include <util/utility/util_noncopyable.h>
#include <util/utility/util_two_part_data_manipulation.h>

namespace
{
  mcal::gpt::value_type mcal_gpt_system_tick_initial_count;

  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }

  struct mcal_gpt_system_tick final : private util::noncopyable
  {
  private:
    static std::uint32_t lo() {  return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system_timer_clo>::reg_get(); }
    static std::uint32_t hi() {  return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system_timer_chi>::reg_get(); }

  public:
    static std::uint64_t get_tick()
    {
      // Return the system tick using a multiple read to ensure data consistency.

      const std::uint32_t lo0 = lo();
      const std::uint32_t hi0 = hi();
      const std::uint32_t lo1 = lo();

      const std::uint64_t consistent_microsecond_tick =
        ((lo1 >= lo0) ? util::make_long(lo0, hi0) : util::make_long(lo1, hi()));

      return consistent_microsecond_tick;
    }
  };
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    mcal_gpt_system_tick_initial_count = mcal_gpt_system_tick::get_tick();
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  const std::uint64_t elapsed =
    (gpt_is_initialized() ? std::uint64_t(mcal_gpt_system_tick::get_tick() - mcal_gpt_system_tick_initial_count)
                          : UINT64_C(0));

  return mcal::gpt::value_type(elapsed);
}
