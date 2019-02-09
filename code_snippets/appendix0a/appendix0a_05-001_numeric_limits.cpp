///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_05-001_numeric_limits.cpp

// NOTE: This file contains a non-standard extension
// of namespace std for purpose of example only.

namespace std
{
  typedef enum float_denorm_style { denorm_absent }     float_denorm_style;
  typedef enum float_round_style  { round_toward_zero } float_round_style;

  template<class T>
  class numeric_limits
  {
  public:
    static constexpr bool is_specialized = false;
    static constexpr T min   () { return T(); }
    static constexpr T max   () { return T(); }
    static constexpr T lowest() { return T(); }

    static constexpr int digits       = 0;
    static constexpr int digits10     = 0;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed   = false;
    static constexpr bool is_integer  = false;
    static constexpr bool is_exact    = false;
    static constexpr int radix        = 0;
    static constexpr T epsilon()     { return T(); }
    static constexpr T round_error() { return T(); }

    static constexpr int min_exponent   = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent   = 0;
    static constexpr int max_exponent10 = 0;

    static constexpr bool has_infinity      = false;
    static constexpr bool has_quiet_NaN     = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm
      = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr T infinity     () { return T(); }
    static constexpr T quiet_NaN    () { return T(); }
    static constexpr T signaling_NaN() { return T(); }
    static constexpr T denorm_min   () { return T(); }

    static constexpr bool is_iec559  = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo  = false;
    static constexpr bool traps      = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style
      = round_toward_zero;
  };
}

namespace std
{
  template<>
  class numeric_limits<int>
  {
  public:
    static constexpr bool is_specialized = true;

    static constexpr int min() { return 0; }
    static constexpr int max()
      { return +2147483647; }
    static constexpr int lowest()
      { return -max() - 1; }

    static constexpr int digits       = 32;
    static constexpr int digits10     =  9;
    static constexpr int max_digits10 =  9;
    static constexpr bool is_signed   = false;
    static constexpr bool is_integer  = true;
    static constexpr bool is_exact    = true;
    static constexpr int radix        =  2;
    static constexpr int epsilon() { return 0; }
    static constexpr int round_error()
      { return 0; }

    static constexpr int min_exponent   = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent   = 0;
    static constexpr int max_exponent10 = 0;

    static constexpr bool has_infinity      = false;
    static constexpr bool has_quiet_NaN     = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm
      = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr int infinity () { return 0; }
    static constexpr int quiet_NaN() { return 0; }
    static constexpr int signaling_NaN()
      { return 0; }
    static constexpr int denorm_min() { return 0; }

    static constexpr bool is_iec559       = false;
    static constexpr bool is_bounded      = false;
    static constexpr bool is_modulo       = false;
    static constexpr bool traps           = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style
      = round_toward_zero;
  };
}

// Do not use <iostream> here because that
// will probably pull in <limits>.
#include <cstdio>

constexpr int n_max = std::numeric_limits<int>::max   ();
constexpr int n_min = std::numeric_limits<int>::min   ();
constexpr int n_low = std::numeric_limits<int>::lowest();

int main()
{
  printf("n_max: %d\n", n_max);
  printf("n_min: %d\n", n_min);
  printf("n_low: %d\n", n_low);
}
