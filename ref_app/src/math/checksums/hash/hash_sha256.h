///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_SHA256_2023_02_26_H_
  #define HASH_SHA256_2023_02_26_H_

  // See also: https://en.wikipedia.org/wiki/SHA-2

  #include <algorithm>
  #include <array>
  #include <functional>

  #include <math/checksums/hash/hash_base.h>

  namespace math { namespace checksums { namespace hash {

  template<typename CountType>
  class hash_sha256 : public hash_base<CountType,
                                       static_cast<std::uint16_t>(UINT16_C(256)),
                                       static_cast<std::uint16_t>(UINT8_C(64)),
                                       static_cast<std::uint16_t>(UINT8_C(64))>
  {
  private:
    using base_class_type = hash_base<CountType,
                                      static_cast<std::uint16_t>(UINT16_C(256)),
                                      static_cast<std::uint16_t>(UINT8_C(64)),
                                      static_cast<std::uint16_t>(UINT8_C(64))>;

    static_assert(base_class_type::message_buffer_static_size() == static_cast<std::uint16_t>(UINT8_C(64)),
                  "Error: The message buffer size must exactly equal 64");

    using transform_function_type = std::uint32_t(*)(const std::uint32_t*);

  public:
    hash_sha256() = default;

    hash_sha256(const hash_sha256&) = default;
    hash_sha256(hash_sha256&&) noexcept = default;

    ~hash_sha256() override = default;

    auto operator=(const hash_sha256&) -> hash_sha256& = default;
    auto operator=(hash_sha256&&) noexcept -> hash_sha256& = default;

    auto initialize() -> void override
    {
      base_class_type::initialize();

      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(0))] = static_cast<std::uint32_t>(UINT32_C(0x6A09E667));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(1))] = static_cast<std::uint32_t>(UINT32_C(0xBB67AE85));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(2))] = static_cast<std::uint32_t>(UINT32_C(0x3C6EF372));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(3))] = static_cast<std::uint32_t>(UINT32_C(0xA54FF53A));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(4))] = static_cast<std::uint32_t>(UINT32_C(0x510E527F));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(5))] = static_cast<std::uint32_t>(UINT32_C(0x9B05688C));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(6))] = static_cast<std::uint32_t>(UINT32_C(0x1F83D9AB));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(7))] = static_cast<std::uint32_t>(UINT32_C(0x5BE0CD19));
    }

  private:
    auto perform_algorithm() -> void override;

    static constexpr auto transform_function1(std::uint32_t x) -> std::uint32_t; // BSIG0
    static constexpr auto transform_function2(std::uint32_t x) -> std::uint32_t; // BSIG1
    static constexpr auto transform_function3(std::uint32_t x) -> std::uint32_t; // SSIG0
    static constexpr auto transform_function4(std::uint32_t x) -> std::uint32_t; // SSIG1
  };

  template <typename my_count_type>
  auto hash_sha256<my_count_type>::perform_algorithm() -> void
  {
    // Apply the hash transformation algorithm to a full data block.

    using transform_constants_array_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(64))>;

    constexpr transform_constants_array_type transform_constants
    {
      UINT32_C(0x428A2F98), UINT32_C(0x71374491), UINT32_C(0xB5C0FBCF), UINT32_C(0xE9B5DBA5),
      UINT32_C(0x3956C25B), UINT32_C(0x59F111F1), UINT32_C(0x923F82A4), UINT32_C(0xAB1C5ED5),
      UINT32_C(0xD807AA98), UINT32_C(0x12835B01), UINT32_C(0x243185BE), UINT32_C(0x550C7DC3),
      UINT32_C(0x72BE5D74), UINT32_C(0x80DEB1FE), UINT32_C(0x9BDC06A7), UINT32_C(0xC19BF174),
      UINT32_C(0xE49B69C1), UINT32_C(0xEFBE4786), UINT32_C(0x0FC19DC6), UINT32_C(0x240CA1CC),
      UINT32_C(0x2DE92C6F), UINT32_C(0x4A7484AA), UINT32_C(0x5CB0A9DC), UINT32_C(0x76F988DA),
      UINT32_C(0x983E5152), UINT32_C(0xA831C66D), UINT32_C(0xB00327C8), UINT32_C(0xBF597FC7),
      UINT32_C(0xC6E00BF3), UINT32_C(0xD5A79147), UINT32_C(0x06CA6351), UINT32_C(0x14292967),
      UINT32_C(0x27B70A85), UINT32_C(0x2E1B2138), UINT32_C(0x4D2C6DFC), UINT32_C(0x53380D13),
      UINT32_C(0x650A7354), UINT32_C(0x766A0ABB), UINT32_C(0x81C2C92E), UINT32_C(0x92722C85),
      UINT32_C(0xA2BFE8A1), UINT32_C(0xA81A664B), UINT32_C(0xC24B8B70), UINT32_C(0xC76C51A3),
      UINT32_C(0xD192E819), UINT32_C(0xD6990624), UINT32_C(0xF40E3585), UINT32_C(0x106AA070),
      UINT32_C(0x19A4C116), UINT32_C(0x1E376C08), UINT32_C(0x2748774C), UINT32_C(0x34B0BCB5),
      UINT32_C(0x391C0CB3), UINT32_C(0x4ED8AA4A), UINT32_C(0x5B9CCA4F), UINT32_C(0x682E6FF3),
      UINT32_C(0x748F82EE), UINT32_C(0x78A5636F), UINT32_C(0x84C87814), UINT32_C(0x8CC70208),
      UINT32_C(0x90BEFFFA), UINT32_C(0xA4506CEB), UINT32_C(0xBEF9A3F7), UINT32_C(0xC67178F2)
    };

    using transform_block_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(64))>;

    transform_block_type transform_block { };

    detail::convert_uint8_input_to_uint32_output_reverse
    (
      base_class_type::message_buffer.data(),
      base_class_type::message_buffer.data() + static_cast<std::size_t>(base_class_type::message_buffer_static_size()),
      transform_block.data()
    );

    for(auto   loop_counter = static_cast<std::size_t>(UINT8_C(16));
               loop_counter < std::tuple_size<transform_constants_array_type>::value;
             ++loop_counter)
    {
      transform_block[loop_counter] =
        static_cast<std::uint32_t>
        (
            transform_function4(transform_block[static_cast<std::size_t>(loop_counter - static_cast<std::size_t>(UINT8_C( 2)))])
          +                     transform_block[static_cast<std::size_t>(loop_counter - static_cast<std::size_t>(UINT8_C( 7)))]
          + transform_function3(transform_block[static_cast<std::size_t>(loop_counter - static_cast<std::size_t>(UINT8_C(15)))])
          +                     transform_block[static_cast<std::size_t>(loop_counter - static_cast<std::size_t>(UINT8_C(16)))]
        );
    }

    auto hash_tmp = base_class_type::transform_context;

    for(auto   loop_counter = static_cast<std::size_t>(UINT8_C(0));
               loop_counter < std::tuple_size<transform_constants_array_type>::value;
             ++loop_counter)
    {
      const auto tmp1 =
        static_cast<std::uint32_t>
        (
            hash_tmp[static_cast<std::size_t>(UINT8_C(7))]
          + transform_function2(hash_tmp[static_cast<std::size_t>(UINT8_C(4))])
          + static_cast<std::uint32_t>
            (
              static_cast<std::uint32_t>
              (
                  static_cast<std::uint32_t>
                  (
                      hash_tmp[static_cast<std::size_t>(UINT8_C(4))]
                    & hash_tmp[static_cast<std::size_t>(UINT8_C(5))]
                  )
                ^ static_cast<std::uint32_t>
                  (
                      static_cast<std::uint32_t>(~hash_tmp[static_cast<std::size_t>(UINT8_C(4))])
                    & hash_tmp[static_cast<std::size_t>(UINT8_C(6))]
                  )
              )
            )
          + transform_constants[loop_counter]
          + transform_block    [loop_counter]
        );

      const auto tmp2 =
        static_cast<std::uint32_t>
        (
            transform_function1(hash_tmp[static_cast<std::size_t>(UINT8_C(0))])
          + static_cast<std::uint32_t>
            (
                static_cast<std::uint32_t>(hash_tmp[static_cast<std::size_t>(UINT8_C(0))] & hash_tmp[static_cast<std::size_t>(UINT8_C(1))])
              ^ static_cast<std::uint32_t>(hash_tmp[static_cast<std::size_t>(UINT8_C(0))] & hash_tmp[static_cast<std::size_t>(UINT8_C(2))])
              ^ static_cast<std::uint32_t>(hash_tmp[static_cast<std::size_t>(UINT8_C(1))] & hash_tmp[static_cast<std::size_t>(UINT8_C(2))])
            )
        );

      hash_tmp[static_cast<std::size_t>(UINT8_C(7))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(6))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(6))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(5))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(5))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(4))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(4))] = static_cast<std::uint32_t>
                                                       (
                                                         hash_tmp[static_cast<std::size_t>(UINT8_C(3))] + tmp1
                                                       );
      hash_tmp[static_cast<std::size_t>(UINT8_C(3))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(2))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(2))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(1))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(1))] =   hash_tmp[static_cast<std::size_t>(UINT8_C(0))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(0))] =   static_cast<std::uint32_t>(tmp1 + tmp2);
    }

    // Update the hash state with the transformation results.
    std::transform(base_class_type::transform_context.cbegin(),
                   base_class_type::transform_context.cend  (),
                   hash_tmp.cbegin                          (),
                   base_class_type::transform_context.begin (),
                   std::plus<std::uint32_t>                 ());
  }

  template <typename my_count_type>
  constexpr auto hash_sha256<my_count_type>::transform_function1(std::uint32_t x) -> std::uint32_t
  {
    // BSIG0
    return
      static_cast<std::uint32_t>
      (
          detail::circular_right_shift<static_cast<unsigned>(UINT8_C( 2))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(13))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(22))>(x)
      );
  }

  template <typename my_count_type>
  constexpr auto hash_sha256<my_count_type>::transform_function2(std::uint32_t x) -> std::uint32_t
  {
    // BSIG1
    return
      static_cast<std::uint32_t>
      (
          detail::circular_right_shift<static_cast<unsigned>(UINT8_C( 6))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(11))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(25))>(x)
      );
  }

  template <typename my_count_type>
  constexpr auto hash_sha256<my_count_type>::transform_function3(std::uint32_t x) -> std::uint32_t
  {
    // SSIG0
    return
      static_cast<std::uint32_t>
      (
          detail::circular_right_shift<static_cast<unsigned>(UINT8_C(7))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(18))>(x)
        ^ static_cast<std::uint32_t>(x >> static_cast<unsigned>(UINT8_C(3)))
      );
  }

  template <typename my_count_type>
  constexpr auto hash_sha256<my_count_type>::transform_function4(std::uint32_t x) -> std::uint32_t
  {
    // SSIG1
    return
      static_cast<std::uint32_t>
      (
          detail::circular_right_shift<static_cast<unsigned>(UINT8_C(17))>(x)
        ^ detail::circular_right_shift<static_cast<unsigned>(UINT8_C(19))>(x)
        ^ static_cast<std::uint32_t>(x >> static_cast<unsigned>(UINT8_C(10)))
      );
  }

  } } } // namespace math::checksums::hash

#endif // HASH_SHA256_2023_02_26_H_
