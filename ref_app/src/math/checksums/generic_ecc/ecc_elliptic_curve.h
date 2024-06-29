///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work uses (significantly) translated and modified parts
// of andreacorbellini/ecc
//   see also: https://github.com/andreacorbellini/ecc
//   and also: https://github.com/andreacorbellini/ecc/blob/master/scripts/ecdsa.py

// Full original andreacorbellini/ecc copyright information follows.
/*----------------------------------------------------------------------------

The MIT License (MIT)

Copyright (c) 2015 Andrea Corbellini

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

-----------------------------------------------------------------------------*/

// For algorithm description of ECDSA, see
// D. Hankerson, A. Menezes, S. Vanstone, "Guide to Elliptic
// Curve Cryptography", Springer 2004, Chapter 4, in particular
// Algorithm 4.24 (keygen on page 180), and Algorithms 4.29 and 4.30
// (sign/verify on page 184).

// For another algorithm description of ECDSA,
//   see also: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-5.pdf

#ifndef ECC_ELLIPTIC_CURVE_2023_02_18_H
#define ECC_ELLIPTIC_CURVE_2023_02_18_H

#include <random>
#include <utility>

#define WIDE_INTEGER_DISABLE_IOSTREAM
#define WIDE_INTEGER_DISABLE_TO_STRING
#define WIDE_INTEGER_DISABLE_IMPLEMENT_UTIL_DYNAMIC_ARRAY
#define WIDE_INTEGER_DISABLE_TRIVIAL_COPY_AND_STD_LAYOUT_CHECKS

#if !defined(WIDE_INTEGER_NAMESPACE)
#define WIDE_INTEGER_NAMESPACE ckormanyos
#endif

#include <math/wide_integer/uintwide_t.h>

namespace generic_ecc
{
  template<const unsigned CurveBits,
           typename LimbType,
           const char* CoordX,
           const char* CoordY>
  struct ecc_point
  {
    using uint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(CurveBits), LimbType, void, false>;

