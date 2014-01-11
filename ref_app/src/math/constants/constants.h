///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CONSTANTS_2012_01_09_H_
  #define _CONSTANTS_2012_01_09_H_

  #include <cstdfloat>

  namespace math
  {
    namespace constants
    {
      template<typename float_type>
      const float_type sqrt2()
      {
        return static_cast<float_type>(FLOATMAX_C(1.4142135623730950488016887242096980785697));
      }

      template<typename float_type>
      const float_type pi()
      {
        return static_cast<float_type>(FLOATMAX_C(3.1415926535897932384626433832795028841972));
      }

      template<typename float_type>
      const float_type pi_half()
      {
        return static_cast<float_type>(FLOATMAX_C(1.5707963267948966192313216916397514420986));
      }

      template<typename float_type>
      const float_type sqrt_pi()
      {
        return static_cast<float_type>(FLOATMAX_C(1.7724538509055160272981674833411451827975));
      }

      template<typename float_type>
      const float_type ln2()
      {
        return static_cast<float_type>(FLOATMAX_C(0.6931471805599453094172321214581765680755));
      }

      template<typename float_type>
      const float_type e()
      {
        return static_cast<float_type>(FLOATMAX_C(2.7182818284590452353602874713526624977572));
      }

      template<typename float_type>
      const float_type euler_gamma()
      {
        return static_cast<float_type>(FLOATMAX_C(0.5772156649015328606065120900824024310422));
      }
    }
  }

#endif // _CONSTANTS_2012_01_09_H_
