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
           const std::uint16_t MessageBufferSize>
  class hash_base
  {
  public:
    using count_type = CountType;

    static_assert(   ( std::numeric_limits<count_type>::is_specialized == true)
                  && ( std::numeric_limits<count_type>::is_integer     == true)
                  && ( std::numeric_limits<count_type>::is_signed      == false)
                  && ( std::numeric_limits<count_type>::radix          == 2)
                  && ((std::numeric_limits<count_type>::digits % 8)    == 0),
                  "Error: The count type must be an unsigned integer with radix 2, having a multiple of 8 bits");

    virtual ~hash_base() = default;

    virtual auto initialize() -> void
    {
      message_index        = static_cast<std::uint_least16_t>(UINT8_C(0));
      message_length_total = static_cast<count_type>(UINT8_C(0));
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

        if(message_index == message_buffer_static_size)
        {
          this->perform_algorithm();
        }

        process_chunk_size = (std::min)(static_cast<count_type>(count - process_index),
                                        static_cast<count_type>(message_buffer_static_size - message_index));

        std::copy(message + static_cast<std::size_t>(process_index),
                  message + static_cast<std::size_t>(process_index + process_chunk_size),
                  message_buffer.begin() + static_cast<std::size_t>(message_index));

      }
    }

    auto finalize() -> void
    {
      message_block_type the_last_message_block;

      std::copy(message_buffer.cbegin(),
                message_buffer.cbegin() + message_index,
                the_last_message_block.begin());

      // Create the padding. Begin by setting the leading padding byte to 0x80.
      the_last_message_block[message_index] = static_cast<std::uint8_t>(UINT8_C(0x80));

      ++message_index;

      // Fill the rest of the padding bytes with zero.
      std::fill(the_last_message_block.begin() + message_index,
                the_last_message_block.end(),
                static_cast<std::uint8_t>(UINT8_C(0)));

      // Do we need an extra block? If so, then transform the
      // current block and pad an additional block.
      if(message_index > static_cast<std::uint16_t>(message_buffer_static_size - 8U))
      {
        message_buffer = the_last_message_block;

        perform_algorithm();

        the_last_message_block.fill(static_cast<std::uint8_t>(UINT8_C(0)));
      }

      // Encode the number of bits. Simultaneously convert the number of bytes
      // to the number of bits by performing a left-shift of 3 on the byte-array.
      // The hash_sha1 stores the 8 bytes of the bit counter in reverse order,
      // with the lowest byte being stored at the highest position of the buffer
      auto carry = static_cast<std::uint8_t>(UINT8_C(0));

      auto local_message_length_total = static_cast<std::uint64_t>(message_length_total);

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

      message_length_total = static_cast<count_type>(local_message_length_total);

      message_buffer = the_last_message_block;

      this->perform_algorithm();
    }

    auto hash(const std::uint8_t* message, const count_type count) -> void
    {
      this->initialize();
      this->process(message, count);
      this->finalize();
    }

  protected:
    static constexpr auto message_buffer_static_size = MessageBufferSize;

    using message_block_type = std::array<std::uint8_t, static_cast<std::size_t>(message_buffer_static_size)>;

    std::uint_least16_t message_index        { };
    count_type          message_length_total { };
    message_block_type  message_buffer       { };

    hash_base() = default;

    hash_base(const hash_base&) = default;
    hash_base(hash_base&&) noexcept = default;

    auto operator=(const hash_base& other) -> hash_base& = default;
    auto operator=(hash_base&& other) noexcept -> hash_base& = default;

  private:
    virtual auto perform_algorithm() -> void = 0;
  };

  } } } // namespace math::checksums::hash

#endif // HASH_BASE_2013_09_05_H_
