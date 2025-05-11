///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_TEST_INDEPENDENT_TEST_SYSTEM_NONE_2020_07_15_H
  #define MATH_TEST_INDEPENDENT_TEST_SYSTEM_NONE_2020_07_15_H

  #include <math/test/math_test_independent_test_system_base.h>

  namespace WIDE_INTEGER_NAMESPACE { namespace math { namespace test {

  class independent_test_system_none : public independent_test_system_base
  {
  public:
    independent_test_system_none() noexcept = default;

    ~independent_test_system_none() noexcept override = default;

    auto is_prime(const char* const pstr_prime_candidate) const -> bool override
    {
      static_cast<void>(pstr_prime_candidate);

      return true;
    }
  };

  } // namespace test
  } // namespace math
  } // namespace WIDE_INTEGER_NAMESPACE

#endif // MATH_TEST_INDEPENDENT_TEST_SYSTEM_NONE_2020_07_15_H
