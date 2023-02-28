///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_BASE_2013_09_05_H_
  #define HASH_BASE_2013_09_05_H_

  #include <limits>

  #include <math/checksums/hash/hash_detail.h>

  namespace math { namespace checksums { namespace hash {

  template<typename CountType,
           const std::uint16_t ResultBitCount,
           const std::uint16_t MessageBufferSize,
           const std::uint16_t MessageLengthTotalBitCount>
  class hash_base
  {
  public:
    using count_type = CountType;

    using result_type = std::array<std::uint8_t, static_cast<std::size_t>(ResultBitCount / static_cast<std::uint16_t>(UINT8_C(8)))>;

    static_assert
    (
           std::numeric_limits<count_type>::is_specialized
      &&   std::numeric_limits<count_type>::is_integer
      && (!std::numeric_limits<count_type>::is_signed)
      && (std::numeric_limits<count_type>::radix == static_cast<int>(INT8_C(2)))
      && (std::numeric_limits<count_type>::digits >= static_cast<int>(INT8_C(16)))
      && (static_cast<int>(std::numeric_limits<count_type>::digits % static_cast<int>(INT8_C(8))) == static_cast<int>(INT8_C(0))),
      "Error: The count type must be an unsigned integer with radix 2, that is 16 bits or wider, and having a multiple of 8 bits"
    );

    virtual ~hash_base() = default;

    virtual auto initialize() -> void
    {
      message_index        = static_cast<std::uint_least16_t>(UINT8_C(0));
      message_length_total = static_cast<count_type>(UINT8_C(0));

      message_buffer.fill(static_cast<std::uint8_t>(UINT8_C(0)));
    }

    auto process(const std::uint8_t* message, const count_type count) -> void
    {
      auto process_index      = count_type { };
      auto process_chunk_size = count_type { };

      while(process_index < count)
      {
        message_index        = static_cast<std::uint_least16_t>(message_index        + process_chunk_size);
        message_length_total = static_cast<count_type>         (message_length_total + process_chunk_size);
        process_index        = static_cast<count_type>         (process_index        + process_chunk_size);

        if(message_index == message_buffer_static_size())
        {
          my_perform_algorithm();
        }

        process_chunk_size = (std::min)(static_cast<count_type>(count - process_index),
                                        static_cast<count_type>(message_buffer_static_size() - message_index));

        std::copy(message + static_cast<std::size_t>(process_index),
                  message + static_cast<std::size_t>(process_index + process_chunk_size),
                  message_buffer.begin() + static_cast<std::size_t>(message_index));

      }
    }

    auto finalize() -> void
    {
      // Create the padding. Begin by setting the leading padding byte to 0x80.
      message_buffer[message_index] = static_cast<std::uint8_t>(UINT8_C(0x80));

      ++message_index;

      // We need an extra block because there are not enough bytes
      // available for storing the total bit count. So we must
      // transform the current block, then create and pad yet another
      // additional block.

      if(static_cast<std::uint16_t>(message_index + static_cast<std::uint_least16_t>(message_length_total_width())) > message_buffer_static_size())
      {
        my_perform_algorithm();
      }

      // Encode the total number of bits in the final transform buffer.
      // Here, we can easily see the conversion of the number of bytes
      // to the number of bits. This is done by performing a left-shift
      // of 3 on the variable "message_length_total".

      auto carry = static_cast<std::uint_fast8_t>(UINT8_C(0));

      for(auto   ri  = message_buffer.rbegin();
                 ri != message_buffer.rbegin() + message_length_total_width();
               ++ri)
      {
        const std::uint_least16_t the_word =
          static_cast<std::uint_least16_t>
          (
            static_cast<std::uint_least16_t>(message_length_total) << static_cast<unsigned>(UINT8_C(3))
          );

        *ri = static_cast<std::uint8_t>(the_word | carry);

        message_length_total =
          static_cast<count_type>
          (
            message_length_total >> static_cast<unsigned>(UINT8_C(8))
          );

        carry =
          static_cast<std::uint_fast8_t>
          (
              static_cast<std::uint_fast8_t>(the_word >> static_cast<unsigned>(UINT8_C(8)))
            & static_cast<std::uint_fast8_t>(UINT8_C(0x07))
          );
      }

      my_perform_algorithm();
    }

    auto get_result(typename result_type::pointer result) -> void
    {
      // Extract the hash result from the message digest state.
      detail::convert_uint32_input_to_uint8_output_reverse
      (
        transform_context.data(),
        transform_context.data() + static_cast<std::size_t>(std::tuple_size<result_type>::value / sizeof(std::uint32_t)),
        result
      );
    }

    auto hash(const std::uint8_t* message, const count_type count) -> void
    {
      this->initialize();
      this->process(message, count);
      this->finalize();
    }

  protected:
    using message_block_type = std::array<std::uint8_t, static_cast<std::size_t>(MessageBufferSize)>;

    using context_type = std::array<std::uint32_t, static_cast<std::size_t>(std::tuple_size<result_type>::value / sizeof(std::uint32_t))>;

    static constexpr auto message_buffer_static_size() -> std::uint16_t
    {
      return static_cast<std::uint16_t>(std::tuple_size<message_block_type>::value);
    }

    std::uint_least16_t message_index        { };
    count_type          message_length_total { };
    message_block_type  message_buffer       { };
    context_type        transform_context    { };

    hash_base() = default;

    hash_base(const hash_base&) = default;
    hash_base(hash_base&&) noexcept = default;

    auto operator=(const hash_base& other) -> hash_base& = default;
    auto operator=(hash_base&& other) noexcept -> hash_base& = default;

  private:
    static constexpr auto message_length_total_width() noexcept -> std::uint16_t
    {
      return
        static_cast<std::uint16_t>
        (
          MessageLengthTotalBitCount / static_cast<std::uint16_t>(UINT8_C(8))
        );
    }

    virtual auto perform_algorithm() -> void = 0;

    auto my_perform_algorithm() -> void
    {
      this->perform_algorithm();

      message_index = static_cast<std::uint_least16_t>(UINT8_C(0));

      message_buffer.fill(static_cast<std::uint8_t>(UINT8_C(0)));
    }
  };

  } } } // namespace math::checksums::hash

#endif // HASH_BASE_2013_09_05_H_
