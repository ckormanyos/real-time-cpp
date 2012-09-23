#ifndef _INTEGRAL_2012_01_09_H_
  #define _INTEGRAL_2012_01_09_H_

  #include <cstdint>
  #include <algorithm>

  template<typename value_type,
           typename function_type>
  inline value_type integral(const value_type a,
                             const value_type b,
                             const value_type tol,
                             function_type function)
  {
    std::uint_fast8_t n = 1U;

    value_type h = (b - a);
    value_type I = (function(a) + function(b)) * (h / 2);

    for(std::uint_fast8_t k = 0U; k < 8U; k++)
    {
      h /= 2;

      value_type sum(0);
      for(std::uint_fast8_t j = 1U; j <= n; j++)
      {
        sum += function(a + (value_type((j * 2) - 1) * h));
      }

      const value_type I0 = I;
      I = (I / 2) + (h * sum);

      const value_type ratio = I0 / I;
      const value_type delta = std::abs(ratio - 1);

      if((k > 1U) && (delta < tol))
      {
        break;
      }

      n *= 2;
    }

    return I;
  }

#endif // _INTEGRAL_2012_01_09_H_

/*
#include <cmath>
#include <math/constants/constants.h>
#include <math/calculus/integral.h>

template<typename value_type>
class cyl_bessel_j_integral_rep
{
public:
  cyl_bessel_j_integral_rep(const std::uint_fast8_t N,
                            const value_type& X) : n(N), x(X) { }

  value_type operator()(const value_type& t) const
  {
    // pi * Jn(x) = Int_0^pi [cos(x * sin(t) - n*t) dt]
    return cos(x * sin(t) - (n * t));
  }

private:
  const std::uint_fast8_t n;
  const value_type x;
};

// J2(1.23) = 0.16636938378681407351
double y = integral(0.0,
                    const_pi<double>(),
                    0.01,
                    cyl_bessel_j_integral_rep<double>(2U, 1.23)) / const_pi<double>();
*/
