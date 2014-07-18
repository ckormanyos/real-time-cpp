///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#define CFG_USE_APP_BENCHMARK_DSP

namespace app
{
  namespace benchmark
  {
    namespace dsp
    {
      void task_init();
      void task_func();
    }
  }
}

void app::benchmark::dsp::task_init()
{
  #if defined(CFG_USE_APP_BENCHMARK_DSP)

  #endif
}

void app::benchmark::dsp::task_func()
{
  #if defined(CFG_USE_APP_BENCHMARK_DSP)

  #endif
}
