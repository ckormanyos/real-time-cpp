///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#define WIDE_INTEGER_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark.h>
#include <math/wide_integer/generic_template_uintwide_t.h>

namespace
{
  using uint256_t =
    wide_integer::generic_template::uintwide_t<256U, std::uint16_t>;

  static_assert(std::numeric_limits<uint256_t>::digits == 256,
                "Error: Incorrect digit count for this example");

  // Note: Some of the comments in this file use the Wolfram Language(TM).
  //
  // Create two pseudo-random 256-bit unsigned integers.
  //   Table[IntegerString[RandomInteger[(2^256) - 1], 16], 2]
  //
  //   {F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
  //    166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75}
  //
  // Set the values of two random 256-bit unsigned integers.
  //   a = 0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE
  //   b = 0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
  //
  // Multiply:
  //   a * b = 0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076
  //
  // Divide:
  //   a / b = 10
  //
  // Modulus:
  //   a % b = 0x14998D5CA3DB6385F7DEDF4621DE48A9104AC13797C6567713D7ABC216D7AB4C

  const uint256_t a =
    "0xF4DF741DE58BCB2F37F18372026EF9CB"
      "CFC456CB80AF54D53BDEED78410065DE";

  const uint256_t b =
    "0x166D63E0202B3D90ECCEAA046341AB50"
      "4658F55B974A7FD63733ECF89DD0DF75";

  bool run_wide_integer_mul()
  {
    const bool result_of_mul_is_ok =
      ((a * b) == "0xE491A360C57EB4306C61F9A04F7F7D99"
                    "BE3676AAD2D71C5592D5AE70F84AF076");

    return result_of_mul_is_ok;
  }

  bool run_wide_integer_div()
  {
    const bool result_of_div_is_ok =
      ((a / b) == 10U);

    return result_of_div_is_ok;
  }

  bool run_wide_integer_mod()
  {
    const bool result_of_mod_is_ok =
      ((a % b) == "0x14998D5CA3DB6385F7DEDF4621DE48A9"
                    "104AC13797C6567713D7ABC216D7AB4C");

    return result_of_mod_is_ok;
  }
}

bool app::benchmark::run_wide_integer()
{
  static std::uint_fast8_t select_test_case;

  bool result_is_ok;

  if     (select_test_case == 0U) { result_is_ok = run_wide_integer_mul(); }
  else if(select_test_case == 1U) { result_is_ok = run_wide_integer_div(); }
  else if(select_test_case == 2U) { result_is_ok = run_wide_integer_mod(); }
  else                            { result_is_ok = false; }

  ++select_test_case;

  if(select_test_case >= 3U)
  {
    select_test_case = 0U;
  }

  return result_is_ok;
}
