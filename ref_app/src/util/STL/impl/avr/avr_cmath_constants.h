///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _AVR_CMATH_CONSTANTS_2012_01_09_H_
  #define _AVR_CMATH_CONSTANTS_2012_01_09_H_

  template<typename T>
  constexpr inline T const_sqrt2()
  {
    return T(1.4142135623730950488016887242096980785697L);
  }

  template<typename T>
  constexpr inline T const_pi()
  {
    return T(3.1415926535897932384626433832795028841972L);
  }

  template<typename T>
  constexpr inline T const_sqrt_pi()
  {
    return T(1.7724538509055160272981674833411451827975L);
  }

  template<typename T>
  constexpr inline T const_ln2()
  {
    return T(0.6931471805599453094172321214581765680755L);
  }

  template<typename T>
  constexpr inline T const_e()
  {
    return T(2.7182818284590452353602874713526624977572);
  }

  template<typename T>
  constexpr inline T const_euler_gamma()
  {
    return T(0.5772156649015328606065120900824024310422);
  }

#endif // _AVR_CMATH_CONSTANTS_2012_01_09_H_
