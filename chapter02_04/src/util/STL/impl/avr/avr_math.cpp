/*
#include "../cstdint_impl.h"
#include "../cmath_impl.h"
#include "../array_impl.h"
#include "../limits_impl.h"
#include "../initializer_list_impl.h"
#include "../xnumeric_impl.h"

// The tgamma function is implemented here for the AVR.
// This provides an example of a special function calculation.
// Note that double is the same as float for AVR.

namespace
{
  constexpr double pi = 3.14159265358979323846264338327950288419716939937510582;

  double gamma(double x)
  {
    double g;

    if(x < double(0.03))
    {
      // Small argument Taylor series for 1/gamma.

      const double x2 = x  * x;
      const double x3 = x2 * x;
      const double bot =    x
                         + (x2 * double(0.577215665))
                         - (x3 * double(0.655878072))
                         - ((x2 * x2) * double(0.042002635));
      g = double(1) / bot;
    }
    else
    {
      // Abramowitz & Stegun Section 6.1.36 (polynomial approximation with 8 coefficients).

      constexpr std::initializer_list<double> coefs_a_table_6_1_36
      {
        double(-0.577191652),
        double(+0.988205891),
        double(-0.897056937),
        double(+0.918206857),
        double(-0.756704078),
        double(+0.482199394),
        double(-0.193527818),
        double(+0.035868343)
      };

      const std::array<double, 8U> powers_of_x
      {{
        x,
        powers_of_x[0] * x,
        powers_of_x[1] * x,
        powers_of_x[2] * x,
        powers_of_x[3] * x,
        powers_of_x[4] * x,
        powers_of_x[5] * x,
        powers_of_x[6] * x
      }};

      g = xnumeric::xinner_product(coefs_a_table_6_1_36.begin(),
                                   coefs_a_table_6_1_36.end(),
                                   powers_of_x.begin(),
                                   double(1)) / x;
    }

    return g;
  }
}

double tgamma(double x)
{
  // Check for pure zero argument.
  if(x == 0.0)
  {
    return std::numeric_limits<double>::quiet_NaN();
  }

  // Check for overflow and underflow.
  if(    (x > 35.0)
     || ((x > -1.0E-38) && (x < 1.0E-38))
    )
  {
    return std::numeric_limits<double>::infinity();
  }

  if((x == 1.0) || (x == 2.0))
  {
    return 1.0;
  }

  // Use a positive argument for the Gamma calculation.
  const bool b_neg = (x < 0.0);
  double xx = ((!b_neg) ? x : -x);

  // Get any integer recursion and scale the argument.
  const std::uint16_t nx = std::uint16_t(::floor(xx));
  xx -= double(nx);

  double g = ::gamma(xx);

  // Do the recursion if necessary.
  for(std::uint16_t recur = 0U; recur < nx; ++recur)
  {
    g *= xx;
    ++xx;
  }

  // Return (and possibly reflect) the result.
  if(false == b_neg)
  {
    return g;
  }
  else
  {
    return -::pi / ((xx * g) * ::sin(::pi * xx));
  }
}
*/
