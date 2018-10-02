#include <app/benchmark/app_benchmark.h>
#include <math/wide_integer/non_template_uint256_t.h>

namespace
{
  using wide_integer_type = wide_integer::non_template::uint256_t;

  // Create two pseudo-random 256-bit unsigned integers.
  //   Table[IntegerString[RandomInteger[{1, (2^256) - 1}], 16], 2]
  //   {
  //     F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
  //     166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
  //   }
  //
  // Create two random 256-bit unsigned integers.
  //   a = 0xF4DF741DE58BCB2F'37F18372026EF9CB'CFC456CB80AF54D5'3BDEED78410065DE
  //   b = 0x166D63E0202B3D90'ECCEAA046341AB50'4658F55B974A7FD6'3733ECF89DD0DF75
  //
  // Multiply c = a * b.
  //   a * b = 0xE491A360C57EB430'6C61F9A04F7F7D99'BE3676AAD2D71C55'92D5AE70F84AF076
  //
  // Divide d = a / b.
  //   a / b = 0xA

  const wide_integer_type a
  (
    {
      UINT64_C(0x3BDEED78410065DE),
      UINT64_C(0xCFC456CB80AF54D5),
      UINT64_C(0x37F18372026EF9CB),
      UINT64_C(0xF4DF741DE58BCB2F)
    }
  );

  const wide_integer_type b
  (
    {
      UINT64_C(0x3733ECF89DD0DF75),
      UINT64_C(0x4658F55B974A7FD6),
      UINT64_C(0xECCEAA046341AB50),
      UINT64_C(0x166D63E0202B3D90)
    }
  );

  const wide_integer_type a_mul_b
  (
    {
      UINT64_C(0x92D5AE70F84AF076),
      UINT64_C(0xBE3676AAD2D71C55),
      UINT64_C(0x6C61F9A04F7F7D99),
      UINT64_C(0xE491A360C57EB430)
    }
  );

  wide_integer_type a_div_b(std::uint16_t(0xAU));
}

bool app::benchmark::run_wide_integer()
{
  const wide_integer_type c = (a * b);
  const wide_integer_type d = (a / b);

  const bool result_is_ok = ((c == a_mul_b) && (d == a_div_b));

  return result_is_ok;
}
