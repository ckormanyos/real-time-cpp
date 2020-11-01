#ifndef DECWIDE_T_DETAIL_HELPER_2020_10_26_H_
  #define DECWIDE_T_DETAIL_HELPER_2020_10_26_H_

  #include <cstdint>

  namespace math { namespace wide_decimal { namespace detail {

  template<const std::int32_t MyDigits10,
           typename LimbType>
  struct decwide_t_helper
  {
    static constexpr std::uint32_t pow2_maker_of_upper_limit(std::uint32_t value, std::size_t p2 = 0U)
    {
      return (value >> p2) != 0U ? pow2_maker_of_upper_limit(value, p2 + 1) : std::uint32_t(1) << p2;
    }

    static constexpr std::uint32_t pow10_maker(std::uint32_t n)
    {
      return ((n == UINT32_C(0)) ? UINT32_C(1) : pow10_maker(n - UINT32_C(1)) * UINT32_C(10));
    }

    static constexpr std::int32_t digits10          = MyDigits10;
    static constexpr std::int32_t digits            = digits10;
    static constexpr std::int32_t max_digits10      = static_cast<std::int32_t>(digits10 + 1);
    static constexpr std::int32_t radix             = static_cast<std::int32_t>(10);

    // TBD: Can we obtain elem_digits10 from a meta-template?
    static constexpr std::int32_t elem_digits10     = ((std::numeric_limits<LimbType>::digits == 32) ? static_cast<std::int32_t>(8) : static_cast<std::int32_t>(4));
    static constexpr std::int32_t elem_number       = static_cast<std::int32_t>(((digits10 / elem_digits10) + (((digits10 % elem_digits10) != 0) ? 1 : 0)) + (24 / elem_digits10));
    static constexpr std::int32_t elem_mask         = static_cast<std::int32_t>(pow10_maker((std::uint32_t)  elem_digits10));
    static constexpr std::int32_t elem_mask_half    = static_cast<std::int32_t>(pow10_maker((std::uint32_t) (elem_digits10 / 2)));
  };

  } } } // namespace math::wide_decimal::detail

#endif // DECWIDE_T_DETAIL_HELPER_2020_10_26_H_
