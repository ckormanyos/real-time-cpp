///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_TEST_INDEPENDENT_TEST_SYSTEM_BASE_2020_07_16_H
  #define MATH_TEST_INDEPENDENT_TEST_SYSTEM_BASE_2020_07_16_H

  #include <util/utility/util_noncopyable.h>

  namespace WIDE_INTEGER_NAMESPACE { namespace math { namespace test {

  class independent_test_system_base : private ::util::noncopyable
  {
  public:
    virtual ~independent_test_system_base() noexcept = default;

    virtual auto is_prime(const char* const pstr_prime_candidate) const -> bool = 0;

  protected:
    independent_test_system_base() noexcept = default;
  };

  } // namespace test
  } // namespace math
  } // namespace WIDE_INTEGER_NAMESPACE

#endif // MATH_TEST_INDEPENDENT_TEST_SYSTEM_BASE_2020_07_16_H
