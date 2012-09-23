#ifndef _CONSTANTS_2012_01_09_H_
  #define _CONSTANTS_2012_01_09_H_

  template<typename T>
  constexpr inline T const_sqrt2()
  {
    return T(1.4142135623730950488016887242096980785697);
  }

  template<typename T>
  constexpr inline T const_pi()
  {
    return T(3.1415926535897932384626433832795028841972);
  }

  template<typename T>
  constexpr inline T const_sqrt_pi()
  {
    return T(1.7724538509055160272981674833411451827975);
  }

  template<typename T>
  constexpr inline T const_ln2()
  {
    return T(0.6931471805599453094172321214581765680755);
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

#endif // _CONSTANTS_2012_01_09_H_
