///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_TEST_INDEPENDENT_TEST_SYSTEM_BOOST_2020_10_10_H_
  #define MATH_TEST_INDEPENDENT_TEST_SYSTEM_BOOST_2020_10_10_H_

  #include <ctime>
  #include <random>

  #include <boost/multiprecision/cpp_int.hpp>
  #include <boost/multiprecision/miller_rabin.hpp>

  #include <math/test/math_test_independent_test_system_base.h>

  namespace math { namespace test {

  class independent_test_system_boost : public math::test::independent_test_system_base
  {
  private:
    using uint128_t = boost::multiprecision::uint128_t;

  public:
    independent_test_system_boost() noexcept
      : my_gen       (std::clock()),
        my_seed_count(0U) { }

    virtual ~independent_test_system_boost() noexcept { }

    virtual bool is_prime(const char* const pstr_prime_candidate) const override
    {
      const uint128_t p(std::string("0x") + pstr_prime_candidate);

      const bool is_prime_says_boost_miller_rabin =
        boost::multiprecision::miller_rabin_test(p, 25, my_gen);

      ++my_seed_count;

      if((my_seed_count % 0x1000U) == 0U)
      {
        my_gen.seed(std::clock());
      }

      return is_prime_says_boost_miller_rabin;
    }

  private:
    mutable std::mt19937  my_gen;
    mutable std::uint32_t my_seed_count;
  };

  } } // namespace math::test

#endif // MATH_TEST_INDEPENDENT_TEST_SYSTEM_BOOST_2020_10_10_H_
