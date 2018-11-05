
#define WIDE_INTEGER_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark.h>
#include <math/wide_integer/generic_template_uintwide_t.h>

namespace
{
  using wide_integer_type = wide_integer::generic_template::uint256_t;

  // Note: Some of the following comments use the Wolfram Language(TM).
  //
  // Create two pseudo-random 256-bit unsigned integers.
  //   Table[IntegerString[RandomInteger[{1, (2^256) - 1}], 16], 2]
  //   {
  //     F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
  //     166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
  //   }
  //
  // Set the values of two random 256-bit unsigned integers.
  //   a = 0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE
  //   b = 0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
  //
  // Multiply c = a * b.
  //   a * b = 0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076
  //
  // Divide d = a / b.
  //   a / b = 10

  const wide_integer_type a("0xF4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE");
  const wide_integer_type b("0x166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75");

  const wide_integer_type a_mul_b("0xE491A360C57EB4306C61F9A04F7F7D99BE3676AAD2D71C5592D5AE70F84AF076");
  const wide_integer_type a_div_b(std::uint8_t(10U));

  wide_integer_type c;
  wide_integer_type d;

  bool run_wide_integer_mul()
  {
    static_assert(std::numeric_limits<wide_integer_type>::digits == 256,
                  "Error: Incorrect digit count for this example");

    c = (a * b);

    const bool result_is_ok = (c == a_mul_b);

    return result_is_ok;
  }

  bool run_wide_integer_div()
  {
    static_assert(std::numeric_limits<wide_integer_type>::digits == 256,
                  "Error: Incorrect digit count for this example");

    d = (a / b);

    const bool result_is_ok = (d == a_div_b);

    return result_is_ok;
  }
}

bool app::benchmark::run_wide_integer()
{
  static bool toggle_test_case = true;

  const bool result_is_ok = (toggle_test_case ? run_wide_integer_mul()
                                              : run_wide_integer_div());

  toggle_test_case = (!toggle_test_case);

  return result_is_ok;
}
