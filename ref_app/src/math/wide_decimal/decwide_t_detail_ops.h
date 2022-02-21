///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 1999 - 2022.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// This file implements low-level decwide_t operations such as
// the loops for comparison, addition, subtraction, multiplication
// (including Karatsuba and FFT loops), and division (but only
// division by 1 limb).

#ifndef DECWIDE_T_DETAIL_OPS_2021_04_12_H // NOLINT(llvm-header-guard)
  #define DECWIDE_T_DETAIL_OPS_2021_04_12_H

  #include <cstdint>
  #include <iterator>
  #include <type_traits>

  #include <math/wide_decimal/decwide_t_detail.h>
  #include <math/wide_decimal/decwide_t_detail_fft.h>

  WIDE_DECIMAL_NAMESPACE_BEGIN

  #if(__cplusplus >= 201703L)
  namespace math::wide_decimal::detail {
  #else
  namespace math { namespace wide_decimal { namespace detail { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename InputIteratorLeftType,
           typename InputIteratorRightType>
  auto compare_ranges(      InputIteratorLeftType  a,
                            InputIteratorRightType b,
                      const std::uint_fast32_t     count) -> std::int_fast8_t
  {
    std::int_fast8_t n_return = 0;

    InputIteratorRightType it_b    (b);
    InputIteratorLeftType  it_a    (a);
    InputIteratorRightType it_a_end(a + count);

    while(it_a != it_a_end)
    {
      using value_left_type =
        typename std::iterator_traits<InputIteratorLeftType>::value_type;

      if(*it_a > static_cast<value_left_type>(*it_b)) { n_return =  1; break; }
      if(*it_a < static_cast<value_left_type>(*it_b)) { n_return = -1; break; }

      ++it_a;
      ++it_b;
    }

    return n_return;
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType>
  auto eval_add_n(      OutputLimbIteratorType r,
                        InputLimbIteratorType  u,
                        InputLimbIteratorType  v,
                  const std::int32_t           count) -> typename std::iterator_traits<OutputLimbIteratorType>::value_type
  {
    using local_limb_type = typename std::iterator_traits<OutputLimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    // Addition algorithm
    auto carry = static_cast<std::uint_fast8_t>(0U);

    for(auto j = static_cast<std::int32_t>(count - static_cast<std::int32_t>(1)); j >= static_cast<std::int32_t>(0); --j)
    {
      const auto t =
        static_cast<local_limb_type>
        (
          static_cast<local_limb_type>(u[j] + v[j]) + carry
        );

      carry = ((t >= static_cast<local_limb_type>(local_elem_mask)) ? static_cast<std::uint_fast8_t>(1U)
                                                                    : static_cast<std::uint_fast8_t>(0U));

      r[j]  = static_cast<local_limb_type>(t - ((carry != 0U) ? static_cast<local_limb_type>(local_elem_mask)
                                                              : static_cast<local_limb_type>(0U)));
    }

    return static_cast<local_limb_type>(carry);
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType>
  auto eval_subtract_n(OutputLimbIteratorType r,
                       InputLimbIteratorType u, // NOLINT(bugprone-easily-swappable-parameters)
                       InputLimbIteratorType v,
                       const std::int32_t count) -> bool
  {
    using local_limb_type        = typename std::iterator_traits<OutputLimbIteratorType>::value_type;
    using local_signed_limb_type = typename std::make_signed<local_limb_type>::type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    // Subtraction algorithm
    auto borrow = static_cast<std::uint_fast8_t>(0U);

    for(auto j = static_cast<std::uint32_t>(count - static_cast<std::int32_t>(1)); static_cast<std::int32_t>(j) >= static_cast<std::int32_t>(0); --j)
    {
      const auto vjb =
        static_cast<local_limb_type>
        (
          v[j] + static_cast<local_limb_type>(borrow)
        );

      auto t =
        static_cast<local_signed_limb_type>
        (
          static_cast<local_limb_type>
          (
              u[j]
            + static_cast<local_limb_type>
              (
                static_cast<local_limb_type>(~vjb) + 1U
              )
          )
        );

      // Underflow? Borrow?
      if(t < 0)
      {
        // Yes, underflow and borrow
        t      = static_cast<local_signed_limb_type>(t + static_cast<local_signed_limb_type>(local_elem_mask));
        borrow = static_cast<std::uint_fast8_t>(1U);
      }
      else
      {
        borrow = static_cast<std::uint_fast8_t>(0U);
      }

      r[j] = static_cast<local_limb_type>(t);
    }

    return (borrow != static_cast<std::uint_fast8_t>(0U));
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType>
  void eval_multiply_n_by_n_to_2n
  (
    OutputLimbIteratorType r,
    InputLimbIteratorType a,
    InputLimbIteratorType b,
    const std::int_fast32_t count,
    const typename std::enable_if<(std::is_same<typename std::iterator_traits<OutputLimbIteratorType>::value_type, std::uint8_t>::value)>::type* p_nullparam = nullptr
  )
  {
    static_cast<void>(p_nullparam);

    using local_limb_type = typename std::iterator_traits<OutputLimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    using local_double_limb_type =
      typename std::conditional<(std::is_same<local_limb_type, std::uint32_t>::value),
                                  std::uint64_t,
                                  typename std::conditional<(std::is_same<local_limb_type, std::uint16_t>::value),
                                                            std::uint32_t,
                                                            std::uint16_t>::type>::type;

    std::fill(r, r + (count * 2), static_cast<local_limb_type>(0));

    for(std::int_fast32_t i = count - 1; i >= 0; --i)
    {
      std::int_fast32_t j = count - 1;

      local_double_limb_type carry = 0U;

      for( ; j >= 0; --j)
      {
        carry = static_cast<local_double_limb_type>(carry + static_cast<local_double_limb_type>(static_cast<local_double_limb_type>(a[i]) * b[j]));
        carry = static_cast<local_double_limb_type>(carry + r[1 + (i + j)]);

        r[1 + (i + j)] = static_cast<local_limb_type>       (carry % local_elem_mask);
        carry          = static_cast<local_double_limb_type>(carry / local_elem_mask);
      }

      r[1 + i + j] = static_cast<local_limb_type>(carry);
    }
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType>
  void eval_multiply_n_by_n_to_2n
  (
    OutputLimbIteratorType r,
    InputLimbIteratorType a,
    InputLimbIteratorType b,
    const std::int_fast32_t count,
    const typename std::enable_if<(   (std::is_same<typename std::iterator_traits<OutputLimbIteratorType>::value_type, std::uint16_t>::value)
                                   || (std::is_same<typename std::iterator_traits<OutputLimbIteratorType>::value_type, std::uint32_t>::value))>::type* p_nullparam = nullptr)
  {
    static_cast<void>(p_nullparam);

    using local_limb_type = typename std::iterator_traits<OutputLimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    using local_double_limb_type =
      typename std::conditional<(std::is_same<local_limb_type, std::uint32_t>::value),
                                 std::uint64_t,
                                 typename std::conditional<(std::is_same<local_limb_type, std::uint16_t>::value),
                                                            std::uint32_t,
                                                            std::uint16_t>::type>::type;

    using local_reverse_iterator_type = std::reverse_iterator<local_limb_type*>;

    local_reverse_iterator_type ir(r + (count * 2));

    auto carry = static_cast<local_double_limb_type>(0U);

    for(auto j = static_cast<std::int32_t>(count - 1); j >= static_cast<std::int32_t>(1); --j)
    {
      auto sum = carry;

      for(auto i = static_cast<std::int32_t>(count - 1); i >= j; --i)
      {
        sum += static_cast<local_double_limb_type>
               (
                 static_cast<local_double_limb_type>(a[i]) * b[  static_cast<std::int32_t>(count - 1)
                                                               - static_cast<std::int32_t>(i - j)]
               );
      }

      carry = static_cast<local_double_limb_type>(sum / local_elem_mask);
      *ir++ = static_cast<local_limb_type>       (sum % local_elem_mask);
    }

    for(auto j = static_cast<std::int32_t>(count - 1); j >= static_cast<std::int32_t>(0); --j)
    {
      local_double_limb_type sum = carry;

      for(auto i = j; i >= static_cast<std::int32_t>(0); --i)
      {
        sum += static_cast<local_double_limb_type>(a[j - i] * static_cast<local_double_limb_type>(b[i]));
      }

      carry = static_cast<local_double_limb_type>(sum / local_elem_mask);
      *ir++ = static_cast<local_limb_type>       (sum % local_elem_mask);
    }

    *ir = static_cast<local_limb_type>(carry);
  }

  template<typename LimbIteratorType>
  auto mul_loop_n(      LimbIteratorType                                            u,
                        typename std::iterator_traits<LimbIteratorType>::value_type n,
                  const std::int32_t                                                p) -> typename std::iterator_traits<LimbIteratorType>::value_type
  {
    using local_limb_type = typename std::iterator_traits<LimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    using local_double_limb_type =
      typename std::conditional<(std::is_same<local_limb_type, std::uint32_t>::value),
                                 std::uint64_t,
                                 typename std::conditional<(std::is_same<local_limb_type, std::uint16_t>::value),
                                                            std::uint32_t,
                                                            std::uint16_t>::type>::type;

    local_limb_type carry = 0U;

    // Multiplication loop.
    for(auto j = static_cast<std::int32_t>(p - 1); j >= static_cast<std::int32_t>(0); --j)
    {
      const auto t =
        static_cast<local_double_limb_type>
        (
            carry
          + static_cast<local_double_limb_type>(static_cast<local_double_limb_type>(u[j]) * n)
        );

      carry = static_cast<local_limb_type>(t / local_elem_mask);
      u[j]  = static_cast<local_limb_type>(t % local_elem_mask);
    }

    return static_cast<local_limb_type>(carry);
  }

  template<typename LimbIteratorType>
  auto div_loop_n(      LimbIteratorType                                            u,
                        typename std::iterator_traits<LimbIteratorType>::value_type n,
                  const std::int32_t                                                p) -> typename std::iterator_traits<LimbIteratorType>::value_type
  {
    using local_limb_type = typename std::iterator_traits<LimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    using local_double_limb_type =
      typename std::conditional<(std::is_same<local_limb_type, std::uint32_t>::value),
                                 std::uint64_t,
                                 typename std::conditional<(std::is_same<local_limb_type, std::uint16_t>::value),
                                                            std::uint32_t,
                                                            std::uint16_t>::type>::type;

    local_limb_type prev = 0U;

    for(auto j = static_cast<std::int32_t>(0); j < p; ++j)
    {
      const auto t =
        static_cast<local_double_limb_type>
        (
            u[j]
          + static_cast<local_double_limb_type>(static_cast<local_double_limb_type>(prev) * local_elem_mask)
        );

      u[j] = static_cast<local_limb_type>(t / n);
      prev = static_cast<local_limb_type>(t % n);
    }

    return prev;
  }

  template<typename LimbIteratorType>
  auto eval_multiply_kara_propagate_carry(      LimbIteratorType                                            t,
                                          const std::uint_fast32_t                                          n,
                                          const typename std::iterator_traits<LimbIteratorType>::value_type carry) -> void
  {
    using local_limb_type = typename std::iterator_traits<LimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    std::uint_fast8_t carry_out = ((carry != 0U) ? static_cast<std::uint_fast8_t>(1U)
                                                 : static_cast<std::uint_fast8_t>(0U));

    using local_reverse_iterator_type = std::reverse_iterator<LimbIteratorType>;

    local_reverse_iterator_type ri_t  (t + n);
    local_reverse_iterator_type rend_t(t);

    while((carry_out != 0U) && (ri_t != rend_t))
    {
      const auto tt = static_cast<local_limb_type>(*ri_t + static_cast<local_limb_type>(carry_out));

      carry_out = ((tt >= local_elem_mask) ? static_cast<std::uint_fast8_t>(1U)
                                           : static_cast<std::uint_fast8_t>(0U));

      *ri_t++  = static_cast<local_limb_type>(tt - ((carry_out != 0U) ? local_elem_mask
                                                                      : static_cast<local_limb_type>(0U)));
    }
  }

  template<typename LimbIteratorType>
  auto eval_multiply_kara_propagate_borrow(      LimbIteratorType   t,
                                           const std::uint_fast32_t n,
                                           const bool               has_borrow) -> void
  {
    using local_limb_type = typename std::iterator_traits<LimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask = decwide_t_helper_base<local_limb_type>::elem_mask;

    std::int_fast8_t borrow = (has_borrow ? static_cast<std::int_fast8_t>(1)
                                          : static_cast<std::int_fast8_t>(0));

    using local_reverse_iterator_type = std::reverse_iterator<LimbIteratorType>;

    local_reverse_iterator_type ri_t  (t + n);
    local_reverse_iterator_type rend_t(t);

    while((borrow != 0) && (ri_t != rend_t))
    {
      using local_signed_limb_type = typename std::make_signed<local_limb_type>::type;

      auto tt = static_cast<local_signed_limb_type>(static_cast<local_signed_limb_type>(*ri_t) - borrow);

      // Underflow? Borrow?
      if(tt < 0)
      {
        // Yes, underflow and borrow
        tt     = static_cast<local_signed_limb_type>(tt + static_cast<local_signed_limb_type>(local_elem_mask));
        borrow = static_cast<int_fast8_t>(1);
      }
      else
      {
        borrow = static_cast<int_fast8_t>(0);
      }

      *ri_t++ = static_cast<local_limb_type>(tt);
    }
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType,
           typename TempLimbIteratorType>
  auto eval_multiply_kara_n_by_n_to_2n(OutputLimbIteratorType r, // NOLINT(misc-no-recursion)
                                       InputLimbIteratorType a,
                                       InputLimbIteratorType b,
                                       const std::uint_fast32_t n,
                                       TempLimbIteratorType t) -> void
  {
    if(n <= 32U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    {
      static_cast<void>(t);

      detail::eval_multiply_n_by_n_to_2n(r, a, b, static_cast<std::int32_t>(n));
    }
    else
    {
      // Based on "Algorithm 1.3 KaratsubaMultiply", Sect. 1.3.2, page 5
      // of R.P. Brent and P. Zimmermann, "Modern Computer Arithmetic",
      // Cambridge University Press (2011).

      // The Karatsuba multipliation computes the product of a*b as:
      // [b^N + b^(N/2)] a1*b1 + [b^(N/2)](a1 - a0)(b0 - b1) + [b^(N/2) + 1] a0*b0

      // Here we visualize a and b in two components 1,0 corresponding
      // to the high and low order parts, respectively.

      // Step 1
      // Calculate a1*b1 and store it in the upper-order part of r.
      // Calculate a0*b0 and store it in the lower-order part of r.
      // copy r to t0.

      // Step 2
      // Add a1*b1 (which is t2) to the middle two-quarters of r (which is r1)
      // Add a0*b0 (which is t0) to the middle two-quarters of r (which is r1)

      // Step 3
      // Calculate |a1-a0| in t0 and note the sign (i.e., the borrow flag)

      // Step 4
      // Calculate |b0-b1| in t1 and note the sign (i.e., the borrow flag)

      // Step 5
      // Call kara mul to calculate |a1-a0|*|b0-b1| in (t2),
      // while using temporary storage in t4 along the way.

      // Step 6
      // Check the borrow signs. If a1-a0 and b0-b1 have the same signs,
      // then add |a1-a0|*|b0-b1| to r1, otherwise subtract it from r1.

      using local_limb_type = typename std::iterator_traits<InputLimbIteratorType>::value_type;

      const std::uint_fast32_t  nh = n / 2U;

      InputLimbIteratorType a0 = a + nh;
      InputLimbIteratorType a1 = a + 0U;

      InputLimbIteratorType b0 = b + nh;
      InputLimbIteratorType b1 = b + 0U;

      OutputLimbIteratorType r0 = r + 0U;
      OutputLimbIteratorType r1 = r + nh;
      OutputLimbIteratorType r2 = r + n;

      TempLimbIteratorType t0 = t + 0U;
      TempLimbIteratorType t1 = t + nh;
      TempLimbIteratorType t2 = t + n;
      TempLimbIteratorType t4 = t + (n + n);

      // Step 1
      eval_multiply_kara_n_by_n_to_2n(r0, a1, b1, nh, t);
      eval_multiply_kara_n_by_n_to_2n(r2, a0, b0, nh, t);
      std::copy(r0, r0 + (2U * n), t0);

      // Step 2
      local_limb_type carry;
      carry = detail::eval_add_n(r1, r1, t0, static_cast<std::int32_t>(n));
      eval_multiply_kara_propagate_carry(r0, nh, carry);
      carry = detail::eval_add_n(r1, r1, t2, static_cast<std::int32_t>(n));
      eval_multiply_kara_propagate_carry(r0, nh, carry);

      // Step 3
      const std::int_fast8_t cmp_result_a1a0 = detail::compare_ranges(a1, a0, nh);

      if(cmp_result_a1a0 == 1)
      {
        static_cast<void>(detail::eval_subtract_n(t0, a1, a0, static_cast<std::int32_t>(nh)));
      }
      else if(cmp_result_a1a0 == -1)
      {
        static_cast<void>(detail::eval_subtract_n(t0, a0, a1, static_cast<std::int32_t>(nh)));
      }

      // Step 4
      const std::int_fast8_t cmp_result_b0b1 = detail::compare_ranges(b0, b1, nh);

      if(cmp_result_b0b1 == 1)
      {
        static_cast<void>(detail::eval_subtract_n(t1, b0, b1, static_cast<std::int32_t>(nh)));
      }
      else if(cmp_result_b0b1 == -1)
      {
        static_cast<void>(detail::eval_subtract_n(t1, b1, b0, static_cast<std::int32_t>(nh)));
      }

      // Step 5
      eval_multiply_kara_n_by_n_to_2n(t2, t0, t1, nh, t4);

      // Step 6
      if((cmp_result_a1a0 * cmp_result_b0b1) == 1)
      {
        carry = detail::eval_add_n(r1, r1, t2, static_cast<std::int32_t>(n));

        eval_multiply_kara_propagate_carry(r0, nh, carry);
      }
      else if((cmp_result_a1a0 * cmp_result_b0b1) == -1)
      {
        const bool has_borrow = detail::eval_subtract_n(r1, r1, t2, static_cast<std::int32_t>(n));

        eval_multiply_kara_propagate_borrow(r0, nh, has_borrow);
      }
    }
  }

  template<typename InputLimbIteratorType,
           typename OutputLimbIteratorType,
           typename FftFloatIteratorType>
  auto mul_loop_fft(OutputLimbIteratorType r,
                    InputLimbIteratorType u, // NOLINT(bugprone-easily-swappable-parameters)
                    InputLimbIteratorType v,
                    FftFloatIteratorType af,
                    FftFloatIteratorType bf,
                    const std::int32_t prec_elems_for_multiply,
                    const std::uint32_t n_fft) -> void
  {
    using local_limb_type = typename std::iterator_traits<OutputLimbIteratorType>::value_type;

    constexpr local_limb_type local_elem_mask_half = decwide_t_helper_base<local_limb_type>::elem_mask_half;

    using local_fft_float_type = typename std::iterator_traits<FftFloatIteratorType>::value_type;

    for(auto i = static_cast<std::uint32_t>(0U); i < static_cast<std::uint32_t>(prec_elems_for_multiply); ++i)
    {
      af[(i * 2U)]      = static_cast<local_fft_float_type>(u[i] / local_elem_mask_half); // NOLINT(bugprone-integer-division)
      af[(i * 2U) + 1U] = static_cast<local_fft_float_type>(u[i] % local_elem_mask_half);

      bf[(i * 2U)]      = static_cast<local_fft_float_type>(v[i] / local_elem_mask_half); // NOLINT(bugprone-integer-division)
      bf[(i * 2U) + 1U] = static_cast<local_fft_float_type>(v[i] % local_elem_mask_half);
    }

    std::fill(af + (2 * prec_elems_for_multiply), af + n_fft, static_cast<local_fft_float_type>(0));
    std::fill(bf + (2 * prec_elems_for_multiply), bf + n_fft, static_cast<local_fft_float_type>(0));

    // Perform forward FFTs on the data arrays a and b.
    detail::fft::rfft_lanczos_rfft<local_fft_float_type, true>(n_fft, af);
    detail::fft::rfft_lanczos_rfft<local_fft_float_type, true>(n_fft, bf);

    // Perform the convolution of a and b in the transform space.
    // This does, in fact, execute the actual multiplication of (a * b).
    af[0U] *= bf[0U];
    af[1U] *= bf[1U];

    for(auto j = static_cast<std::uint32_t>(2U); j < n_fft; j += 2U)
    {
      const local_fft_float_type tmp_aj = af[j];

      af[j + 0U] = (tmp_aj * bf[j + 0U]) - (af[j + 1U] * bf[j + 1U]);
      af[j + 1U] = (tmp_aj * bf[j + 1U]) + (af[j + 1U] * bf[j + 0U]);
    }

    // Perform the reverse FFT on the result of the convolution.
    detail::fft::rfft_lanczos_rfft<local_fft_float_type, false>(n_fft, af);

    // Release the carries and re-combine the low and high parts.
    // This sets the integral data elements in the big number
    // to the result of multiplication.
    using fft_carry_type = std::uint_fast64_t;

    auto carry = static_cast<fft_carry_type>(0U);

    for(auto j = static_cast<std::uint32_t>((prec_elems_for_multiply * 2L) - 2L);
                 static_cast<std::int32_t>(j) >= static_cast<std::int32_t>(0);
             j -= 2U)
    {
            auto xaj   = static_cast<local_fft_float_type>(af[j] / (n_fft / 2U)); // NOLINT(bugprone-integer-division)
      const auto xlo   = static_cast<fft_carry_type> (xaj + detail::fft::template_half<local_fft_float_type>()) + carry;
                 carry = static_cast<fft_carry_type> (xlo / local_elem_mask_half);
      const auto nlo   = static_cast<local_limb_type>(xlo - static_cast<fft_carry_type>(carry * local_elem_mask_half));

                 xaj   = ((j != 0) ? static_cast<local_fft_float_type>(af[j - 1U] / (n_fft / 2U)) : static_cast<local_fft_float_type>(0)); // NOLINT(bugprone-integer-division)
      const auto xhi   = static_cast<fft_carry_type> (xaj + detail::fft::template_half<local_fft_float_type>()) + carry;
                 carry = static_cast<fft_carry_type> (xhi / local_elem_mask_half);
      const auto nhi   = static_cast<local_limb_type>(xhi - static_cast<fft_carry_type>(carry * local_elem_mask_half));

      r[(j / 2U)] = static_cast<local_limb_type>(static_cast<local_limb_type>(nhi * local_elem_mask_half) + nlo);
    }
  }

  #if(__cplusplus >= 201703L)
  } // namespace math::wide_decimal::detail
  #else
  } // namespace detail
  } // namespace wide_decimal
  } // namespace math
  #endif

  WIDE_DECIMAL_NAMESPACE_END

#endif // DECWIDE_T_DETAIL_OPS_2021_04_12_H
