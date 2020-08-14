///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_22-002_test_random_engines.cpp

#include <iomanip>
#include <iostream>
#include <random>

template<typename RngType>
typename RngType::result_type get_10000th_rnd_with_default_seed()
{
  using rng_type = RngType;

  rng_type eng;

  eng.discard(9999U);

  const typename rng_type::result_type rnd = eng();

  return rnd;
}

void do_something()
{
  using random_engine_type_0 = std::minstd_rand0;  //          1043618065
  using random_engine_type_1 = std::minstd_rand;   //           399268537
  using random_engine_type_2 = std::mt19937;       //          4123659995
  using random_engine_type_3 = std::mt19937_64;    // 9981545732273789042
  using random_engine_type_4 = std::ranlux24_base; //             7937952
  using random_engine_type_5 = std::ranlux48_base; //      61839128582725
  using random_engine_type_6 = std::ranlux24;      //             9901578
  using random_engine_type_7 = std::ranlux48;      //     249142670248501
  using random_engine_type_8 = std::knuth_b;       //         $1112339016

  const typename random_engine_type_0::result_type rnd_0 = get_10000th_rnd_with_default_seed<random_engine_type_0>();
  const typename random_engine_type_1::result_type rnd_1 = get_10000th_rnd_with_default_seed<random_engine_type_1>();
  const typename random_engine_type_2::result_type rnd_2 = get_10000th_rnd_with_default_seed<random_engine_type_2>();
  const typename random_engine_type_3::result_type rnd_3 = get_10000th_rnd_with_default_seed<random_engine_type_3>();
  const typename random_engine_type_4::result_type rnd_4 = get_10000th_rnd_with_default_seed<random_engine_type_4>();
  const typename random_engine_type_5::result_type rnd_5 = get_10000th_rnd_with_default_seed<random_engine_type_5>();
  const typename random_engine_type_6::result_type rnd_6 = get_10000th_rnd_with_default_seed<random_engine_type_6>();
  const typename random_engine_type_7::result_type rnd_7 = get_10000th_rnd_with_default_seed<random_engine_type_7>();
  const typename random_engine_type_8::result_type rnd_8 = get_10000th_rnd_with_default_seed<random_engine_type_8>();

  const bool result_0_is_ok = (rnd_0 == UINT32_C(         1043618065)); // std::minstd_rand0
  const bool result_1_is_ok = (rnd_1 == UINT32_C(          399268537)); // std::minstd_rand
  const bool result_2_is_ok = (rnd_2 == UINT32_C(         4123659995)); // std::mt19937
  const bool result_3_is_ok = (rnd_3 == UINT64_C(9981545732273789042)); // std::mt19937_64
  const bool result_4_is_ok = (rnd_4 == UINT32_C(            7937952)); // std::ranlux24_base
  const bool result_5_is_ok = (rnd_5 == UINT64_C(     61839128582725)); // std::ranlux48_base
  const bool result_6_is_ok = (rnd_6 == UINT32_C(            9901578)); // std::ranlux24
  const bool result_7_is_ok = (rnd_7 == UINT64_C(    249142670248501)); // std::ranlux48
  const bool result_8_is_ok = (rnd_8 == UINT32_C(         1112339016)); // std::knuth_b

  const bool result_is_ok = (   result_0_is_ok
                             && result_1_is_ok
                             && result_2_is_ok
                             && result_3_is_ok
                             && result_4_is_ok
                             && result_5_is_ok
                             && result_6_is_ok
                             && result_7_is_ok
                             && result_8_is_ok);

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

int main()
{
  do_something();
}
