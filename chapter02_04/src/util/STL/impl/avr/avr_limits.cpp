#include "../limits_impl.h"

namespace
{
  constexpr double avr_nan = __builtin_nan("");
  constexpr double avr_inf = __builtin_inf();
}

namespace std
{
  double numeric_limits_base::my_value_that_needs_to_be_provided_double_quiet_NaN(void)
  {
    return ::avr_nan;
  }

  double numeric_limits_base::my_value_that_needs_to_be_provided_double_infinity(void)
  {
    return ::avr_inf;
  }
}
