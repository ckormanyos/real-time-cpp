///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_gpt.h>

#include <util/utility/util_noncopyable.h>

extern "C"
{
  extern int64_t esp_timer_get_time();
}

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

    static std::uint64_t get_consistent_microsecond_tick()
    {
      // Return the (elapsed) system tick using a function from
      // the Espressif SDK. The system tick representing
      // the elapsed time is used because the system tick timer
      // has already been initialized by the SDK initialization.
      // This means that by the time the bare-metal software actually
      // starts up, the system tick timer will have already increased
      // to some non-zero value represented here by initial_count.

      return (std::uint64_t) ::esp_timer_get_time();
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
  if(!gpt_is_initialized())
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
