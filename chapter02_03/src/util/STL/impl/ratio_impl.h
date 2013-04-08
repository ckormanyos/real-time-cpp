///////////////////////////////////////////////////////////////////////////////
/// \author (c) Marco Paland (info@paland.com)
///             2011-2012, PALANDesign Hannover, Germany
///
/// \license LGPLv3
/// ratio is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// ratio is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser Public License for more details.
/// You should have received a copy of the GNU Lesser Public License
/// along with ratio. If not, see <http://www.gnu.org/licenses/>.
///
///
/// \brief <ratio> implementation of C++11
///
/// This class implements the <ratio> class of C++11 for compilers which
/// do not support this standard. It has NO dependencies to other libs
///
///////////////////////////////////////////////////////////////////////////////

#ifndef _RATIO_IMPL_2012_06_01_H_
  #define _RATIO_IMPL_2012_06_01_H_

  #include "cstdint_impl.h"

  namespace std
  {

  // helper functions
  template<class T, T v>
  struct _integral_constant
  {
    static const T value = v;
    typedef T value_type;
    typedef _integral_constant type;
    operator value_type() const { return value; }
  };

  template<intmax_t Pn>
  struct _static_sign : _integral_constant<intmax_t, (Pn < 0) ? -1 : 1>
  { };

  template<intmax_t Pn>
  struct _static_abs : _integral_constant<intmax_t, Pn * _static_sign<Pn>::value>
  { };

  template<intmax_t Pn, intmax_t Qn>
  struct _static_gcd;

  template<intmax_t Pn, intmax_t Qn>
  struct _static_gcd : _static_gcd<Qn, (Pn % Qn)>
  { };

  template<intmax_t Pn>
  struct _static_gcd<Pn, 0> : _integral_constant<intmax_t, _static_abs<Pn>::value>
  { };

  template<intmax_t Qn>
  struct _static_gcd<0, Qn> : _integral_constant<intmax_t, _static_abs<Qn>::value>
  { };

  template<intmax_t Pn, intmax_t Qn>
  struct _safe_multiply
  {
    static const intmax_t value = Pn * Qn;
  };

  template<intmax_t Pn, intmax_t Qn>
  struct _safe_add
  {
    static const intmax_t value = Pn + Qn;
  };


  // ratio
  template<intmax_t Num, intmax_t Den = 1>
  struct ratio {
    static const intmax_t num = Num * _static_sign<Den>::value / _static_gcd<Num, Den>::value;
    static const intmax_t den = _static_abs<Den>::value / _static_gcd<Num, Den>::value;
    typedef ratio<num, den> type;
  };

//  template<intmax_t Num, intmax_t Den>
//  intmax_t ratio<Num, Den>::num;

//  template<intmax_t Num, intmax_t Den>
//  intmax_t ratio<Num, Den>::den;


  template<typename R1, typename R2>
  struct ratio_add
  {
  private:
    static const intmax_t gcd  = _static_gcd<R1::den, R2::den>::value;
    static const intmax_t   n  = _safe_add<_safe_multiply<R1::num, (R2::den / gcd)>::value,
                                           _safe_multiply<R2::num, (R1::den / gcd)>::value>::value;
    static const intmax_t gcd2 = _static_gcd<n, gcd>::value;
      
  public:
    typedef ratio<n / gcd2, _safe_multiply<R1::den / gcd2, R2::den / gcd>::value> type;
    static const intmax_t num = type::num;
    static const intmax_t den = type::den;
  };

  template<typename R1, typename R2>
  const intmax_t ratio_add<R1, R2>::num;

  template<typename R1, typename R2>
  const intmax_t ratio_add<R1, R2>::den;


  template<typename R1, typename R2>
  struct ratio_subtract {
    typedef typename ratio_add<R1, ratio<-R2::num, R2::den> >::type type;
    static const intmax_t num = type::num;
    static const intmax_t den = type::den;
  };

  template<typename R1, typename R2>
  const intmax_t ratio_subtract<R1, R2>::num;

  template<typename R1, typename R2>
  const intmax_t ratio_subtract<R1, R2>::den;


  template<typename R1, typename R2>
  struct ratio_multiply {
  private:
    static const intmax_t gcd1 = _static_gcd<R1::num, R2::den>::value;
    static const intmax_t gcd2 = _static_gcd<R2::num, R1::den>::value;

  public:
    typedef ratio<_safe_multiply<(R1::num / gcd1), (R2::num / gcd2)>::value,
                  _safe_multiply<(R1::den / gcd2), (R2::den / gcd1)>::value> type;
    static const intmax_t num = type::num;
    static const intmax_t den = type::den;
  };

  template<typename R1, typename R2>
  const intmax_t ratio_multiply<R1, R2>::num;

  template<typename R1, typename R2>
  const intmax_t ratio_multiply<R1, R2>::den;


  template<typename R1, typename R2>
  struct ratio_divide {
    typedef typename ratio_multiply<R1, ratio<R2::den, R2::num> >::type type;
    static const intmax_t num = type::num;
    static const intmax_t den = type::den;
  };

  template<typename R1, typename R2>
  const intmax_t ratio_divide<R1, R2>::num;

  template<typename R1, typename R2>
  const intmax_t ratio_divide<R1, R2>::den;


  // ratio comparison
  template<typename R1, typename R2>
  struct ratio_equal : _integral_constant<bool, R1::num == R2::num && R1::den == R2::den>
  { };

  template<typename R1, typename R2>
  struct ratio_not_equal : _integral_constant<bool, !ratio_equal<R1, R2>::value>
  { };

  template<typename R1, typename R2>
  struct _ratio_less_impl_2;

  template<typename R1, typename R2, intmax_t Q1 = R1::num / R1::den, intmax_t Q2 = R2::num / R2::den, bool eq = (Q1 == Q2)>
  struct _ratio_less_impl_1 : _ratio_less_impl_2<ratio<R1::num % R1::den, R1::den>, ratio<R2::num % R2::den, R2::den> >::type
  { };

  template<typename R1, typename R2, intmax_t Q1, intmax_t Q2>
  struct _ratio_less_impl_1<R1, R2, Q1, Q2, false> : _integral_constant<bool, (Q1 < Q2)>
  { };

  template<typename R1, typename R2>
  struct _ratio_less_impl_2 : _ratio_less_impl_1<ratio<R2::den, R2::num>, ratio<R1::den, R1::num> >::type
  { };

  template<intmax_t D1, typename R2>
  struct _ratio_less_impl_2<ratio<0, D1>, R2> : _integral_constant<bool, true>
  { };

  template<typename R1, intmax_t D2>
  struct _ratio_less_impl_2<R1, ratio<0, D2> > : _integral_constant<bool, false>
  { };

  template<intmax_t D1, intmax_t D2>
  struct _ratio_less_impl_2<ratio<0, D1>, ratio<0, D2> > : _integral_constant<bool, false>
  { };

  template<typename R1, typename R2,
           bool = (R1::num == 0 || R2::num == 0 ||
                   (_static_sign<R1::num>::value != _static_sign<R2::num>::value)
                  ),
           bool = (_static_sign<R1::num>::value == -1 &&
                   _static_sign<R2::num>::value == -1)>
  struct _ratio_less_impl : _ratio_less_impl_1<R1, R2>::type
  { };

  template<typename R1, typename R2>
  struct _ratio_less_impl<R1, R2, true, false> : _integral_constant<bool, (R1::num) < (R2::num)>
  { };

  template<typename R1, typename R2>
  struct _ratio_less_impl<R1, R2, false, true> : _ratio_less_impl_1<ratio<-R2::num, R2::den>, ratio<-R1::num, R1::den> >::type
  { };

  template<typename R1, typename R2>
  struct ratio_less : _ratio_less_impl<R1, R2>::type
  { };

  template<typename R1, typename R2>
  struct ratio_less_equal : _integral_constant<bool, !ratio_less<R2, R1>::value>
  { };

  template<typename R1, typename R2>
  struct ratio_greater : _integral_constant<bool, ratio_less<R2, R1>::value>
  { };

  template<typename R1, typename R2>
  struct ratio_greater_equal : _integral_constant<bool, !ratio_less<R1, R2>::value>
  { };

  typedef ratio<1, 1000000000000000000> atto;
  typedef ratio<1,    1000000000000000> femto;
  typedef ratio<1,       1000000000000> pico;
  typedef ratio<1,          1000000000> nano;
  typedef ratio<1,             1000000> micro;
  typedef ratio<1,                1000> milli;
  typedef ratio<1,                 100> centi;
  typedef ratio<1,                  10> deci;
  typedef ratio<                 10, 1> deca;
  typedef ratio<                100, 1> hecto;
  typedef ratio<               1000, 1> kilo;
  typedef ratio<            1000000, 1> mega;
  typedef ratio<         1000000000, 1> giga;
  typedef ratio<      1000000000000, 1> tera;
  typedef ratio<   1000000000000000, 1> peta;
  typedef ratio<1000000000000000000, 1> exa;
} // namespace std

#endif // _RATIO_IMPL_2012_06_01_H_
