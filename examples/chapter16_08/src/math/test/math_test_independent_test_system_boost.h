///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 -2024.
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

  namespace WIDE_INTEGER_NAMESPACE { namespace math { namespace test {

  template<const unsigned Width2>
  class independent_test_system_boost : public math::test::independent_test_system_base
  {
  private:
    static constexpr unsigned boost_uint_digits { Width2 };

    using boost_uint_backend_type =
      boost::multiprecision::cpp_int_backend<boost_uint_digits,
                                             boost_uint_digits,
                                             boost::multiprecision::unsigned_magnitude>;

    using boost_uint_type = boost::multiprecision::number<boost_uint_backend_type, boost::multiprecision::et_off>;

    using random_engine_type = std::mt19937_64;

  public:
    independent_test_system_boost() noexcept = default;

    ~independent_test_system_boost() noexcept override { }

    auto is_prime(const char* const pstr_prime_candidate) const -> bool override
    {
      const boost_uint_type p { std::string("0x") + pstr_prime_candidate };

      const bool is_prime_says_boost_miller_rabin = boost::multiprecision::miller_rabin_test(p, 25, my_gen);

      ++my_seed_count;

      if((my_seed_count % 0x1000U) == 0U)
      {
        my_gen.seed(static_cast<typename random_engine_type::result_type>(std::clock()));
      }

      return is_prime_says_boost_miller_rabin;
    }

  private:
    mutable random_engine_type my_gen        { static_cast<typename random_engine_type::result_type>(std::clock()) };
    mutable std::uint32_t      my_seed_count { };
  };

  } // namespace test
  } // namespace math
  } // namespace WIDE_INTEGER_NAMESPACE

#endif // MATH_TEST_INDEPENDENT_TEST_SYSTEM_BOOST_2020_10_10_H_
