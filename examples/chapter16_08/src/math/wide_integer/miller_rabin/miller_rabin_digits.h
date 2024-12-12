///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MILLER_RABIN_DIGITS_2024_12_12_H
  #define MILLER_RABIN_DIGITS_2024_12_12_H

  #define WIDE_INTEGER_DISABLE_IOSTREAM
  #define WIDE_INTEGER_DISABLE_TO_STRING
  #define WIDE_INTEGER_DISABLE_FLOAT_INTEROP
  #define WIDE_INTEGER_DISABLE_IMPLEMENT_UTIL_DYNAMIC_ARRAY
  #define WIDE_INTEGER_DISABLE_TRIVIAL_COPY_AND_STD_LAYOUT_CHECKS

  // Note that -DWIDE_INTEGER_NAMESPACE=ckormanyos is defined
  // on the compiler command line.

  #include <math/wide_integer/uintwide_t.h>

  WIDE_INTEGER_NAMESPACE_BEGIN

  namespace math { namespace wide_integer {

  constexpr unsigned miller_rabin_digits { static_cast<unsigned>(UINT16_C(128)) };

  } // namespace wide_integer
  } // namespace math

  WIDE_INTEGER_NAMESPACE_END

#endif // MILLER_RABIN_DIGITS_2024_12_12_H
