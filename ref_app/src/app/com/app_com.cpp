///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spi.h>

#include <util/utility/util_random_pcg32.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace com
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  using random_engine_type = util::random_pcg32_fast;

  random_engine_type app_com_random_device;

  std::uint16_t app_com_random_counter;
}

void app::com::task_init()
{
  app_com_random_device.seed(util::timer<std::uint64_t>::get_mark());
}

void app::com::task_func()
{
  ++app_com_random_counter;

  if(app_com_random_counter == 10000U)
  {
    app_com_random_counter = 0U;

    app_com_random_device.seed(util::timer<std::uint64_t>::get_mark());
  }

  const random_engine_type::result_type app_com_random_value32 = app_com_random_device();

  mcal::spi::spi0().send(static_cast<std::uint8_t>(app_com_random_value32));
}
