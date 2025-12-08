//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_DETAIL_2020_05_18_H_
  #define HASH_DETAIL_2020_05_18_H_

  #include <cstddef>
  #include <cstdint>

  namespace math { namespace checksums { namespace hash { namespace detail {

  template<const std::uint_fast8_t digits_shift,
           typename arithmetic_type>
  constexpr auto circular_right_shift(arithmetic_type the_value) -> arithmetic_type
  {
    return
      static_cast<arithmetic_type>
      (
          static_cast<arithmetic_type>(static_cast<arithmetic_type>(the_value) >> static_cast<unsigned>(digits_shift))
        | static_cast<arithmetic_type>(static_cast<arithmetic_type>(the_value) << static_cast<unsigned>(std::numeric_limits<arithmetic_type>::digits - digits_shift))
      );
  }

  template<const std::uint_fast8_t digits_shift,
           typename arithmetic_type>
  constexpr auto circular_left_shift(arithmetic_type the_value) -> arithmetic_type
  {
    return
      static_cast<arithmetic_type>
      (
          static_cast<arithmetic_type>(static_cast<arithmetic_type>(the_value) << static_cast<unsigned>(digits_shift))
        | static_cast<arithmetic_type>(static_cast<arithmetic_type>(the_value) >> static_cast<unsigned>(std::numeric_limits<arithmetic_type>::digits - digits_shift))
      );
  }

  inline auto convert_uint8_input_to_uint32_output(const std::uint8_t* in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin) -> void
  {
    // Decode the input uint8_t source into the output uint32_t destination.
    // This subroutine assumes that the length of the input is a multiple of 4.

    auto j = static_cast<std::size_t>(UINT8_C(0));

    while(in_begin != in_end)
    {
      out_begin[static_cast<std::size_t>(j / static_cast<std::size_t>(UINT8_C(4)))] =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 0U)) << static_cast<unsigned>(UINT8_C( 0)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 1U)) << static_cast<unsigned>(UINT8_C( 8)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 2U)) << static_cast<unsigned>(UINT8_C(16)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 3U)) << static_cast<unsigned>(UINT8_C(24)))
        );

      in_begin += static_cast<std::size_t>(UINT8_C(4));

      j = static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(4)));
    }
  }

  inline auto convert_uint8_input_to_uint32_output_reverse(const std::uint8_t*  in_begin, const std::uint8_t*  in_end, std::uint32_t* out_begin) -> void
  {
    // Decode the input uint8_t source into the output uint32_t destination.
    // This subroutine assumes that the length of the input is a multiple of 4.

    auto j = static_cast<std::size_t>(UINT8_C(0));

    while(in_begin != in_end)
    {
      out_begin[static_cast<std::size_t>(j / static_cast<std::size_t>(UINT8_C(4)))] =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 3U)) << static_cast<unsigned>(UINT8_C( 0)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 2U)) << static_cast<unsigned>(UINT8_C( 8)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 1U)) << static_cast<unsigned>(UINT8_C(16)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(*(in_begin + 0U)) << static_cast<unsigned>(UINT8_C(24)))
        );

      in_begin += static_cast<std::size_t>(UINT8_C(4));

      j = static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(4)));
    }
  }

  inline auto convert_uint32_input_to_uint8_output(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin) -> void
  {
    // Encode the input uint32_t source into the output uint8_t destination.
    // This subroutine assumes that the length of the output is a multiple of 4.

    auto j = static_cast<std::size_t>(UINT8_C(0));

    while(in_begin != in_end)
    {
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(0)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C( 0)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(1)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C( 8)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(2)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C(16)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(3)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C(24)));

      ++in_begin;

      j = static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(4)));
    }
  }

  inline auto convert_uint32_input_to_uint8_output_reverse(const std::uint32_t* in_begin, const std::uint32_t* in_end, std::uint8_t*  out_begin) -> void
  {
    // Encode the input uint32_t source into the output uint8_t destination.
    // This subroutine assumes that the length of the output is a multiple of 4.

    auto j = static_cast<std::size_t>(UINT8_C(0));

    while(in_begin != in_end)
    {
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(3)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C( 0)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(2)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C( 8)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(1)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C(16)));
      out_begin[static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(0)))] = static_cast<std::uint8_t>(*in_begin >> static_cast<unsigned>(UINT8_C(24)));

      ++in_begin;

      j = static_cast<std::size_t>(j + static_cast<std::size_t>(UINT8_C(4)));
    }
  }

  } } } } // namespace math::checksums::hash::detail

#endif // HASH_DETAIL_2020_05_18_H_
