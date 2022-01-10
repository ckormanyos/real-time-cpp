///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_math_independent_test_system.h>
#include <math/test/math_test_independent_test_system_none.h>

WIDE_INTEGER_NAMESPACE::math::test::independent_test_system_base& mcal::math::independent_test_system0() noexcept
{
  using test_system_type = WIDE_INTEGER_NAMESPACE::math::test::independent_test_system_none;

  static test_system_type ts0;

  return ts0;
}
