///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_SHA1_2013_09_03_H_
  #define HASH_SHA1_2013_09_03_H_

  // See also: https://en.wikipedia.org/wiki/SHA-1

  #include <algorithm>
  #include <array>
  #include <functional>

  #include <math/checksums/hash/hash_base.h>

  namespace math { namespace checksums { namespace hash {

  class hash_sha1 : public hash_base<static_cast<std::uint16_t>(UINT8_C(160)),
                                     static_cast<std::uint16_t>(UINT8_C(64)),
                                     static_cast<std::uint16_t>(UINT8_C(64))>
  {
  private:
    using base_class_type = hash_base<static_cast<std::uint16_t>(UINT8_C(160)),
                                      static_cast<std::uint16_t>(UINT8_C(64)),
                                      static_cast<std::uint16_t>(UINT8_C(64))>;

    static_assert(base_class_type::message_buffer_static_size() == static_cast<std::uint16_t>(UINT8_C(64)),
                  "Error: The message  buffer size must exactly equal 64");

  public:
    hash_sha1() = default;

    hash_sha1(const hash_sha1&) = default;
    hash_sha1(hash_sha1&&) noexcept = default;

    ~hash_sha1() override = default;

    auto operator=(const hash_sha1&) -> hash_sha1& = default;
    auto operator=(hash_sha1&&) noexcept -> hash_sha1& = default;

    auto initialize() -> void override
    {
      base_class_type::initialize();

      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(0))] = static_cast<std::uint32_t>(UINT32_C(0x67452301));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(1))] = static_cast<std::uint32_t>(UINT32_C(0xEFCDAB89));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(2))] = static_cast<std::uint32_t>(UINT32_C(0x98BADCFE));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(3))] = static_cast<std::uint32_t>(UINT32_C(0x10325476));
      base_class_type::transform_context[static_cast<std::size_t>(UINT8_C(4))] = static_cast<std::uint32_t>(UINT32_C(0xC3D2E1F0));
    }

  private:
    auto perform_algorithm() -> void override;
  };

  auto hash_sha1::perform_algorithm() -> void
  {
    // Apply the hash transformation algorithm to a full data block.

    using transform_constants_array_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(4))>;

    const transform_constants_array_type transform_constants
    {
      static_cast<std::uint32_t>(UINT32_C(0x5A827999)),
      static_cast<std::uint32_t>(UINT32_C(0x6ED9EBA1)),
      static_cast<std::uint32_t>(UINT32_C(0x8F1BBCDC)),
      static_cast<std::uint32_t>(UINT32_C(0xCA62C1D6))
    };

    using transform_block_type = std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(16))>;

    transform_block_type transform_block { };

    detail::convert_uint8_input_to_uint32_output_reverse
    (
      base_class_type::message_buffer.data(),
      base_class_type::message_buffer.data() + static_cast<std::size_t>(base_class_type::message_buffer_static_size()),
      transform_block.data()
    );

    using transform_function_type = std::uint32_t(*)(const std::uint32_t*);

    const std::array<transform_function_type, static_cast<std::size_t>(UINT8_C(4))> transform_functions
    {
      [](const std::uint32_t* p) -> std::uint32_t { return (static_cast<std::uint32_t>(                           p[1U] & p[2U]) | static_cast<std::uint32_t>(static_cast<std::uint32_t>(~p[1U]) & p[3U])); },
      [](const std::uint32_t* p) -> std::uint32_t { return  static_cast<std::uint32_t>(static_cast<std::uint32_t>(p[1U] ^ p[2U]) ^ p[3U]); },
      [](const std::uint32_t* p) -> std::uint32_t { return  static_cast<std::uint32_t>(static_cast<std::uint32_t>(p[1U] & p[2U]) | static_cast<std::uint32_t>(p[1U] & p[3U]) | static_cast<std::uint32_t>(p[2U] & p[3U])); },
      [](const std::uint32_t* p) -> std::uint32_t { return (static_cast<std::uint32_t>(                           p[1U] ^ p[2U]) ^ p[3U]); }
    };

    auto hash_tmp = base_class_type::transform_context;

    auto loop_index = static_cast<std::uint8_t>(UINT8_C(0));

    for(auto   loop_counter = static_cast<std::uint8_t>(UINT8_C(0));
               loop_counter < static_cast<std::uint8_t>(UINT8_C(80));
             ++loop_counter)
    {
      if(loop_counter >= static_cast<std::uint8_t>(UINT8_C(16)))
      {
        const auto the_dword =
          static_cast<std::uint32_t>
          (
              transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter + static_cast<std::uint8_t>(UINT8_C(13))) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter + static_cast<std::uint8_t>(UINT8_C( 8))) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter + static_cast<std::uint8_t>(UINT8_C( 2))) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(                          loop_counter                                           & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
          );

        const auto transform_block_index = static_cast<std::size_t>(loop_counter & std::uint8_t(UINT8_C(0x0F)));

        transform_block[transform_block_index] = detail::circular_left_shift<static_cast<unsigned>(UINT8_C(1))>(the_dword);

        if     (loop_counter == static_cast<std::uint8_t>(UINT8_C(20))) { loop_index = static_cast<std::uint8_t>(UINT8_C(1)); }
        else if(loop_counter == static_cast<std::uint8_t>(UINT8_C(40))) { loop_index = static_cast<std::uint8_t>(UINT8_C(2)); }
        else if(loop_counter == static_cast<std::uint8_t>(UINT8_C(60))) { loop_index = static_cast<std::uint8_t>(UINT8_C(3)); }
      }

      const auto tmp1 =
        static_cast<std::uint32_t>
        (
            detail::circular_left_shift<static_cast<unsigned>(UINT8_C(5))>(hash_tmp[static_cast<std::size_t>(UINT8_C(0))])
          + (transform_functions[loop_index])(hash_tmp.data())
          + hash_tmp[static_cast<std::size_t>(UINT8_C(4))]
          + transform_block[static_cast<std::size_t>(loop_counter & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
          + transform_constants[loop_index]
        );

      hash_tmp[static_cast<std::size_t>(UINT8_C(4))] = hash_tmp[static_cast<std::size_t>(UINT8_C(3))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(3))] = hash_tmp[static_cast<std::size_t>(UINT8_C(2))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(2))] = detail::circular_left_shift<static_cast<unsigned>(UINT8_C(30))>(hash_tmp[static_cast<std::size_t>(UINT8_C(1))]);
      hash_tmp[static_cast<std::size_t>(UINT8_C(1))] = hash_tmp[static_cast<std::size_t>(UINT8_C(0))];
      hash_tmp[static_cast<std::size_t>(UINT8_C(0))] = tmp1;
    }

    // Update the hash state with the transformation results.
    std::transform(base_class_type::transform_context.cbegin(),
                   base_class_type::transform_context.cend  (),
                   hash_tmp.cbegin                          (),
                   base_class_type::transform_context.begin (),
                   std::plus<std::uint32_t>                 ());
  }

  } } } // namespace math::checksums::hash

#endif // HASH_SHA1_2013_09_03_H_
