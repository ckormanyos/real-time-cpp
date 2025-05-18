///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_ECC_GENERIC_ECC))

#include <random>

#include <math/checksums/crc/crc32.h>
#include <math/checksums/generic_ecc/digital_signature_generic_ecc.h>
#include <math/checksums/hash/hash_sha256.h>

#include <mcal_gpt.h>

#include <util/utility/util_time.h>
#include <util/utility/util_two_part_data_manipulation.h>

namespace curve_secp256k1
{
  constexpr char CurveName           [] = "secp256k1";                                                          // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char FieldCharacteristicP[] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char CurveCoefficientA   [] = "0x0";                                                                // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char CurveCoefficientB   [] = "0x7";                                                                // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char BasePointGx         [] = "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char BasePointGy         [] = "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr char SubGroupOrderN      [] = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-pro-bounds-array-to-pointer-decay,modernize-avoid-c-arrays)
  constexpr auto SubGroupCoFactorH      = static_cast<int>(INT8_C(1));

  using hash_type = math::checksums::hash::hash_sha256<std::uint16_t>;
}

namespace local
{
  auto test_sign_verify() -> bool;

  // Declare the secp256k1 digital signature type.

  using digital_signature_secp256k1_type =
    generic_ecc::digital_signature_generic_ecc<static_cast<unsigned>(UINT16_C(256)),
                                               std::uint32_t,
                                               curve_secp256k1::CurveName,            // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::FieldCharacteristicP, // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::CurveCoefficientA,    // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::CurveCoefficientB,    // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::BasePointGx,          // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::BasePointGy,          // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::SubGroupOrderN,       // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
                                               curve_secp256k1::SubGroupCoFactorH,
                                               curve_secp256k1::hash_type>;

  auto test_sign_verify_index = unsigned { };
}

namespace
{
  local::digital_signature_secp256k1_type ds;

  std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))> public_key_xy { };
  std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(32))> private_key   { };

  const auto seed_keygen = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(32))>
                           {
                             0xC6U, 0x45U, 0x5BU, 0xF2U, 0xF3U, 0x80U, 0xF6U, 0xB8U,
                             0x1FU, 0x5FU, 0xD1U, 0xA1U, 0xDBU, 0xC2U, 0x39U, 0x2BU,
                             0x37U, 0x83U, 0xEDU, 0x1EU, 0x7DU, 0x91U, 0xB6U, 0x29U,
                             0x42U, 0x70U, 0x6EU, 0x55U, 0x84U, 0xBAU, 0x0BU, 0x92U
                           };

  const auto public_key_xy_ctrl = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))>
                                  {
                                    0xC6U, 0x23U, 0x56U, 0x29U, 0xF1U, 0x57U, 0x69U, 0x0EU,
                                    0x1DU, 0xF3U, 0x72U, 0x48U, 0x25U, 0x6CU, 0x4FU, 0xB7U,
                                    0xEFU, 0xF0U, 0x73U, 0xD0U, 0x25U, 0x0FU, 0x5BU, 0xD8U,
                                    0x5DU, 0xF4U, 0x0BU, 0x9EU, 0x12U, 0x7AU, 0x84U, 0x61U,
                                    0xCBU, 0xAAU, 0x67U, 0x9FU, 0x07U, 0xF9U, 0xB9U, 0x8FU,
                                    0x91U, 0x5CU, 0x1FU, 0xB7U, 0xD8U, 0x5AU, 0x37U, 0x9DU,
                                    0x05U, 0x59U, 0xA9U, 0xEEU, 0xE6U, 0x73U, 0x5BU, 0x1BU,
                                    0xE0U, 0xCEU, 0x0EU, 0x2EU, 0x2BU, 0x2EU, 0x94U, 0xDEU
                                  };

  const auto seed_sign = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(32))>
                         {
                           0x6FU, 0x73U, 0xD8U, 0xE9U, 0x5DU, 0x6DU, 0xDBU, 0xF0U,
                           0xEBU, 0x35U, 0x2AU, 0x9FU, 0x0BU, 0x2CU, 0xE9U, 0x19U,
                           0x31U, 0x51U, 0x1EU, 0xDAU, 0xF9U, 0xACU, 0x8FU, 0x12U,
                           0x8DU, 0x5AU, 0x4FU, 0x87U, 0x7CU, 0x4FU, 0x04U, 0x50U
                         };

  const auto sig_ctrl = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))>
                        {
                          0x65U, 0x71U, 0x7AU, 0x86U, 0x0FU, 0x31U, 0x5AU, 0x21U,
                          0xE6U, 0xE2U, 0x3CU, 0xDEU, 0x41U, 0x1CU, 0x89U, 0x40U,
                          0xDEU, 0x42U, 0xA6U, 0x9DU, 0x8AU, 0xB2U, 0x6CU, 0x24U,
                          0x65U, 0x90U, 0x2BU, 0xE8U, 0xF3U, 0xB7U, 0x5EU, 0x7BU,
                          0xDBU, 0x8BU, 0x8EU, 0x75U, 0xA7U, 0xB0U, 0xC2U, 0xF0U,
                          0xD9U, 0xEBU, 0x8DU, 0xBFU, 0x1BU, 0x52U, 0x36U, 0xEDU,
                          0xEBU, 0x89U, 0xB2U, 0x11U, 0x6FU, 0x5AU, 0xEBU, 0xD4U,
                          0x0EU, 0x77U, 0x0FU, 0x8CU, 0xCCU, 0x3DU, 0x66U, 0x05U
                        };

  std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))> sig_to_retrieve { };
}