    using double_sint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(2))), LimbType, void, true>;

    static_assert(static_cast<unsigned>(std::numeric_limits<uint_type>::digits) == CurveBits,
                  "Error: Wrong number of bits in the unsigned integer type of the point");

    using limb_type = typename uint_type::limb_type;

    using point_type =
      struct point_type
      {
        constexpr point_type(double_sint_type x = static_cast<double_sint_type>(static_cast<unsigned>(UINT8_C(0))), // NOLINT(google-explicit-constructor,hicpp-explicit-conversions,bugprone-easily-swappable-parameters)
                             double_sint_type y = static_cast<double_sint_type>(static_cast<unsigned>(UINT8_C(0)))) noexcept
          : my_x(x),
            my_y(y) { }

        double_sint_type my_x; // NOLINT(misc-non-private-member-variables-in-classes)
        double_sint_type my_y; // NOLINT(misc-non-private-member-variables-in-classes)
      };
  };

  template<const unsigned CurveBits,
           typename LimbType,
           const char* CurveName,
           const char* FieldCharacteristicP,
           const char* CurveCoefficientA,
           const char* CurveCoefficientB,
           const char* CoordGx,
           const char* CoordGy,
           const char* SubGroupOrderN,
           const int   SubGroupCoFactorH,
           typename HashType>
  struct ecc_elliptic_curve : public ecc_point<CurveBits, LimbType, CoordGx, CoordGy>
  {
    using hash_type = HashType;

    using base_class_type = ecc_point<CurveBits, LimbType, CoordGx, CoordGy>; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    using point_type       = typename base_class_type::point_type;
    using uint_type        = typename base_class_type::uint_type;
    using double_sint_type = typename base_class_type::double_sint_type;
    using limb_type        = typename base_class_type::limb_type;

    using keypair_type = std::pair<uint_type, std::pair<uint_type, uint_type>>;

    using quadruple_sint_type   = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(4))),  limb_type, void, true>;
    using sexatuple_sint_type   = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(6))),  limb_type, void, true>;
    using duodectuple_sint_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uintwide_t<static_cast<WIDE_INTEGER_NAMESPACE::math::wide_integer::size_t>(std::numeric_limits<uint_type>::digits * static_cast<int>(INT8_C(12))), limb_type, void, true>;

    static constexpr auto curve_p () noexcept -> double_sint_type { return double_sint_type(FieldCharacteristicP); } // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    static constexpr auto curve_a () noexcept -> double_sint_type { return double_sint_type(CurveCoefficientA); }    // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    static constexpr auto curve_b () noexcept -> double_sint_type { return double_sint_type(CurveCoefficientB); }    // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    static constexpr auto curve_gx() noexcept -> double_sint_type { return double_sint_type(CoordGx); }              // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    static constexpr auto curve_gy() noexcept -> double_sint_type { return double_sint_type(CoordGy); }              // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    static constexpr auto curve_n () noexcept -> double_sint_type { return double_sint_type(SubGroupOrderN); }       // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)

    static auto inverse_mod(const double_sint_type& k, const double_sint_type& p) -> double_sint_type // NOLINT(misc-no-recursion)
    {
      // Returns the inverse of k modulo p.
      // This function returns the only integer x such that (x * k) % p == 1.
      // k must be non-zero and p must be a prime.

      if(k == 0)
      {
        // Error: Division by zero.
        return 0; // LCOV_EXCL_LINE
      }

      if(k < 0)
      {
        // k ** -1 = p - (-k) ** -1  (mod p)
        return p - inverse_mod(-k, p);
      }

      // Extended Euclidean algorithm.
      auto s = double_sint_type(0U); auto old_s = double_sint_type(1U);
      auto r = double_sint_type(p) ; auto old_r = double_sint_type(k);

      while(r != 0U) // NOLINT(altera-id-dependent-backward-branch)
      {
        const auto quotient = divmod(old_r, r).first;

        const auto tmp_r = r; r = old_r - (quotient * r); old_r = tmp_r;
        const auto tmp_s = s; s = old_s - (quotient * s); old_s = tmp_s;
      }

      return divmod(old_s, p).second;
    }

    // Functions that work on curve points

    static auto is_on_curve(const point_type& point) -> bool
    {
      // Returns True if the given point lies on the elliptic curve.
      if((point.my_x == 0) && (point.my_y == 0))
      {
        // None represents the point at infinity.
        return true;
      }

      // Test the condition:
      //   (y * y - x * x * x - curve.a * x -curve.b) % curve.p == 0

      const auto num =
        quadruple_sint_type
        (
            (quadruple_sint_type(point.my_y) *  quadruple_sint_type(point.my_y))
          - (quadruple_sint_type(point.my_x) * (quadruple_sint_type(point.my_x) * quadruple_sint_type(point.my_x)))
          - (quadruple_sint_type(point.my_x) *  quadruple_sint_type(curve_a()))
          -  quadruple_sint_type(curve_b())
        );

      const auto divmod_result = divmod(num, quadruple_sint_type(curve_p())).second;

      return (divmod_result == 0);
    }

    // LCOV_EXCL_START
    static constexpr auto point_neg(const point_type& point) -> point_type
    {
      // Returns the negation of the point on the curve (i.e., -point).

      return
      {
        ((point.my_x == 0) && (point.my_y == 0))
          ? point_type(0)
          : point_type
            {
               point.my_x,
              -divmod(point.my_y, curve_p()).second
            }
      };
    }
    // LCOV_EXCL_STOP

    static auto point_add(const point_type& point1, const point_type& point2) -> point_type
    {
      // Returns the result of (point1 + point2) according to the group law.

      const auto& x1 = point1.my_x; const auto& y1 = point1.my_y;
      const auto& x2 = point2.my_x; const auto& y2 = point2.my_y;

      if((x1 == 0) && (y1 == 0))
      {
        // 0 + point2 = point2
        return point_type(point2);
      }

      if((x2 == 0) && (y2 == 0))
      {
        // point1 + 0 = point1
        return point_type(point1); // LCOV_EXCL_LINE
      }

      if((x1 == x2) && (y1 != y2))
      {
        // point1 + (-point1) = 0
        return point_type { }; // LCOV_EXCL_LINE
      }

      // Differentiate the cases (point1 == point2) and (point1 != point2).

      const auto m =
        quadruple_sint_type
        (
          (x1 == x2)
            ? (quadruple_sint_type(x1) * quadruple_sint_type(x1) * 3 + quadruple_sint_type(curve_a())) * quadruple_sint_type(inverse_mod(y1 * 2, curve_p()))
            : quadruple_sint_type(y1 - y2) * quadruple_sint_type(inverse_mod(x1 - x2, curve_p()))
        );

      const auto x3 =
        duodectuple_sint_type
        (
          duodectuple_sint_type(m) * duodectuple_sint_type(m) - duodectuple_sint_type(x1 + x2)
        );

      auto y3 =
        duodectuple_sint_type
        (
          duodectuple_sint_type(y1) + duodectuple_sint_type(m) * (x3 - duodectuple_sint_type(x1))
        );

      y3.negate();

      return
      {
        double_sint_type(divmod(x3, duodectuple_sint_type(curve_p())).second),
        double_sint_type(divmod(y3, duodectuple_sint_type(curve_p())).second)
      };
    }

    static auto scalar_mult(const double_sint_type& k, const point_type& point) -> point_type // NOLINT(misc-no-recursion)
    {
      // Returns k * point computed using the double and point_add algorithm.

      if(((k % curve_n()) == 0) || ((point.my_x == 0) && (point.my_y == 0)))
      {
        return point_type { }; // LCOV_EXCL_LINE
      }

      if(k < 0)
      {
        // k * point = -k * (-point)
        return scalar_mult(-k, point_neg(point)); // LCOV_EXCL_LINE
      }

      point_type result { };
      point_type addend = point;

      double_sint_type k_val(k);

      while(k_val != 0) // NOLINT(altera-id-dependent-backward-branch)
      {
        const auto lo_bit =
          static_cast<unsigned>
          (
            static_cast<unsigned>(k_val) & static_cast<unsigned>(UINT8_C(1))
          );

        if(lo_bit != static_cast<unsigned>(UINT8_C(0)))
        {
          // Add.
          result = point_add(result, addend);
        }

        // Double.
        addend = point_add(addend, addend);

        k_val >>= static_cast<unsigned>(UINT8_C(1));
      }

      return result;
    }

    template<typename UnknownWideUintType>
    static auto get_pseudo_random_uint() -> UnknownWideUintType
    {
      using local_wide_unsigned_integer_type = UnknownWideUintType;

      using local_distribution_type = WIDE_INTEGER_NAMESPACE::math::wide_integer::uniform_int_distribution<local_wide_unsigned_integer_type::my_width2, typename local_wide_unsigned_integer_type::limb_type>;

      using local_random_engine_type = std::linear_congruential_engine<std::uint32_t, UINT32_C(48271), UINT32_C(0), UINT32_C(2147483647)>;

      const auto seed_value = static_cast<typename local_random_engine_type::result_type>(static_cast<std::uint32_t>(UINT32_C(0xF00DCAFE)));

      local_random_engine_type generator(seed_value);

      local_distribution_type dist;

      const auto unsigned_pseudo_random_value = dist(generator);

      return unsigned_pseudo_random_value;
    }

    static auto make_keypair(const uint_type* p_uint_seed = nullptr) -> keypair_type
    {
      // This subroutine generate a random private-public key pair.
      // The input parameter p_uint_seed can, however, be used to
      // provide a fixed-input value for the private key.

      // TBD: Be sure to limit to random.randrange(1, curve.n).

      const auto private_key =
        uint_type
        (
          (p_uint_seed == nullptr) ? get_pseudo_random_uint<uint_type>() : *p_uint_seed
        );

      const auto public_key  = scalar_mult(private_key, { curve_gx(), curve_gy() } );

      return
      {
        private_key,
        {
          uint_type(public_key.my_x),
          uint_type(public_key.my_y)
        }
      };
    }

    static auto sign_message_ph(const uint_type& private_key,
                                const uint_type& z_msg_hash,
                                const uint_type* p_uint_seed) -> std::pair<uint_type, uint_type>
    {
      const auto z = quadruple_sint_type(z_msg_hash);

      double_sint_type r { };
      double_sint_type s { };

      const auto n = quadruple_sint_type(curve_n());

      const auto pk = quadruple_sint_type(private_key);

      while((r == 0) || (s == 0)) // NOLINT(altera-id-dependent-backward-branch)
      {
        // TBD: Be sure to limit to random.randrange(1, curve.n).
        const auto k =
          double_sint_type
          (
            (p_uint_seed == nullptr) ? static_cast<double_sint_type>(get_pseudo_random_uint<uint_type>()) : static_cast<double_sint_type>(*p_uint_seed)
          );

        const auto pt = scalar_mult(k, { curve_gx(), curve_gy() } );

        r = divmod(pt.my_x, curve_n()).second;

        const auto num =
        (
           (quadruple_sint_type(z) + (quadruple_sint_type(r) * pk))
          * quadruple_sint_type(inverse_mod(k, curve_n()))
        );

        s = double_sint_type(divmod(num, n).second);
      }

      return
      {
        uint_type(r),
        uint_type(s)
      };
    }

    static auto verify_signature_ph(const std::pair<uint_type, uint_type>& pub,
                                    const uint_type&                       z_msg_hash,
                                    const std::pair<uint_type, uint_type>& sig) -> bool
    {
      const auto w = quadruple_sint_type(inverse_mod(sig.second, curve_n()));

      const auto n = quadruple_sint_type(curve_n());

      const auto u1 = double_sint_type(divmod(quadruple_sint_type(z_msg_hash) * w, n).second);
      const auto u2 = double_sint_type(divmod(quadruple_sint_type(sig.first)  * w, n).second);

      const auto pt =
        point_add
        (
          scalar_mult(u1, { curve_gx(), curve_gy() } ),
          scalar_mult(u2, { pub.first,  pub.second } )
        );

      const auto result_verify_is_ok =
      (
        divmod(double_sint_type(sig.first), curve_n()).second == divmod(pt.my_x, curve_n()).second
      );

      return result_verify_is_ok;
    }
  };
} // namespace generic_ecc

#endif // ECC_ELLIPTIC_CURVE_2023_02_18_H
