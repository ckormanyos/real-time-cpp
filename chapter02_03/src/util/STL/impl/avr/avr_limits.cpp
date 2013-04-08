///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/*
#include "../limits_impl.h"

namespace
{
  constexpr float  avr_nan_float  = static_cast<float>(__builtin_nan(""));
  constexpr float  avr_inf_float  = static_cast<float>(__builtin_inf());
  constexpr double avr_nan_double = __builtin_nan("");
  constexpr double avr_inf_double = __builtin_inf();
}

namespace std
{
  float numeric_limits_base::my_value_that_needs_to_be_provided_float_quiet_NaN()
  {
    return ::avr_nan_float;
  }

  float numeric_limits_base::my_value_that_needs_to_be_provided_float_infinity()
  {
    return ::avr_inf_float;
  }

  double numeric_limits_base::my_value_that_needs_to_be_provided_double_quiet_NaN()
  {
    return ::avr_nan_double;
  }

  double numeric_limits_base::my_value_that_needs_to_be_provided_double_infinity()
  {
    return ::avr_inf_double;
  }
}
*/
