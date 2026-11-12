///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>

auto test_stl_sanity_cmath() -> bool;

auto test_stl_sanity_cmath() -> bool
{
  const auto near = [](float actual, float expected, float tolerance)
  {
    return (std::fabs(actual - expected) < tolerance);
  };

  bool result_near_is_ok { true };

  result_near_is_ok = near(std::tgamma(1.0F), 1.0F, 0.001F) && result_near_is_ok;
  result_near_is_ok = near(std::tgamma(2.0F), 1.0F, 0.001F) && result_near_is_ok;
  result_near_is_ok = near(std::tgamma(3.0F), 2.0F, 0.001F) && result_near_is_ok;
  result_near_is_ok = near(std::tgamma(4.0F), 6.0F, 0.001F) && result_near_is_ok;
  result_near_is_ok = near(std::tgamma(0.5F), 1.7724539F, 0.05F) && result_near_is_ok;
  result_near_is_ok = near(std::tgamma(-0.5F), -3.5449077F, 0.1F) && result_near_is_ok;

  if(   !result_near_is_ok
     || std::isfinite(std::tgamma(0.0F))
     || std::isfinite(std::tgamma(-1.0F)))
  {
    return false;
  }

  if(   !near(std::asinh(0.0F), 0.0F, 0.001F)
     || !near(std::asinh(1.0F), 0.8813736F, 0.001F)
     || !near(std::asinh(-1.0F), -0.8813736F, 0.001F)
     || !near(std::asinh(-1.0E20F), -46.74485F, 0.01F)
     || !near(std::acosh(1.0F), 0.0F, 0.001F)
     || !near(std::acosh(2.0F), 1.3169579F, 0.001F)
     || !std::isnan(std::acosh(0.5F))
     || !near(std::atanh(0.0F), 0.0F, 0.001F)
     || !near(std::atanh(0.5F), 0.5493061F, 0.001F)
     || !std::isinf(std::atanh(1.0F))
     || !std::isinf(std::atanh(-1.0F)))
  {
    return false;
  }

  return true;
}
