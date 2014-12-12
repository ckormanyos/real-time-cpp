
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//#define CFG_USE_APP_BENCHMARK_CPU

#if defined(CFG_USE_APP_BENCHMARK_CPU)

  #include <mcal_benchmark.h>
  #include <util/utility/util_time.h>

  #define CFG_APP_BENCHMARK_CPU_TYPE_MD5     1
  #define CFG_APP_BENCHMARK_CPU_TYPE_SHA1    2
  #define CFG_APP_BENCHMARK_CPU_TYPE_SHA224  3
  #define CFG_APP_BENCHMARK_CPU_TYPE_SHA256  4
  #define CFG_APP_BENCHMARK_CPU_TYPE_SHA384  5
  #define CFG_APP_BENCHMARK_CPU_TYPE_SHA512  6

//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_MD5
//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_SHA1
//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_SHA224
//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_SHA256
//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_SHA384
//  #define CFG_APP_BENCHMARK_CPU_TYPE CFG_APP_BENCHMARK_CPU_TYPE_SHA512

  #if(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_MD5)
    #include <math/checksums/hash/md5.h>
    typedef md5   <std::uint8_t> hash_type;
    const std::uint32_t control_value = UINT32_C(0x09191D4F);
  #elif(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_SHA1)
    #include <math/checksums/hash/sha1.h>
    typedef sha1  <std::uint8_t> hash_type;
    const std::uint32_t control_value = UINT32_C(0x8029201C);
  #elif(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_SHA224)
    #include <math/checksums/hash/sha224.h>
    typedef sha224<std::uint8_t> hash_type;
    const std::uint32_t control_value = UINT32_C(0xB34E7f65);
  #elif(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_SHA256)
    #include <math/checksums/hash/sha256.h>
    typedef sha256<std::uint8_t> hash_type;
    const std::uint32_t control_value = UINT32_C(0x5A59225B);
  #elif(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_SHA384)
    #include <math/checksums/hash/sha384.h>
    typedef sha384<std::uint8_t> hash_type;
    const std::uint64_t control_value = UINT64_C(0x8BB184C5851558CA);
  #elif(CFG_APP_BENCHMARK_CPU_TYPE == CFG_APP_BENCHMARK_CPU_TYPE_SHA512)
    #include <math/checksums/hash/sha512.h>
    typedef sha512<std::uint8_t> hash_type;
    const std::uint64_t control_value = UINT64_C(0x3F7E0479733B7E33);
  #else
    #error Cryptographic benchmark type is undefined (CFG_APP_BENCHMARK_CPU_TYPE)
  #endif

  namespace
  {
    hash_type the_hash;

    hash_type::result_type_as_integral_values the_hash_result;

    typedef util::timer<std::uint32_t> timer_type;

    timer_type            app_benchmark_cpu_timer;
    timer_type::tick_type app_benchmark_cpu_timing_result;
  }

  bool app_benchmark_cpu_the_result_is_ok = true;

#endif

namespace app
{
  namespace benchmark
  {
    namespace cpu
    {
      void task_init();
      void task_func();
    }
  }
}

void app::benchmark::cpu::task_init()
{
  #if defined(CFG_USE_APP_BENCHMARK_CPU)

  mcal::benchmark::benchmark_port_type::set_direction_output();

  #endif
}

void app::benchmark::cpu::task_func()
{
  #if defined(CFG_USE_APP_BENCHMARK_CPU)

  app_benchmark_cpu_timer.set_mark();

  mcal::benchmark::benchmark_port_type::set_pin_high();

  the_hash.process_data("creativity", hash_type::count_type(10U));

  the_hash_result = the_hash.get_result_as_integral_values_and_finalize_the_state();

  if(app_benchmark_cpu_the_result_is_ok)
  {
    mcal::benchmark::benchmark_port_type::set_pin_low();
    app_benchmark_cpu_timing_result = app_benchmark_cpu_timer.get_ticks_since_mark();
  }

  app_benchmark_cpu_the_result_is_ok = (the_hash_result.front() == control_value);

  #endif
}
