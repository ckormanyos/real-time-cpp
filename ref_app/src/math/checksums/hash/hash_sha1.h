///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_SHA1_2013_09_03_H_
  #define HASH_SHA1_2013_09_03_H_

  // See also: https://en.wikipedia.org/wiki/SHA-1

  // In this development domain, we use hash SHA1
  // for unique checksum verification of byte streams,
  // not for secure digital hashes.

  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <functional>
  #include <limits>

  #include <math/checksums/hash/hash_base.h>

  namespace math { namespace checksums { namespace hash {

  template<typename CountType>
  class hash_sha1 final : public hash_base<CountType, static_cast<std::size_t>(UINT8_C(64))>
  {
  private:
    using base_class_type = hash_base<CountType, static_cast<std::size_t>(UINT8_C(64))>;

    static_assert(base_class_type::message_buffer_static_size == static_cast<std::uint16_t>(UINT8_C(64)),
                  "Error: The message  buffer size must exactly equal 64");

    using transform_function_type = std::uint32_t(*)(const std::uint32_t*);

    static constexpr std::array<transform_function_type, static_cast<std::size_t>(UINT8_C(4))> transform_functions()
    {
      return
      {{
        [](const std::uint32_t* p) -> std::uint32_t { return (std::uint32_t(              p[1U] & p[2U]) | std::uint32_t(std::uint32_t(~p[1U]) & p[3U])); },
        [](const std::uint32_t* p) -> std::uint32_t { return  std::uint32_t(std::uint32_t(p[1U] ^ p[2U]) ^ p[3U]); },
        [](const std::uint32_t* p) -> std::uint32_t { return  std::uint32_t(std::uint32_t(p[1U] & p[2U]) | std::uint32_t(p[1U] & p[3U]) | std::uint32_t(p[2U] & p[3U])); },
        [](const std::uint32_t* p) -> std::uint32_t { return (std::uint32_t(              p[1U] ^ p[2U]) ^ p[3U]); }
      }};
    }

  public:
    using result_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(20))>;

    hash_sha1() = default;

    hash_sha1(const hash_sha1&) = default;
    hash_sha1(hash_sha1&&) noexcept = default;

    virtual ~hash_sha1() = default;

    hash_sha1& operator=(const hash_sha1&) = default;
    hash_sha1& operator=(hash_sha1&&) noexcept = default;

    virtual void initialize()
    {
      base_class_type::initialize();

      message_hash[static_cast<std::size_t>(UINT8_C(0))] = static_cast<std::uint32_t>(UINT32_C(0x67452301));
      message_hash[static_cast<std::size_t>(UINT8_C(1))] = static_cast<std::uint32_t>(UINT32_C(0xEFCDAB89));
      message_hash[static_cast<std::size_t>(UINT8_C(2))] = static_cast<std::uint32_t>(UINT32_C(0x98BADCFE));
      message_hash[static_cast<std::size_t>(UINT8_C(3))] = static_cast<std::uint32_t>(UINT32_C(0x10325476));
      message_hash[static_cast<std::size_t>(UINT8_C(4))] = static_cast<std::uint32_t>(UINT32_C(0xC3D2E1F0));
    }

    virtual void finalize()
    {
      typename base_class_type::message_block_type the_last_message_block;

      std::copy(base_class_type::message_buffer.cbegin(),
                base_class_type::message_buffer.cbegin() + base_class_type::message_index,
                the_last_message_block.begin());

      // Create the padding. Begin by setting the leading padding byte to 0x80.
      the_last_message_block[base_class_type::message_index] = static_cast<std::uint8_t>(UINT8_C(0x80));

      ++base_class_type::message_index;

      // Fill the rest of the padding bytes with zero.
      std::fill(the_last_message_block.begin() + base_class_type::message_index,
                the_last_message_block.end(),
                static_cast<std::uint8_t>(UINT8_C(0)));

      // Do we need an extra block? If so, then transform the
      // current block and pad an additional block.
      if(base_class_type::message_index > static_cast<std::uint16_t>(base_class_type::message_buffer_static_size - 8U))
      {
        base_class_type::message_buffer = the_last_message_block;

        perform_algorithm();

        the_last_message_block.fill(static_cast<std::uint8_t>(UINT8_C(0)));
      }

      // Encode the number of bits. Simultaneously convert the number of bytes
      // to the number of bits by performing a left-shift of 3 on the byte-array.
      // The hash_sha1 stores the 8 bytes of the bit counter in reverse order,
      // with the lowest byte being stored at the highest position of the buffer
      std::uint8_t carry = static_cast<std::uint8_t>(UINT8_C(0));

      auto local_message_length_total = static_cast<std::uint64_t>(base_class_type::message_length_total);

      std::for_each(the_last_message_block.rbegin(),
                    the_last_message_block.rbegin() + static_cast<std::size_t>(UINT8_C(8)),
                    [&carry, &local_message_length_total](std::uint8_t& the_byte)
                    {
                      const std::uint_least16_t the_word =
                        static_cast<std::uint_least16_t>(local_message_length_total << static_cast<unsigned>(UINT8_C(3)));

                      the_byte = static_cast<std::uint8_t>(the_word | carry);

                      local_message_length_total >>= static_cast<unsigned>(UINT8_C(8));

                      carry =
                        static_cast<std::uint8_t>
                        (
                            static_cast<std::uint8_t>(the_word >> static_cast<unsigned>(UINT8_C(8)))
                          & static_cast<std::uint8_t>(UINT8_C(0x07))
                        );
                    });

      base_class_type::message_length_total = (typename base_class_type::count_type) local_message_length_total;

      base_class_type::message_buffer = the_last_message_block;

      perform_algorithm();
    }

    void get_result(typename result_type::pointer result)
    {
      // Extract the hash result from the message digest state.
      detail::convert_uint32_input_to_uint8_output_reverse(
        message_hash.data(),
        message_hash.data() + static_cast<std::size_t>(std::tuple_size<result_type>::value / sizeof(std::uint32_t)),
        result);
    }

  private:
    using context_type = std::array<std::uint32_t, static_cast<std::size_t>(std::tuple_size<result_type>::value / static_cast<std::size_t>(UINT8_C(4)))>;

    context_type message_hash;

    virtual void perform_algorithm();
  };

  template <typename my_count_type>
  void hash_sha1<my_count_type>::perform_algorithm()
  {
    // Apply the hash algorithm to a full data block.
    constexpr std::array<std::uint32_t, static_cast<std::size_t>(UINT8_C(4))> constants
    {
      static_cast<std::uint32_t>(UINT32_C(0x5A827999)),
      static_cast<std::uint32_t>(UINT32_C(0x6ED9EBA1)),
      static_cast<std::uint32_t>(UINT32_C(0x8F1BBCDC)),
      static_cast<std::uint32_t>(UINT32_C(0xCA62C1D6))
    };

    using transform_block_type = std::array<std::uint32_t, static_cast<std::size_t>(base_class_type::message_buffer_static_size / static_cast<std::uint16_t>(UINT8_C(4)))>;

    transform_block_type transform_block;

    detail::convert_uint8_input_to_uint32_output_reverse(
      base_class_type::message_buffer.data(),
      base_class_type::message_buffer.data() + static_cast<std::size_t>(base_class_type::message_buffer_static_size),
      transform_block.data());

    context_type hash_tmp = message_hash;

    std::uint8_t loop_index = static_cast<std::uint8_t>(UINT8_C(0));

    for(std::uint8_t loop_counter = static_cast<std::uint8_t>(UINT8_C(0)); loop_counter < static_cast<std::uint8_t>(UINT8_C(80)); ++loop_counter)
    {
      if(loop_counter >= static_cast<std::uint8_t>(UINT8_C(16)))
      {
        const auto the_dword =
          static_cast<std::uint32_t>
          (
              transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter + 13U) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter +  8U) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(static_cast<std::uint8_t>(loop_counter +  2U) & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
            ^ transform_block[static_cast<std::size_t>(                          loop_counter        & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
          );

        transform_block[static_cast<std::size_t>(loop_counter & std::uint8_t(UINT8_C(0x0F)))] =
          detail::circular_left_shift<1U>(the_dword);

        if     (loop_counter == static_cast<std::uint8_t>(UINT8_C(20))) { loop_index = static_cast<std::uint8_t>(UINT8_C(1)); }
        else if(loop_counter == static_cast<std::uint8_t>(UINT8_C(40))) { loop_index = static_cast<std::uint8_t>(UINT8_C(2)); }
        else if(loop_counter == static_cast<std::uint8_t>(UINT8_C(60))) { loop_index = static_cast<std::uint8_t>(UINT8_C(3)); }
      }

      const auto tmp32 =
        static_cast<std::uint32_t>
        (
            detail::circular_left_shift<5U>(hash_tmp[0U])
          + transform_functions()[loop_index](hash_tmp.data())
          + hash_tmp[4U]
          + transform_block[static_cast<std::size_t>(loop_counter & static_cast<std::uint8_t>(UINT8_C(0x0F)))]
          + constants[loop_index]
        );

      hash_tmp[4U] = hash_tmp[3U];
      hash_tmp[3U] = hash_tmp[2U];
      hash_tmp[2U] = detail::circular_left_shift<30U>(hash_tmp[1U]);
      hash_tmp[1U] = hash_tmp[0U];
      hash_tmp[0U] = tmp32;
    }

    // Update the hash state with the transformation results.
    std::transform(message_hash.cbegin     (),
                   message_hash.cend       (),
                   hash_tmp.cbegin         (),
                   message_hash.begin      (),
                   std::plus<std::uint32_t>());

    base_class_type::message_index = static_cast<std::uint_least16_t>(UINT8_C(0));
  }

  } } } // namespace math::checksums::hash

#endif // HASH_SHA1_2013_09_03_H_
