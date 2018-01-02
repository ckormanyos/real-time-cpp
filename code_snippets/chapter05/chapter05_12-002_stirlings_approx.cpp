// chapter_05_12-002_stirlings_approx.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

template<typename T>
constexpr T pi =
  T(3.1415926535'8979323846'2643383279'5028841972L);

template<typename T>
constexpr T e =
  T(2.7182818284'5904523536'0287471352'6624977572L);

template<typename T>
T tgamma_order_1(T x)
{
  using std::pow;
  using std::sqrt;

  const T      one_over_x = T(1.0L) / x;
  const T sqrt_one_over_x = sqrt(one_over_x);

  const T term0 =    sqrt(T(2.0L) * pi<T>)
                   * sqrt_one_over_x;
  const T term1 = (  sqrt(pi<T> / T(2.0L))
                   * (  sqrt_one_over_x
                      * one_over_x))
                  / T(6.0L);

  return pow ( x / e<T>, x) * (term0 + term1);
}

int main()
{
  constexpr std::streamsize prec =
    std::numeric_limits<float>::max_digits10;

  std::cout << std::setprecision(prec)
            << tgamma_order_1(20.0F)
            << std::endl;
}

// Test tgamma_order_1(20.0F).
// Result:       1.21644237     e+17.
// Compare with: 1.2164510041...e+17.
