///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_WIDE_INTEGER))

// Optionally and manually change the zero in (#if 0) to one
// in order to force run-time evaluation. If left as #if 0,
// then the wide-integer calculations will be constexpr
// and performed at compile-time.

#if 0
#define APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST const             // NOLINT(cppcoreguidelines-macro-usage)
#define APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT 0 // NOLINT(cppcoreguidelines-macro-usage)
#else
#define APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST constexpr         // NOLINT(cppcoreguidelines-macro-usage)
#define APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT 1 // NOLINT(cppcoreguidelines-macro-usage)
#endif

#define WIDE_INTEGER_DISABLE_IOSTREAM
#define WIDE_INTEGER_DISABLE_TO_STRING
#define WIDE_INTEGER_DISABLE_IMPLEMENT_UTIL_DYNAMIC_ARRAY
#define WIDE_INTEGER_DISABLE_TRIVIAL_COPY_AND_STD_LAYOUT_CHECKS

#if !defined(WIDE_INTEGER_NAMESPACE)
#define WIDE_INTEGER_NAMESPACE ckormanyos
#endif

#include <math/wide_integer/uintwide_t.h>

namespace
{
  #if defined(WIDE_INTEGER_NAMESPACE)
  using WIDE_INTEGER_NAMESPACE::math::wide_integer::uint256_t;
  using WIDE_INTEGER_NAMESPACE::math::wide_integer::uint512_t;
  #else
  using ::math::wide_integer::uint256_t;
  using ::math::wide_integer::uint512_t;
  #endif

  static_assert((   std::numeric_limits<uint256_t>::digits == static_cast<int>(INT16_C(256))
                 && std::numeric_limits<uint512_t>::digits == static_cast<int>(INT16_C(512))),
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
  //   a * b = 0x1573D6A7CEA734D99865C4F428184983CDB018B80E9CC44B83C773FBE11993E7E491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076
  //
  // Divide:
  //   a / b = 10
  //
  // Modulus:
  //   a % b = 0x14998D5CA3DB6385F7DEDF4621DE48A9104AC13797C6567713D7ABC216D7AB4C

  APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST uint256_t a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST uint256_t b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");
  APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST uint512_t c("0x1573D6A7CEA734D99865C4F428184983CDB018B80E9CC44B83C773FBE11993E7E491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076");
  APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST uint256_t m("0x14998D5CA3DB6385F7DEDF4621DE48A9104AC13797C6567713D7ABC216D7AB4C");

  auto run_wide_integer_mul() -> bool
  {
    APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST auto result_of_mul_is_ok = ((uint512_t(a) * uint512_t(b)) == c);

    #if (defined(APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT) \
             && (APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT == 1))
    static_assert(result_of_mul_is_ok, "Error: result_of_mul_is_ok not OK!");
    #endif

    return result_of_mul_is_ok;
  }

  auto run_wide_integer_div() -> bool
  {
    APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST uint256_t q(static_cast<std::uint8_t>(UINT8_C(10)));

    APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST auto result_of_div_is_ok = ((a / b) == q);

    #if (defined(APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT) \
             && (APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT == 1))
    static_assert(result_of_div_is_ok, "Error: result_of_div_is_ok not OK!");
    #endif

    return result_of_div_is_ok;
  }

  auto run_wide_integer_mod() -> bool
  {
    APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_OR_CONST auto result_of_mod_is_ok = ((a % b) == m);

    #if (defined(APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT) \
             && (APP_BENCHMARK_WIDE_INTEGER_CONSTEXPR_IS_COMPILE_TIME_CONSTANT == 1))
    static_assert(result_of_mod_is_ok, "Error: result_of_div_is_ok not OK!");
    #endif

    return result_of_mod_is_ok;
  }
}

auto app::benchmark::run_wide_integer() -> bool
{
  static std::uint_fast8_t select_test_case;

  bool result_is_ok { };

  if(select_test_case == static_cast<std::uint_fast8_t>(UINT8_C(0)))
  {
    result_is_ok = run_wide_integer_mul();
  }
  else if(select_test_case == static_cast<std::uint_fast8_t>(UINT8_C(1)))
  {
    result_is_ok = run_wide_integer_div();
  }
  else if(select_test_case == static_cast<std::uint_fast8_t>(UINT8_C(2)))
  {
    result_is_ok = run_wide_integer_mod();
  }
  else
  {
    result_is_ok = false;
  }

  ++select_test_case;

  if(select_test_case >= 3U)
  {
    select_test_case = 0U;
  }

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_INTEGER -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_wide_integer.cpp -o ./ref_app/bin/app_benchmark_wide_integer.exe

  auto result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_wide_integer();
  }

  return result_is_ok ? 0 : -1;
}
#endif

#endif // APP_BENCHMARK_TYPE_WIDE_INTEGER
