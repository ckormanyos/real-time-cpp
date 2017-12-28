///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef XCMATH_IMPL_2014_01_11_H_
  #define XCMATH_IMPL_2014_01_11_H_

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

    template<typename float_type>
    const float_type pi()
    {
      return static_cast<float_type>(FLOATMAX_C(3.1415926535897932384626433832795028841972));
    }

    template<typename float_type>
    const float_type ln_two()
    {
      return static_cast<float_type>(FLOATMAX_C(0.6931471805599453094172321214581765680755));
    }

      template<typename float_type>
      const float_type euler()
      {
        return static_cast<float_type>(FLOATMAX_C(0.5772156649015328606065120900824024310422));
      }

  }

#endif // XCMATH_IMPL_2014_01_11_H_