auto local::test_sign_verify() -> bool
{
  auto result_is_ok = true;

  // Declare the message "Hello!" as an array of unsigned bytes.
  const std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(6))> msg_as_array { 'H', 'e', 'l', 'l', 'o', '!' };

  if(local::test_sign_verify_index == static_cast<unsigned>(UINT8_C(0)))
  {
    // Test ECC key generation.

    auto public_key_xy_size = std::size_t { };
    auto private_key_size   = std::size_t { };

    const auto result_keypair_generate_is_ok = ds.keypair_generate(public_key_xy.data(),
                                                                   &public_key_xy_size,
                                                                   private_key.data(),
                                                                   &private_key_size,
                                                                   seed_keygen.data(),
                                                                   seed_keygen.size());

    const auto result_public_key_xy_is_ok = (public_key_xy == public_key_xy_ctrl);

    const auto result_keygen_is_ok = (result_keypair_generate_is_ok && result_public_key_xy_is_ok);

    result_is_ok = (result_keygen_is_ok && result_is_ok);

    ++local::test_sign_verify_index;
  }
  else if(local::test_sign_verify_index == static_cast<unsigned>(UINT8_C(1)))
  {
    // Test ECC sign.
    std::size_t  signature_size { };

    static_cast<void>
    (
      ds.sign(msg_as_array.data(),
              msg_as_array.size(),
              private_key.data(),
              private_key.size(),
              sig_to_retrieve.data(),
              &signature_size,
              seed_sign.data(),
              seed_sign.size())
    );

    const auto result_signature_is_ok = (sig_to_retrieve == sig_ctrl);

    result_is_ok = (result_signature_is_ok && result_is_ok);

    ++local::test_sign_verify_index;
  }
  else if(local::test_sign_verify_index == static_cast<unsigned>(UINT8_C(2)))
  {
    // Test ECC verify.

    const auto result_verify_is_ok = ds.verify(msg_as_array.data(),
                                               msg_as_array.size(),
                                               sig_to_retrieve.data(),
                                               sig_to_retrieve.size(),
                                               public_key_xy.data(),
                                               public_key_xy.size());

    result_is_ok = (result_verify_is_ok && result_is_ok);

    local::test_sign_verify_index = static_cast<unsigned>(UINT8_C(0));
  }

  return result_is_ok;
}

auto app::benchmark::run_ecc_generic_ecc() -> bool
{
  const auto result_ecc_generic_is_ok = local::test_sign_verify();

  return result_ecc_generic_is_ok;
}

extern "C"
auto my_hardware_random_device_generator() -> unsigned int;

extern "C"
auto my_hardware_random_device_generator() -> unsigned int
{
  using timer_type = util::timer<std::uint64_t>;

  const auto t_now = timer_type::get_mark();

  const auto pseudo_random1 =
    math::checksums::crc::crc32_mpeg2
    (
      reinterpret_cast<const std::uint8_t*>(&t_now),
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint32_t)
    );

  const auto pseudo_random2 =
    math::checksums::crc::crc32_mpeg2
    (
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint32_t),
      reinterpret_cast<const std::uint8_t*>(&t_now) + sizeof(std::uint64_t)
    );

  return static_cast<unsigned int>(util::make_long(pseudo_random1, pseudo_random2));
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
auto main() -> int;

auto main() -> int
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_ECC_GENERIC_ECC -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_hash.cpp -o ./ref_app/bin/app_benchmark_hash.exe

  auto result_is_ok = true;

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(16)); ++i)
  {
    result_is_ok = (app::benchmark::run_ecc_generic_ecc() && result_is_ok);
  }

  return (result_is_ok ? 0 : -1);
}

#if !defined(__arm__)
auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  return mcal::gpt::value_type { };
}
#endif

#endif

#endif // APP_BENCHMARK_TYPE_HASH_SHA256
