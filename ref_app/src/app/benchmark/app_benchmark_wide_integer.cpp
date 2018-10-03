
#define WIDE_INTEGER_DISABLE_IOSTREAM

#include <app/benchmark/app_benchmark.h>
#include <math/wide_integer/generic_template_uintwide_t.h>

namespace
{
  using wide_integer_type = wide_integer::generic_template::uint256_t;

  // Create two pseudo-random 256-bit unsigned integers.
  //   Table[IntegerString[RandomInteger[{1, (2^256) - 1}], 16], 2]
  //   {
  //     F4DF741DE58BCB2F37F18372026EF9CBCFC456CB80AF54D53BDEED78410065DE,
  //     166D63E0202B3D90ECCEAA046341AB504658F55B974A7FD63733ECF89DD0DF75
  //   }
  //
  // Create two random 256-bit unsigned integers.
  //   a = 0xF4DF741D'E58BCB2F'37F18372'026EF9CB'CFC456CB'80AF54D5'3BDEED78'410065DE
  //   b = 0x166D63E0'202B3D90'ECCEAA04'6341AB50'4658F55B'974A7FD6'3733ECF8'9DD0DF75
  //
  // Multiply c = a * b.
  //   a * b = 0xE491A360'C57EB430'6C61F9A0'4F7F7D99'BE3676AA'D2D71C55'92D5AE70'F84AF076
  //
  // Divide d = a / b.
  //   a / b = 0xA

  const wide_integer_type a
  (
    {
      UINT32_C(0x410065DE),
      UINT32_C(0x3BDEED78),
      UINT32_C(0x80AF54D5),
      UINT32_C(0xCFC456CB),
      UINT32_C(0x026EF9CB),
      UINT32_C(0x37F18372),
      UINT32_C(0xE58BCB2F),
      UINT32_C(0xF4DF741D)
    }
  );

  const wide_integer_type b
  (
    {
      UINT32_C(0x9DD0DF75),
      UINT32_C(0x3733ECF8),
      UINT32_C(0x974A7FD6),
      UINT32_C(0x4658F55B),
      UINT32_C(0x6341AB50),
      UINT32_C(0xECCEAA04),
      UINT32_C(0x202B3D90),
      UINT32_C(0x166D63E0)
    }
  );

  const wide_integer_type a_mul_b
  (
    {
      UINT32_C(0xF84AF076),
      UINT32_C(0x92D5AE70),
      UINT32_C(0xD2D71C55),
      UINT32_C(0xBE3676AA),
      UINT32_C(0x4F7F7D99),
      UINT32_C(0x6C61F9A0),
      UINT32_C(0xC57EB430),
      UINT32_C(0xE491A360)
    }
  );

  const wide_integer_type a_div_b(std::uint16_t(0xAU));
}

bool app::benchmark::run_wide_integer()
{
  const wide_integer_type c = (a * b);
  const wide_integer_type d = (a / b);

  const bool result_is_ok = ((c == a_mul_b) && (d == a_div_b));

  return result_is_ok;
}
