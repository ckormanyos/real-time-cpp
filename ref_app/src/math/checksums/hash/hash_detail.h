#ifndef HASH_DETAIL_2020_05_18_H_
  #define HASH_DETAIL_2020_05_18_H_

  #include <algorithm>
  #include <cstddef>
  #include <cstdint>

  namespace math { namespace checksums { namespace hash { namespace detail {

  template<const std::uint_fast8_t digits_shift,
            typename arithmetic_type>
  arithmetic_type circular_right_shift(const arithmetic_type& the_value)
  {
    const std::uint_fast8_t left_shift_amount = static_cast<std::uint_fast8_t>(std::numeric_limits<arithmetic_type>::digits - digits_shift);

    const arithmetic_type part1 = arithmetic_type(arithmetic_type(the_value) >> (digits_shift));
    const arithmetic_type part2 = arithmetic_type(arithmetic_type(the_value) << left_shift_amount);

    return arithmetic_type(part1 | part2);
  }

  template<const std::uint_fast8_t digits_shift,
            typename arithmetic_type>
  arithmetic_type circular_left_shift(const arithmetic_type& the_value)
  {
    const std::uint_fast8_t right_shift_amount = static_cast<std::uint_fast8_t>(std::numeric_limits<arithmetic_type>::digits - digits_shift);

    const arithmetic_type part1 = arithmetic_type(arithmetic_type(the_value) << (digits_shift));
    const arithmetic_type part2 = arithmetic_type(arithmetic_type(the_value) >> right_shift_amount);

    return arithmetic_type(part1 | part2);
  }

  inline void convert_uint8_input_to_uint32_output(const std::uint8_t* in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin)
  {
    // Decode the input uint8_t source into the output uint32_t destination.
    // This subroutine assumes that the length of the input is a multiple of 4.

    std::size_t j = 0U;

    while(in_begin != in_end)
    {
      out_begin[j / 4U] = std::uint32_t(  std::uint32_t(std::uint32_t(*(in_begin + 0U)) <<  0U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 1U)) <<  8U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 2U)) << 16U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 3U)) << 24U));

      in_begin += 4U;

      j += 4U;
    }
  }

  inline void convert_uint8_input_to_uint32_output_reverse(const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin)
  {
    // Decode the input uint8_t source into the output uint32_t destination.
    // This subroutine assumes that the length of the input is a multiple of 4.

    std::size_t j = 0U;

    while(in_begin != in_end)
    {
      out_begin[j / 4U] = std::uint32_t(  std::uint32_t(std::uint32_t(*(in_begin + 3U)) <<  0U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 2U)) <<  8U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 1U)) << 16U)
                                        | std::uint32_t(std::uint32_t(*(in_begin + 0U)) << 24U));

      in_begin += 4U;

      j += 4U;
    }
  }

  inline void convert_uint32_input_to_uint8_output(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin)
  {
    // Encode the input uint32_t source into the output uint8_t destination.
    // This subroutine assumes that the length of the output is a multiple of 4.

    std::size_t j = 0U;

    while(in_begin != in_end)
    {
      out_begin[j + 0U] = std::uint8_t(*in_begin >>  0U);
      out_begin[j + 1U] = std::uint8_t(*in_begin >>  8U);
      out_begin[j + 2U] = std::uint8_t(*in_begin >> 16U);
      out_begin[j + 3U] = std::uint8_t(*in_begin >> 24U);

      ++in_begin;

      j += 4U;
    }
  }

  inline void convert_uint32_input_to_uint8_output_reverse(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin)
  {
    // Encode the input uint32_t source into the output uint8_t destination.
    // This subroutine assumes that the length of the output is a multiple of 4.

    std::size_t j = 0U;

    while(in_begin != in_end)
    {
      out_begin[j + 3U] = std::uint8_t(*in_begin >>  0U);
      out_begin[j + 2U] = std::uint8_t(*in_begin >>  8U);
      out_begin[j + 1U] = std::uint8_t(*in_begin >> 16U);
      out_begin[j + 0U] = std::uint8_t(*in_begin >> 24U);

      ++in_begin;

      j += 4U;
    }
  }

  } } } } // namespace math::checksums::hash::detail

#endif // HASH_DETAIL_2020_05_18_H_
