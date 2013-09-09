///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XCMATH_IMPL_2013_08_22_H_
  #define _XCMATH_IMPL_2013_08_22_H_

  #include <algorithm>
  #include <cstdint>
  #include <limits>

  namespace xcmath
  {
    template<typename float_type>
    bool near_integer(const float_type& x, const std::uint_least8_t n)
    {
      const float_type n_eps = static_cast<float_type>( (std::max)(std::uint_least8_t(2U), std::uint_least8_t(n + 1U))
                                                       * std::numeric_limits<float_type>::epsilon());

      const float_type n_minus_n_eps = static_cast<float_type>(n) - n_eps;
      const float_type n_plus_n_eps  = static_cast<float_type>(n) + n_eps;

      return ((x > n_minus_n_eps) && (x < n_plus_n_eps));
    }
  }

  float  acosh(float x);
  float tgamma(float x);

#endif // _XCMATH_IMPL_2013_08_22_H_
