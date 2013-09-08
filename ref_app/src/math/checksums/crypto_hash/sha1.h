
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2013.
//
// \license LGPLv3
// md5 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// chrono is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser Public License for more details.
// You should have received a copy of the GNU Lesser Public License
// along with chrono. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _SHA1_2013_09_08_H_
  #define _SHA1_2013_09_08_H_

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <functional>

  class sha1_context
  {
  public:
    sha1_context() { }

    void sha1_initialize();
    void sha1_input(const char* message_hash, std::size_t length_message);

    void sha1_finalize();

    std::array<std::uint32_t, 5> get_hash();

  private:
    std::array<std::uint8_t, 64> block_message;
    std::array<std::uint8_t, 20> hash_bytes;
    std::array<std::uint8_t,  8> padding_length;

    std::array<std::uint32_t, 5> hash_message;
    std::uint_fast8_t index_block_message;

    void process_message();

    template<const std::uint_fast8_t digits_shift>
    static std::uint32_t circular_shift(const std::uint32_t& shift_32word)
    {
      return (shift_32word << digits_shift) | (shift_32word >> (32 - digits_shift));
    }
  };

  void sha1_context::sha1_initialize()
  {
    hash_message[0] = UINT32_C(0x67452301);
    hash_message[1] = UINT32_C(0xEFCDAB89);
    hash_message[2] = UINT32_C(0x98BADCFE);
    hash_message[3] = UINT32_C(0x10325476);
    hash_message[4] = UINT32_C(0xC3D2E1F0);

    padding_length.fill(0);
    block_message.fill(0);
    index_block_message = 0;
  }

  void sha1_context::sha1_input(const char* message_hash, std::size_t length_message)
  {
    while(length_message != 0)
    {
      block_message[index_block_message] = static_cast<std::uint8_t>(*message_hash);

      ++index_block_message;

      padding_length[0] += 8;
      if(padding_length[0] == 0)
      {
        ++padding_length[1];
        if(padding_length[1] == 0)
        {
          ++padding_length[2];
          if(padding_length[2] == 0)
          {
            ++padding_length[3];
            if(padding_length[3] == 0)
            {
              ++padding_length[4];
              if(padding_length[4] == 0)
              {
                ++padding_length[5];
                if(padding_length[5] == 0)
                {
                  ++padding_length[6];
                  if(padding_length[6] == 0)
                  {
                    ++padding_length[7];
                    if(padding_length[7] == 0)
                    {
                      return;
                    }
                  }
                }
              }
            }
          }
        }
      }

      if(index_block_message == 64U)
      {
        process_message();
      }

      message_hash++;
      length_message--;
    }
  }

  void sha1_context::process_message()
  {
    const std::array<std::uint32_t, 4> constants_definition =
    {{
      UINT32_C(0x5A827999),
      UINT32_C(0x6ED9EBA1),
      UINT32_C(0x8F1BBCDC),
      UINT32_C(0xCA62C1D6)
    }};

    std::uint_fast8_t loop_counter;
    std::uint32_t     temporary_32word;

    std::array<std::uint32_t, 80U> sequence_32word;
    std::array<std::uint32_t,  5U> buffer_32word;

    for(loop_counter = 0U; loop_counter < 16U; loop_counter++)
    {
      sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + 0U]) << 24)
                                        | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + 1U]) << 16)
                                        | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + 2U]) <<  8)
                                        | (static_cast<std::uint32_t>(block_message[(loop_counter * 4U) + 3U]) <<  0));
    }

    for(loop_counter = 16; loop_counter < 80; loop_counter++)
    {
      const std::uint32_t shift_amount = (sequence_32word[loop_counter -  3U] ^
                                          sequence_32word[loop_counter -  8U] ^
                                          sequence_32word[loop_counter - 14U] ^
                                          sequence_32word[loop_counter - 16U]);

      sequence_32word[loop_counter] = circular_shift<1U>(shift_amount);
    }

    buffer_32word = hash_message;

    for(loop_counter = 0U; loop_counter < 20U; loop_counter++)
    {
      temporary_32word =   circular_shift<5U>(buffer_32word[0])
                         + (std::uint32_t(buffer_32word[1] & buffer_32word[2]) | std::uint32_t(std::uint32_t(~buffer_32word[1]) & buffer_32word[3]))
                         + buffer_32word[4] + sequence_32word[loop_counter] + constants_definition[0];

      buffer_32word[4] = buffer_32word[3];
      buffer_32word[3] = buffer_32word[2];
      buffer_32word[2] = circular_shift<30U>(buffer_32word[1]);
      buffer_32word[1] = buffer_32word[0];
      buffer_32word[0] = temporary_32word;
    }

    for(loop_counter = 20; loop_counter < 40; loop_counter++)
    {
      temporary_32word =   circular_shift<5U>(buffer_32word[0])
                         + std::uint32_t(buffer_32word[1] ^ buffer_32word[2] ^ buffer_32word[3])
                         + buffer_32word[4] + sequence_32word[loop_counter] + constants_definition[1];

      buffer_32word[4] = buffer_32word[3];
      buffer_32word[3] = buffer_32word[2];
      buffer_32word[2] = circular_shift<30U>(buffer_32word[1]);
      buffer_32word[1] = buffer_32word[0];
      buffer_32word[0] = temporary_32word;
    }

    for(loop_counter = 40; loop_counter < 60; loop_counter++)
    {
      temporary_32word =   circular_shift<5U>(buffer_32word[0])
                         + std::uint32_t(  std::uint32_t(buffer_32word[1] & buffer_32word[2])
                                         | std::uint32_t(buffer_32word[1] & buffer_32word[3])
                                         | std::uint32_t(buffer_32word[2] & buffer_32word[3]))
                         + buffer_32word[4] + sequence_32word[loop_counter] + constants_definition[2];

      buffer_32word[4] = buffer_32word[3];
      buffer_32word[3] = buffer_32word[2];
      buffer_32word[2] = circular_shift<30U>(buffer_32word[1]);
      buffer_32word[1] = buffer_32word[0];
      buffer_32word[0] = temporary_32word;
    }

    for(loop_counter = 60; loop_counter < 80; loop_counter++)
    {
      temporary_32word =   circular_shift<5U>(buffer_32word[0])
                         + std::uint32_t(buffer_32word[1] ^ buffer_32word[2] ^ buffer_32word[3])
                         + buffer_32word[4] + sequence_32word[loop_counter] + constants_definition[3];

      buffer_32word[4] = buffer_32word[3];
      buffer_32word[3] = buffer_32word[2];
      buffer_32word[2] = circular_shift<30U>(buffer_32word[1]);
      buffer_32word[1] = buffer_32word[0];
      buffer_32word[0] = temporary_32word;
    }

    std::transform(hash_message.cbegin(),
                   hash_message.cend(),
                   buffer_32word.cbegin(),
                   hash_message.begin(),
                   std::plus<std::uint32_t>());

    index_block_message = 0;
  }

  void sha1_context::sha1_finalize()
  {
    if(index_block_message > 55)
    {
      block_message[index_block_message++] = 0x80;

      while(index_block_message < 64)
      {
        block_message[index_block_message++] = 0;
      }

      process_message();

      while(index_block_message < 56)
      {
        block_message[index_block_message++] = 0;
      }
    }
    else
    {
      block_message[index_block_message++] = 0x80;

      while(index_block_message < 56)
      {
        block_message[index_block_message++] = 0;
      }
    }

    std::copy(padding_length.rbegin(), padding_length.rend(), block_message.begin() + 56U);

    process_message();
  }

  std::array<std::uint32_t, 5> sha1_context::get_hash()
  {
    return hash_message;
  }

#endif // _SHA1_2013_09_08_H_
