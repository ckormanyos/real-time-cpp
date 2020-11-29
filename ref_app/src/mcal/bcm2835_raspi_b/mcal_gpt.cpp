///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
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
  struct mcal_gpt_system_tick final : private util::noncopyable
  {
  public:
    mcal_gpt_system_tick() = delete;

    ~mcal_gpt_system_tick() = delete;

    static void init()
    {
      initial_count = get_consistent_microsecond_tick();
    }

    static std::uint64_t get_tick()
    {
      const std::uint64_t elapsed = get_consistent_microsecond_tick() - initial_count;

      return elapsed;
    }

  private:
    static std::uint64_t initial_count;

    static std::uint32_t lo() {  return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system_timer_clo>::reg_get(); }
    static std::uint32_t hi() {  return mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system_timer_chi>::reg_get(); }

    static std::uint64_t get_consistent_microsecond_tick()
    {
      // Return the (elapsed) system tick using a multiple read
      // to ensure data consistency. The system tick representing
      // the elapsed time is used because the system tick timer
      // has already been initialized by the Raspberry Pi's bootloader.
      // This means that by the time the bare-metal software actually
      // starts up, the system tick timer will have already increased
      // to some non-zero value represented here by initial_count.

      // Since we have no information on the detailed ticking order
      // of clo and chi, we read the high counter and the low conter
      // in the hopes that a consistent 64-bit tick has been obtained.

      // Do the first read of the low counter and the high conter.
      const std::uint32_t clo_1 = lo();
      const std::uint32_t chi_1 = hi();

      // Do the second read of the high counter.
      const std::uint32_t clo_2 = lo();

      // Perform a consistency check.
      const mcal::gpt::value_type consistent_microsecond_tick =
        ((clo_2 > clo_1) ? util::make_long(clo_1, chi_1)
                         : util::make_long(clo_2, hi()));

      return consistent_microsecond_tick;
    }
  };

  std::uint64_t mcal_gpt_system_tick::initial_count;

  bool& gpt_is_initialized() __attribute__((used, noinline));

  bool& gpt_is_initialized()
  {
    static bool is_init = bool();

    return is_init;
  }
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    mcal_gpt_system_tick::init();
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  const std::uint64_t elapsed = (gpt_is_initialized() ? mcal_gpt_system_tick::get_tick() : UINT64_C(0));

  return mcal::gpt::value_type(elapsed);
}
