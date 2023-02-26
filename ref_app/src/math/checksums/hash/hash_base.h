///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_BASE_2013_09_05_H_
  #define HASH_BASE_2013_09_05_H_

  #include <algorithm>
  #include <cstdint>
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

    virtual void initialize()
    {
      message_index        = static_cast<std::uint_least16_t>(UINT8_C(0));
      message_length_total = static_cast<count_type>(UINT8_C(0));
    }

    void process(const std::uint8_t* message, const count_type count)
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

        std::copy(message +  process_index,
                  message + (process_index + process_chunk_size),
                  message_buffer.begin() + message_index);

      }
    }

    virtual void finalize() = 0;

    void hash(const std::uint8_t* message, const count_type count)
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

    hash_base& operator=(const hash_base& other) = default;
    hash_base& operator=(hash_base&& other) noexcept = default;

  private:
    virtual void perform_algorithm() = 0;
  };

  } } } // namespace math::checksums::hash

#endif // HASH_BASE_2013_09_05_H_
