///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <random>

#include <math/wide_integer/miller_rabin/miller_rabin_state.h>
#include <mcal_benchmark.h>
#include <mcal_math_independent_test_system.h>
#include <mcal_lcd.h>
#include <mcal_random.h>
#include <sys/idle/sys_idle_miller_rabin.h>
#include <util/utility/util_baselexical_cast.h>
#include <util/utility/util_narrow_cast.h>
#include <util/utility/util_time.h>

namespace
{
  using sys_idle_miller_rabin_uint_type           = math::wide_integer::uintwide_t<math::wide_integer::size_t(128U), std::uint16_t>;

  using sys_idle_miller_rabin_random_engine1_type = mcal::random::default_random_engine;
  using sys_idle_miller_rabin_random_engine2_type = std::minstd_rand;

  using sys_idle_miller_rabin_miller_rabin_type   = math::wide_integer::miller_rabin_state<sys_idle_miller_rabin_random_engine1_type,
                                                                                           sys_idle_miller_rabin_random_engine2_type,
                                                                                           sys_idle_miller_rabin_uint_type::my_width2,
                                                                                           typename sys_idle_miller_rabin_uint_type::limb_type>;

  constexpr std::uint_fast8_t sys_idle_miller_rabin_prime_width_base16
                                                  = util::narrow_cast<std::uint_fast8_t>(std::numeric_limits<sys_idle_miller_rabin_uint_type>::digits / 4);

  using sys_idle_miller_rabin_gen1_result_type    = typename sys_idle_miller_rabin_miller_rabin_type::generator1_type::result_type;

  using sys_idle_miller_rabin_str_result_type     = std::array<char, sys_idle_miller_rabin_prime_width_base16 + 1U>;

  sys_idle_miller_rabin_miller_rabin_type           sys_idle_miller_rabin_object(util::timer<sys_idle_miller_rabin_gen1_result_type>::get_mark());

  std::uint64_t                                     sys_idle_miller_rabin_number_of_primes;

  sys_idle_miller_rabin_str_result_type             sys_idle_miller_rabin_str_result;

}

bool sys::idle::miller_rabin_result_is_ok = true;

void sys::idle::miller_rabin_run()
{
  mcal::benchmark::benchmark_port_type::set_pin_high();

  if(sys_idle_miller_rabin_object.search())
  {
    if(sys_idle_miller_rabin_object.get_n_is_probably_prime())
    {
      ++sys_idle_miller_rabin_number_of_primes;

      // Write the total number of primes to the LCD.
      {
        sys_idle_miller_rabin_str_result.fill(util::narrow_cast<char>('\0'));

        const char* p_end = util::baselexical_cast(sys_idle_miller_rabin_number_of_primes, sys_idle_miller_rabin_str_result.data());

        mcal::lcd::lcd0().write(sys_idle_miller_rabin_str_result.data(),
                                util::narrow_cast<std::uint_fast8_t>(p_end - sys_idle_miller_rabin_str_result.data()),
                                1U);
      }

      // Write the average number of trials to the LCD.
      {
        sys_idle_miller_rabin_str_result.fill(static_cast<char>('\0'));

        const std::uint32_t set_n_average =
          util::narrow_cast<std::uint32_t>(  sys_idle_miller_rabin_miller_rabin_type::get_n_total_mul_10()
                                           / sys_idle_miller_rabin_number_of_primes);

        const char* p_end = util::baselexical_cast(set_n_average, sys_idle_miller_rabin_str_result.data());

        std::uint_fast8_t str_result_size =
          util::narrow_cast<std::uint_fast8_t>(p_end - sys_idle_miller_rabin_str_result.data());

        if(str_result_size == 0U)
        {
          sys_idle_miller_rabin_str_result.at(0U) = util::narrow_cast<char>('\0');
          sys_idle_miller_rabin_str_result.at(1U) = util::narrow_cast<char>('.');
          sys_idle_miller_rabin_str_result.at(2U) = util::narrow_cast<char>('\0');

          str_result_size = 2U;
        }
        else if(str_result_size == 1U)
        {
          const char c0_tmp = sys_idle_miller_rabin_str_result.at(0U);

          sys_idle_miller_rabin_str_result.at(0U) = util::narrow_cast<char>('\0');
          sys_idle_miller_rabin_str_result.at(1U) = util::narrow_cast<char>('.');
          sys_idle_miller_rabin_str_result.at(2U) = c0_tmp;

          str_result_size = 2U;
        }
        else
        {
          const char c0_tmp = sys_idle_miller_rabin_str_result.at(str_result_size - 1U);

          sys_idle_miller_rabin_str_result.at(str_result_size - 1U) = util::narrow_cast<char>('.');
          sys_idle_miller_rabin_str_result.at(str_result_size)      = c0_tmp;
        }

        mcal::lcd::lcd1().write(sys_idle_miller_rabin_str_result.data(),
                                std::uint_fast8_t(str_result_size + UINT8_C(1)),
                                0U);
      }

      // Get the hexadecimal uppercase representation of the prime number.
      sys_idle_miller_rabin_object.get_n().wr_string(sys_idle_miller_rabin_str_result.data(),
                                                     16U,
                                                     false,
                                                     false,
                                                     true,
                                                     sys_idle_miller_rabin_prime_width_base16);

      // Write the prime number to the LCD.
      sys::idle::miller_rabin_result_is_ok &=
        mcal::lcd::lcd0().write(sys_idle_miller_rabin_str_result.data(),
                                sys_idle_miller_rabin_prime_width_base16,
                                0U);

      // Test with a computer algebra system (if one is available).
      // For he embedded target, there is probably no computer algebra
      // system available. For other systems, a well-known computer
      // algebra system could verify primality with a command such as:
      // PrimeQ[FromDigits["A6BAC43FEE73E832401B1E32417BD0AF",16]]
      // (taken from the Wolfram Language (R)).

      // For an online test, query at WolframAlpha(R) with the command:
      // 0xA6BAC43FEE73E832401B1E32417BD0AF
      // then obtain the decimal representation and subsequently use:
      // PrimeQ[221621594933437622289711363577043734703]

      sys::idle::miller_rabin_result_is_ok &=
        ::mcal::math::independent_test_system0().is_prime(sys_idle_miller_rabin_str_result.data());

      // Re-seed one of each of the generators after each new prime.
      {
        const bool reseed_is_even =
          (util::narrow_cast<std::uint_fast8_t>(sys_idle_miller_rabin_number_of_primes & 1U) != 0U);

        if(reseed_is_even)
        {
          using local_gen1_seed_type =
            typename sys_idle_miller_rabin_miller_rabin_type::generator1_type::result_type;

          sys_idle_miller_rabin_object.reseed1(util::timer<local_gen1_seed_type>::get_mark());
        }
        else
        {
          using local_gen2_seed_type =
            typename sys_idle_miller_rabin_miller_rabin_type::generator2_type::result_type;

          sys_idle_miller_rabin_object.reseed2(util::timer<local_gen2_seed_type>::get_mark());
        }
      }
    }
  }

  mcal::benchmark::benchmark_port_type::set_pin_low();
}
