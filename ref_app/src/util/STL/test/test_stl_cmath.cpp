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
  #if defined(__v850__)

  // TBD: Something is going wrong with building this test on gcc-v850-unknown-elf.

  #else

  const auto
    is_near_checker
    {
      [](float actual, float expected, float tolerance)
      {
        const int fpc_result { std::fpclassify(expected) };

        if(fpc_result == FP_ZERO)
        {
          return (std::fabs(actual - expected) < tolerance);
        }
        else if (fpc_result == FP_NORMAL)
        {
          return (std::fabs(1.0F - (actual / expected)) < tolerance);
        }
        else
        {
          return false;
        }
      }
    };

  bool result_near_is_ok { true };

  result_near_is_ok = is_near_checker(std::tgamma(1.0F), 1.0F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(1.1F), 0.951350770F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(1.9F), 0.961765832F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(3.1F), 2.19762028F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(3.5F), 3.32335097F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(4.0F), 6.0F, 0.0001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(0.5F), 1.7724539F, 0.001F) && result_near_is_ok;
  result_near_is_ok = is_near_checker(std::tgamma(-0.5F), -3.54490770F, 0.001F) && result_near_is_ok;

  if(   (!result_near_is_ok)
     || std::isfinite(std::tgamma(0.0F))
     || std::isfinite(std::tgamma(-1.0F)))
  {
    return false;
  }

  if(   (!is_near_checker(std::asinh(0.0F), 0.0F, 0.001F))
     || (!is_near_checker(std::asinh(1.0F), 0.8813736F, 0.001F))
     || (!is_near_checker(std::asinh(-1.0F), -0.8813736F, 0.001F))
     || (!is_near_checker(std::asinh(-1.0E20F), -46.74485F, 0.01F))
     || (!is_near_checker(std::acosh(1.0F), 0.0F, 0.001F))
     || (!is_near_checker(std::acosh(2.0F), 1.3169579F, 0.0001F))
     || (!is_near_checker(std::acosh(4.1F), 2.0889189F, 0.0001F))
     || (!std::isnan(std::acosh(0.5F)))
     || (!is_near_checker(std::atanh(0.0F), 0.0F, 0.001F))
     || (!is_near_checker(std::atanh(0.5F), 0.5493061F, 0.001F))
     || (!std::isinf(std::atanh(1.0F)))
     || (!std::isinf(std::atanh(-1.0F))))
  {
    return false;
  }
  #endif

  return true;
}
