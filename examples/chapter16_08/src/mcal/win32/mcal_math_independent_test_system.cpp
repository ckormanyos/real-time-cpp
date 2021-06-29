///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_math_independent_test_system.h>
#include <math/test/math_test_independent_test_system_mathlink.h>

namespace
{
  // Use the default mathlink 12.1 kernel location on Win*.
  static const char independent_test_system_mathlink_location[] =
    "\"C:\\Program Files\\Wolfram Research\\Mathematica\\12.1\\MathKernel.exe\"";
}

::math::test::independent_test_system_base& mcal::math::independent_test_system0() noexcept
{
  using test_system_type = ::math::test::independent_test_system_mathlink<independent_test_system_mathlink_location>;

  static test_system_type ts0;

  return ts0;
}
