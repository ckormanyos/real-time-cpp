///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <app/benchmark/app_benchmark.h>

#if (defined(APP_BENCHMARK_TYPE) && (APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_STD_BIG_INT))

#include <util/memory/util_ring_allocator.h>

#include <beman/big_int/big_int.hpp> // This includes the entire std-big-int library

#include <algorithm>
#include <cstdint>
#include <cstring>

static auto do_one_test() -> bool;

static auto do_one_test() -> bool
{
  using allocator_type = util::ring_allocator<beman::big_int::uint_multiprecision_t, std::uint_fast32_t { 0x2000U }>;

  using wi_type = beman::big_int::basic_big_int<std::numeric_limits<typename allocator_type::value_type>::digits, allocator_type>;

  using wi_result_type = wi_type;

  wi_type wi_val_a {};
  wi_type wi_val_b {};
  wi_result_type wi_val_ctrl {};

  constexpr const char str_a[] = "fee6f3060ed3f90fdd79fe414418f8d9dc08bbe4470b658ca8f167fc3ce48821a79f8f9df51d795cbb88cb6e3a5e5f46b56f06991d6a929784b414c0bff17ca7eef9ab0e4d469093c548018d66a349beda36a4afdeb9d329d4119e93fa436a2b8417c3b2af701dde827e01e608c3ddfedfdc7fd7052fda87efb34d8321f3941482bc74e109ebdff9aebc9585de04ab47afb41ccbda18d806eb3d87ed7b1c0f03954ef98f08432db8f86e4ebceb292c53ac83f9738f8cd88da17384cdfb31d25bf6e030571d52ac43a7c646dee1fc0a8d827d73917b3c5f84dc7d1515a0c9a1bef3dc7f9d8caed3b3db7c869e262860a4e008c12d5f3da2c733c0f55168a30be2";
  constexpr const char str_b[] = "d7f1c5ebfe9108ab8900f3d1af36367cce3e92121acb9b60e352e5d622525715d0203ddd77d9ab308709777b225948c3e61542010fe75974ddb38cc38a11fa65bee2a6f171fe7ee4e52d81569bfcb886f972bd4655b6388bc7c8982f6e6a31efc21f8579394b5e629c15c367ee6eda6091dcb0f8aea6daa69f9c7059e585fc92a28c16d16183b8b0edf460b9741b712a9aaaf9d557ae4a7ef5cead986e9c414988b5fc43d78d8f7fbbc7f6cfd7e08bf8f87ce6f865b9ad1fcf4b00f42939349398c4a2928c21959ff6105665de3d95be8afc9fe9fb33d6afb95948e9778328fdd7172c70431479229cae5a47463f832b9ca2a39f36963f3ec1dc39fe6a3bffbc";
  constexpr const char str_ctrl[] = "d704b29793a64a44339b92e4f202801cae2ca252f899cf36ae3735c98505f4c16a7a6a159e54e8927d4ec95defd8ec04afcc0043bdab50dfc763b376549ab90df60d476bd5b26c3f5b2378656fe307f7da459b62924efa9f6d408484a44a88265515b04f1d75351ba7e6436cdf6d67a87c82dbacb02f782f1601feb974d10367e275561904466d31daf817f350752636455bf7f6f86f21268bf173182e430fdeb80fbc96daf032ec381f761476b8bf2cc33d6ec7d67d96eb69fef2bce4c715e4d676b8c2066afa83f10243273f5c65b427e71eaee89d285f39692e757cb6b86a085e7869ef85c05155328130e37163b8addb3410ccd9fde92fcc5e8a9b3336113440f34e3ace928c98de63d02c0caa1c160cfb8ccf46d48bdf9ebd24f5611582d92cf787e02198e7bebc83bd9eae8bd63c5b74573a2923146d05e92211baecb7fb4d7408d31cdccdfdeca05c0c4085775a510f4bed924ebd69e6c4e34c3c6ecb3de0ff2187affe6bffaa1d73df44d730668318922a3077232dab4575a64e8a7958301ce2e341a146f758fc51d7e25298545a6b277b1a9cd9ea72def76d7c05ea5a17ba501050106ff8042f0ffea4c97193b0b8ad138e315d7cd09179d55782534c96b32f21d808e0764b3a341ccc1c20543da2ef9620a5c877fa330bfc43556ddf8069c3fa04e3081b699b8673346f82d112c49bf17fa7c52cc9fbbe91a8d7f8";

  const auto fc_result_a{ from_chars(str_a, str_a + std::strlen(str_a), wi_val_a, 16) };
  const auto fc_result_b{ from_chars(str_b, str_b + std::strlen(str_b), wi_val_b, 16) };
  const auto fc_result_ctrl{ from_chars(str_ctrl, str_ctrl + std::strlen(str_ctrl), wi_val_ctrl, 16) };

  static_cast<void>(fc_result_a);
  static_cast<void>(fc_result_b);
  static_cast<void>(fc_result_ctrl);

  const wi_result_type wi_val_c { wi_val_a * wi_val_b };

  const bool result_is_ok { (wi_val_ctrl == wi_val_c) };

  return result_is_ok;
}

auto app::benchmark::run_std_big_int() -> bool
{
  const bool result_is_ok { ::do_one_test() };

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
constexpr auto app_benchmark_standalone_foodcafe = static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE));

extern "C"
{
  extern volatile std::uint32_t app_benchmark_standalone_result;

  auto app_benchmark_run_standalone       () -> bool;
  auto app_benchmark_get_standalone_result() -> bool;

  auto app_benchmark_run_standalone() -> bool
  {
    auto result_is_ok = true;

    for(unsigned i = 0U; i < 64U; ++i)
    {
      result_is_ok &= app::benchmark::run_std_big_int();
    }

    app_benchmark_standalone_result =
      static_cast<std::uint32_t>
      (
        result_is_ok ? app_benchmark_standalone_foodcafe : static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))
      );

    return result_is_ok;
  }

  auto app_benchmark_get_standalone_result() -> bool
  {
    volatile auto result_is_ok =
      (app_benchmark_standalone_result == static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE)));

    return result_is_ok;
  }
}

ATTRIBUTE(used) auto main() -> int;

auto main() -> int
{
  auto result_is_ok = true;

  result_is_ok = (::app_benchmark_run_standalone       () && result_is_ok);
  result_is_ok = (::app_benchmark_get_standalone_result() && result_is_ok);

  return (result_is_ok ? 0 : -1);
}

extern "C"
{
  volatile std::uint32_t app_benchmark_standalone_result;
}
#endif

#endif // APP_BENCHMARK_TYPE_STD_BIG_INT
