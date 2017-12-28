///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <limits>

#include <impl/stl_local_constexpr.h>

namespace float_limits
{
  // Use some GCC internal stuff here.
  STL_LOCAL_CONSTEXPR float       arm_nan_flt  = static_cast<float>(__builtin_nan(""));
  STL_LOCAL_CONSTEXPR float       arm_inf_flt  = static_cast<float>(__builtin_inf());
  STL_LOCAL_CONSTEXPR double      arm_nan_dbl  = __builtin_nan("");
  STL_LOCAL_CONSTEXPR double      arm_inf_dbl  = __builtin_inf();
  STL_LOCAL_CONSTEXPR long double arm_nan_ldbl = static_cast<long double>(__builtin_nan(""));
  STL_LOCAL_CONSTEXPR long double arm_inf_ldbl = static_cast<long double>(__builtin_inf());
}

namespace std
{
  float numeric_limits_details::my_value_that_needs_to_be_provided_flt_quiet_NaN()
  {
    return float_limits::arm_nan_flt;
  }

  float numeric_limits_details::my_value_that_needs_to_be_provided_flt_signaling_NaN()
  {
    return 0.0F;
  }

  float numeric_limits_details::my_value_that_needs_to_be_provided_flt_infinity()
  {
    return float_limits::arm_inf_flt;
  }

  double numeric_limits_details::my_value_that_needs_to_be_provided_dbl_quiet_NaN()
  {
    return float_limits::arm_nan_dbl;
  }

  double numeric_limits_details::my_value_that_needs_to_be_provided_dbl_signaling_NaN()
  {
    return 0.0;
  }

  double numeric_limits_details::my_value_that_needs_to_be_provided_dbl_infinity()
  {
    return float_limits::arm_inf_dbl;
  }

  long double numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_quiet_NaN()
  {
    return float_limits::arm_nan_ldbl;
  }

  long double numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_signaling_NaN()
  {
    return 0.0L;
  }

  long double numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_infinity()
  {
    return float_limits::arm_inf_ldbl;
  }
}
