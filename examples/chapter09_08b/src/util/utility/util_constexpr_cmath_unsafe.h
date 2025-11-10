///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_CONSTEXPR_CMATH_UNSAFE_2023_11_26_H // NOLINT(llvm-header-guard)
  #define UTIL_CONSTEXPR_CMATH_UNSAFE_2023_11_26_H

  #include <limits>

  namespace util {

  template <typename FloatingPointType>
  constexpr auto frexp_unsafe(FloatingPointType x, int* expptr) -> FloatingPointType
  {
    using local_floating_point_type = FloatingPointType;

    local_floating_point_type result { };

    const auto b_neg = (x < static_cast<local_floating_point_type>(0.0L));

    if((x > static_cast<local_floating_point_type>(0.0L)) || b_neg)
    {
      local_floating_point_type f = (b_neg ? -x : x); // NOLINT(altera-id-dependent-backward-branch)

      auto e2 = static_cast<int>(INT8_C(0));

      constexpr auto two_pow_plus32 =
        static_cast<long double>
        (
            static_cast<long double>(0x10000)
          * static_cast<long double>(0x10000)
        );

      constexpr auto two_pow_minus32 = static_cast<long double>(0.000000000232830643653869628906250000L);

      // TBD: Maybe optimize exponent reduction with a more clever kind of binary searching.

      while(f >= static_cast<local_floating_point_type>(two_pow_plus32)) // NOLINT(altera-id-dependent-backward-branch)
      {
        f   = static_cast<local_floating_point_type>(f / static_cast<local_floating_point_type>(two_pow_plus32));
        e2 += static_cast<int>(INT8_C(32));
      }

      while(f <= static_cast<local_floating_point_type>(two_pow_minus32)) // NOLINT(altera-id-dependent-backward-branch)
      {
        f   = static_cast<local_floating_point_type>(f * static_cast<local_floating_point_type>(two_pow_plus32));
        e2 -= static_cast<int>(INT8_C(32));
      }

      constexpr auto one_ldbl = static_cast<long double>(1.0L);
      constexpr auto two_ldbl = static_cast<long double>(2.0L);

      while(f < static_cast<local_floating_point_type>(one_ldbl)) // NOLINT(altera-id-dependent-backward-branch)
      {
        f = static_cast<local_floating_point_type>(f * static_cast<local_floating_point_type>(two_ldbl));

        --e2;
      }

      while(f >= static_cast<local_floating_point_type>(one_ldbl)) // NOLINT(altera-id-dependent-backward-branch)
      {
        f = static_cast<local_floating_point_type>(f / static_cast<local_floating_point_type>(two_ldbl));

        ++e2;
      }

      if(expptr != nullptr)
      {
        *expptr = e2;
      }

      result = ((!b_neg) ? f : -f);
    }
    else
    {
      if(expptr != nullptr)
      {
        *expptr = static_cast<int>(INT8_C(0));
      }
    }

    return result;
  }

  } // namespace util

#endif // UTIL_CONSTEXPR_CMATH_UNSAFE_2023_11_26_H
