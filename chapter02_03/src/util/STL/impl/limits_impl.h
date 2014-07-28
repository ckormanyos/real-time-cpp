///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _LIMITS_IMPL_2010_02_23_H_
  #define _LIMITS_IMPL_2010_02_23_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include <limits.h>
  #include <float.h>

  // Implement some of <limits> for compilers that do not yet support it.
  // The implementation was partly inspired by some concepts in GCC's
  // implementation of <limits>.

  namespace std
  {
    #define CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS  true
    #define CONCEPT_FROM_GLIBCXX_IS_SIGNED(T)    ((static_cast<T>(-1) < static_cast<T>(0)) ? 1 : 0)
    #define CONCEPT_FROM_GLIBCXX_DIGITS(T)       ((static_cast<int>(sizeof(T)) * CHAR_BIT) - CONCEPT_FROM_GLIBCXX_IS_SIGNED(T))
    #define CONCEPT_FROM_GLIBCXX_DIGITS10(T)     static_cast<int>((CONCEPT_FROM_GLIBCXX_DIGITS(T) * 643LL) / 2136LL)
    #define CONCEPT_FROM_GLIBCXX_MAX_DIGITS10(T) static_cast<int>((2 + ((T) * 643LL)) / 2136LL)

    typedef enum enum_float_denorm_style
    {
      denorm_indeterminate = -1,
      denorm_absent        =  0,
      denorm_present       =  1
    }
    float_denorm_style;

    typedef enum enum_float_round_style
    {
      round_indeterminate       = -1,
      round_toward_zero         =  0,
      round_to_nearest          =  1,
      round_toward_infinity     =  2,
      round_toward_neg_infinity =  3
    }
    float_round_style;

    // Forward declaration of the numeric_limits template class.
    template<typename T>
    class numeric_limits;

    class numeric_limits_details
    {
    private:
      static const long long my_long_long_max = 0x7FFFFFFFFFFFFFFFLL;

      // The following values for float, double, and long double are provided
      // in a separate file that is dependent on the AVR architecture.

      static float my_value_that_needs_to_be_provided_flt_infinity();
      static float my_value_that_needs_to_be_provided_flt_quiet_NaN();
      static float my_value_that_needs_to_be_provided_flt_signaling_NaN();
      static float my_value_that_needs_to_be_provided_flt_denorm_min();

      static double my_value_that_needs_to_be_provided_dbl_infinity();
      static double my_value_that_needs_to_be_provided_dbl_quiet_NaN();
      static double my_value_that_needs_to_be_provided_dbl_signaling_NaN();
      static double my_value_that_needs_to_be_provided_dbl_denorm_min();

      static long double my_value_that_needs_to_be_provided_ldbl_infinity();
      static long double my_value_that_needs_to_be_provided_ldbl_quiet_NaN();
      static long double my_value_that_needs_to_be_provided_ldbl_signaling_NaN();
      static long double my_value_that_needs_to_be_provided_ldbl_denorm_min();

      template<typename unsigned_tick_type>
      friend class numeric_limits;
    };

    template<typename T>
    class numeric_limits
    {
    public:
      static const bool is_specialized = false;
      static const int digits = 0;
      static const int digits10 = 0;
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 0;
      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;
      static const bool is_iec559 = false;
      static const bool is_bounded = false;
      static const bool is_modulo = false;
      static const bool traps = false;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;

      static T min() throw()           { return static_cast<T>(0); }
      static T max() throw()           { return static_cast<T>(0); }
      static T lowest() throw()        { return static_cast<T>(0); }
      static T epsilon() throw()       { return static_cast<T>(0); }
      static T round_error() throw()   { return static_cast<T>(0); }
      static T infinity() throw()      { return static_cast<T>(0); }
      static T quiet_NaN() throw()     { return static_cast<T>(0); }
      static T signaling_NaN() throw() { return static_cast<T>(0); }
      static T denorm_min() throw()    { return static_cast<T>(0); }
    };

    // Specialization for bool.
    template<>
    class numeric_limits<bool>
    {
    public:
      static const bool is_specialized = true;

      static bool min() throw()    { return false; }
      static bool max() throw()    { return true; }
      static bool lowest() throw() { return min(); }

      static const int digits = 1;
      static const int digits10 = 0;
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static bool epsilon() throw()     { return false; }
      static bool round_error() throw() { return false; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static bool infinity() throw()      { return false; }
      static bool quiet_NaN() throw()     { return false; }
      static bool signaling_NaN() throw() { return false; }
      static bool denorm_min() throw()    { return false; }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = true;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for char.
    template<>
    class numeric_limits<char>
    {
    public:
      static const bool is_specialized = true;

      static char min() throw()    { return CHAR_MIN; }
      static char max() throw()    { return CHAR_MAX; }
      static char lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(char);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(char);
      static const int max_digits10 = 0;
      static const bool is_signed = CONCEPT_FROM_GLIBCXX_IS_SIGNED(char);
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static char epsilon() throw()     { return 0; }
      static char round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static char infinity() throw()      { return char(); }
      static char quiet_NaN() throw()     { return char(); }
      static char signaling_NaN() throw() { return char(); }
      static char denorm_min() throw()    { return static_cast<char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for signed char.
    template<>
    class numeric_limits<signed char>
    {
    public:
      static const bool is_specialized = true;

      static signed char min() throw()    { return -SCHAR_MAX - 1; }
      static signed char max() throw()    { return  SCHAR_MAX; }
      static signed char lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(signed char);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(signed char);
      static const int max_digits10 = 0;
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static signed char epsilon() throw()     { return 0; }
      static signed char round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static signed char infinity() throw()      { return static_cast<signed char>(0); }
      static signed char quiet_NaN() throw()     { return static_cast<signed char>(0); }
      static signed char signaling_NaN() throw() { return static_cast<signed char>(0); }
      static signed char denorm_min() throw()    { return static_cast<signed char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for unsigned char.
    template<>
    class numeric_limits<unsigned char>
    {
    public:
      static const bool is_specialized = true;

      static unsigned char min() throw()    { return 0; }
      static unsigned char max() throw()    { return (SCHAR_MAX * 2U) + 1; }
      static unsigned char lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(unsigned char);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(unsigned char);
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned char epsilon() throw()     { return 0; }
      static unsigned char round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned char infinity() throw()      { return static_cast<unsigned char>(0); }
      static unsigned char quiet_NaN() throw()     { return static_cast<unsigned char>(0); }
      static unsigned char signaling_NaN() throw() { return static_cast<unsigned char>(0); }
      static unsigned char denorm_min() throw()    { return static_cast<unsigned char>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };


    // Specialization for short.
    template<>
    class numeric_limits<short>
    {
    public:
      static const bool is_specialized = true;

      static short min() throw()    { return -SHRT_MAX - 1; }
      static short max() throw()    { return  SHRT_MAX; }
      static short lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(short);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(short);
      static const int max_digits10 = 0;
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static short epsilon() throw()     { return 0; }
      static short round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static short infinity() throw()      { return short(); }
      static short quiet_NaN() throw()     { return short(); }
      static short signaling_NaN() throw() { return short(); }
      static short denorm_min() throw()    { return short(); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for unsigned short.
    template<>
    class numeric_limits<unsigned short>
    {
    public:
      static const bool is_specialized = true;

      static unsigned short min() throw()    { return 0; }
      static unsigned short max() throw()    { return (SHRT_MAX * 2U) + 1; }
      static unsigned short lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(unsigned short);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(unsigned short);
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned short epsilon() throw()     { return 0; }
      static unsigned short round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned short infinity() throw()      { return static_cast<unsigned short>(0); }
      static unsigned short quiet_NaN() throw()     { return static_cast<unsigned short>(0); }
      static unsigned short signaling_NaN() throw() { return static_cast<unsigned short>(0); }
      static unsigned short denorm_min() throw()    { return static_cast<unsigned short>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for int.
    template<>
    class numeric_limits<int>
    {
    public:
      static const bool is_specialized = true;

      static int min() throw()    { return -INT_MAX - 1; }
      static int max() throw()    { return INT_MAX; }
      static int lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(int);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(int);
      static const int max_digits10 = 0;
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static int epsilon() throw()     { return 0; }
      static int round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static int infinity() throw()      { return static_cast<int>(0); }
      static int quiet_NaN() throw()     { return static_cast<int>(0); }
      static int signaling_NaN() throw() { return static_cast<int>(0); }
      static int denorm_min() throw()    { return static_cast<int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for unsigned int.
    template<>
    class numeric_limits<unsigned int>
    {
    public:
      static const bool is_specialized = true;

      static unsigned int min() throw()    { return 0; }
      static unsigned int max() throw()    { return (INT_MAX * 2U) + 1; }
      static unsigned int lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(unsigned int);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(unsigned int);
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned int epsilon() throw()     { return 0; }
      static unsigned int round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned int infinity() throw()      { return static_cast<unsigned int>(0); }
      static unsigned int quiet_NaN() throw()     { return static_cast<unsigned int>(0); }
      static unsigned int signaling_NaN() throw() { return static_cast<unsigned int>(0); }
      static unsigned int denorm_min() throw()    { return static_cast<unsigned int>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for long.
    template<>
    class numeric_limits<long>
    {
    public:
      static const bool is_specialized = true;

      static long min() throw()    { return -LONG_MAX - 1; }
      static long max() throw()    { return LONG_MAX; }
      static long lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(long);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(long);
      static const int max_digits10 = 0;
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static long epsilon() throw()     { return 0; }
      static long round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static long infinity() throw()      { return static_cast<long>(0); }
      static long quiet_NaN() throw()     { return static_cast<long>(0); }
      static long signaling_NaN() throw() { return static_cast<long>(0); }
      static long denorm_min() throw()    { return static_cast<long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for unsigned long.
    template<>
    class numeric_limits<unsigned long>
    {
    public:
      static const bool is_specialized = true;

      static unsigned long min() throw()    { return 0; }
      static unsigned long max() throw()    { return (LONG_MAX * 2UL) + 1; }
      static unsigned long lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(unsigned long);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(unsigned long);
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned long epsilon() throw()     { return 0; }
      static unsigned long round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned long infinity() throw()      { return static_cast<unsigned long>(0); }
      static unsigned long quiet_NaN() throw()     { return static_cast<unsigned long>(0); }
      static unsigned long signaling_NaN() throw() { return static_cast<unsigned long>(0); }
      static unsigned long denorm_min() throw()    { return static_cast<unsigned long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for long long.
    template<>
    class numeric_limits<long long>
    {
    public:
      static const bool is_specialized = true;

      static long long min() throw()    { return -numeric_limits_details::my_long_long_max - 1; }
      static long long max() throw()    { return  numeric_limits_details::my_long_long_max; }
      static long long lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(long long);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(long long);
      static const int max_digits10 = 0;
      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static long long epsilon() throw()     { return 0; }
      static long long round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static long long infinity() throw()      { return static_cast<long long>(0); }
      static long long quiet_NaN() throw()     { return static_cast<long long>(0); }
      static long long signaling_NaN() throw() { return static_cast<long long>(0); }
      static long long denorm_min() throw()    { return static_cast<long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for unsigned long long.
    template<>
    class numeric_limits<unsigned long long>
    {
    public:
      static const bool is_specialized = true;

      static unsigned long long min() throw()    { return 0; }
      static unsigned long long max() throw()    { return (numeric_limits_details::my_long_long_max * 2ULL) + 1; }
      static unsigned long long lowest() throw() { return min(); }

      static const int digits = CONCEPT_FROM_GLIBCXX_DIGITS(unsigned long long);
      static const int digits10 = CONCEPT_FROM_GLIBCXX_DIGITS10(unsigned long long);
      static const int max_digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;

      static unsigned long long epsilon() throw()     { return 0; }
      static unsigned long long round_error() throw() { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;
      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const float_denorm_style has_denorm = denorm_absent;
      static const bool has_denorm_loss = false;

      static unsigned long long infinity() throw()      { return static_cast<unsigned long long>(0); }
      static unsigned long long quiet_NaN() throw()     { return static_cast<unsigned long long>(0); }
      static unsigned long long signaling_NaN() throw() { return static_cast<unsigned long long>(0); }
      static unsigned long long denorm_min() throw()    { return static_cast<unsigned long long>(0); }

      static const bool is_iec559 = false;
      static const bool is_bounded = true;
      static const bool is_modulo = true;
      static const bool traps = CONCEPT_FROM_GLIBCXX_INTEGRAL_TRAPS;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_toward_zero;
    };

    // Specialization for float.
    template<>
    class numeric_limits<float>
    {
    public:
      static const bool is_specialized = true;

      static float min() throw()    { return  FLT_MIN; }
      static float max() throw()    { return  FLT_MAX; }
      static float lowest() throw() { return -FLT_MAX; }

      static const int digits = FLT_MANT_DIG;
      static const int digits10 = FLT_DIG;
      static const int max_digits10 = CONCEPT_FROM_GLIBCXX_MAX_DIGITS10(FLT_MANT_DIG);
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = FLT_RADIX;

      static float epsilon() throw()     { return FLT_EPSILON; }
      static float round_error() throw() { return 0.5F; }

      static const int min_exponent = FLT_MIN_EXP;
      static const int min_exponent10 = FLT_MIN_10_EXP;
      static const int max_exponent = FLT_MAX_EXP;
      static const int max_exponent10 = FLT_MAX_10_EXP;

      static const bool has_infinity = true;
      static const bool has_quiet_NaN = true;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm = true;
      static const bool has_denorm_loss = false;

      static float infinity() throw()      { return numeric_limits_details::my_value_that_needs_to_be_provided_flt_infinity(); }
      static float quiet_NaN() throw()     { return numeric_limits_details::my_value_that_needs_to_be_provided_flt_quiet_NaN(); }
      static float signaling_NaN() throw() { return numeric_limits_details::my_value_that_needs_to_be_provided_flt_signaling_NaN(); }
      static float denorm_min() throw()    { return numeric_limits_details::my_value_that_needs_to_be_provided_flt_denorm_min(); }

      static const bool is_iec559 = true;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_to_nearest;
    };

    // Specialization for double.
    template<>
    class numeric_limits<double>
    {
    public:
      static const bool is_specialized = true;

      static double min() throw()    { return  DBL_MIN; }
      static double max() throw()    { return  DBL_MAX; }
      static double lowest() throw() { return -DBL_MAX; }

      static const int digits = DBL_MANT_DIG;
      static const int digits10 = DBL_DIG;
      static const int max_digits10 = CONCEPT_FROM_GLIBCXX_MAX_DIGITS10(DBL_MANT_DIG);
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2; // DBL_RADIX;

      static double epsilon() throw()     { return DBL_EPSILON; }
      static double round_error() throw() { return 0.5; }

      static const int min_exponent = DBL_MIN_EXP;
      static const int min_exponent10 = DBL_MIN_10_EXP;
      static const int max_exponent = DBL_MAX_EXP;
      static const int max_exponent10 = DBL_MAX_10_EXP;

      static const bool has_infinity = true;
      static const bool has_quiet_NaN = true;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm = true;
      static const bool has_denorm_loss = false;

      static double infinity() throw()      { return numeric_limits_details::my_value_that_needs_to_be_provided_dbl_infinity(); }
      static double quiet_NaN() throw()     { return numeric_limits_details::my_value_that_needs_to_be_provided_dbl_quiet_NaN(); }
      static double signaling_NaN() throw() { return numeric_limits_details::my_value_that_needs_to_be_provided_dbl_signaling_NaN(); }
      static double denorm_min() throw()    { return numeric_limits_details::my_value_that_needs_to_be_provided_dbl_denorm_min(); }

      static const bool is_iec559 = true;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_to_nearest;
    };

    // Specialization for long double.
    template<>
    class numeric_limits<long double>
    {
    public:
      static const bool is_specialized = true;

      static long double min() throw()    { return  LDBL_MIN; }
      static long double max() throw()    { return  LDBL_MAX; }
      static long double lowest() throw() { return -LDBL_MAX; }

      static const int digits = LDBL_MANT_DIG;
      static const int digits10 = LDBL_DIG;
      static const int max_digits10 = CONCEPT_FROM_GLIBCXX_MAX_DIGITS10(LDBL_MANT_DIG);
      static const bool is_signed = true;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 2; // DBL_RADIX;

      static long double epsilon() throw()     { return LDBL_EPSILON; }
      static long double round_error() throw() { return 0.5; }

      static const int min_exponent = LDBL_MIN_EXP;
      static const int min_exponent10 = LDBL_MIN_10_EXP;
      static const int max_exponent = LDBL_MAX_EXP;
      static const int max_exponent10 = LDBL_MAX_10_EXP;

      static const bool has_infinity = true;
      static const bool has_quiet_NaN = true;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm = true;
      static const bool has_denorm_loss = false;

      static long double infinity() throw()      { return numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_infinity(); }
      static long double quiet_NaN() throw()     { return numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_quiet_NaN(); }
      static long double signaling_NaN() throw() { return numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_signaling_NaN(); }
      static long double denorm_min() throw()    { return numeric_limits_details::my_value_that_needs_to_be_provided_ldbl_denorm_min(); }

      static const bool is_iec559 = true;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool traps = false;
      static const bool tinyness_before = false;
      static const float_round_style round_style = round_to_nearest;
    };
  }

#endif // _LIMITS_IMPL_2010_02_23_H_
