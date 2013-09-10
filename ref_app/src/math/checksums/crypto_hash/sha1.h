
///////////////////////////////////////////////////////////////////////////////
//  Copyright Arwed Steuer 2013.
//
// \license LGPLv3
// sha1 is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// sha1 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser Public License for more details.
// You should have received a copy of the GNU Lesser Public License
// along with sha1. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef SHA1_H_INCLUDED
#define SHA1_H_INCLUDED

#include <array>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "crypto_hash_base.h"

class sha1 : public crypto_hash_base
{
public:
  sha1();
  sha1(char* message_hash, std::uint_fast64_t length_message);
  sha1(const sha1& other);

  void input(char* message_hash, std::uint_fast64_t length_message);
  void input(char* message_hash, std::uint_fast64_t length_message, bool the_other_method);

  std::array<std::uint8_t, 20> byte_array_result();
  std::array<std::uint32_t, 5> dword_array_result();
  std::string string_result();

  void reset();

private:
  bool                         method2;
  bool                         finalized;
  std::uint_fast8_t            index_block_message;
  std::uint64_t                padding_length;
  std::array<std::uint32_t, 5> hash_message;
  std::array<std::uint8_t, 64> block_message;

  void finalize();
  void process1();
  void process2();

  static std::uint32_t circular_shift(std::uint_fast8_t digits_shift, const std::uint32_t& shift_32word)
  {
    return (shift_32word << digits_shift) | (shift_32word >> (32 - digits_shift));
  }
  std::uint32_t constants(std::uint_fast8_t looper);
  std::uint32_t functions(std::uint_fast8_t looper, std::uint32_t first_dword, std::uint32_t dword, std::uint32_t last_dword);
};

////IMPLEMENTATION////

sha1::sha1() : method2            (),
               finalized          (),
               index_block_message(),
               padding_length     (),
               hash_message       ( {{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0}} ),
               block_message      ()
{
}

sha1::sha1(char* message_hash,
           std::uint_fast64_t length_message) : method2            (),
                                                finalized          (),
                                                index_block_message(),
                                                padding_length     (),
                                                hash_message       ( {{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0}} ),
                                                block_message      ()
{
  input(message_hash, length_message, false);
}

sha1::sha1(const sha1& other) : crypto_hash_base   (other),
                                method2            (other.method2),
                                finalized          (other.finalized),
                                index_block_message(other.index_block_message),
                                padding_length     (other.padding_length),
                                hash_message       (other.hash_message),
                                block_message      (other.block_message)
{
}


void sha1::input(char* message_hash, std::uint_fast64_t length_message)
{
  method2 = false;

  while(length_message != 0)
  {
    block_message[index_block_message++] = *message_hash;

    if(index_block_message == 64)
    {
      padding_length += 512;
      if(method2)
      {
        process2();
      }
      else
      {
        process1();
      }
    }

    if(length_message < 64)
    {
      padding_length += 8;
    }

    message_hash++;
    length_message--;
  }
}

void sha1::input(char* message_hash, std::uint_fast64_t length_message, bool the_other_method)
{
  method2 = the_other_method;

  while(length_message != 0)
  {
    block_message[index_block_message++] = *message_hash;

    if(index_block_message == 64)
    {
      padding_length += 512;
      if(method2)
      {
        process2();
      }
      else
      {
        process1();
      }
    }

    if(length_message < 64)
    {
      padding_length += 8;
    }

    message_hash++;
    length_message--;
  }
}

void sha1::process1()
{
  std::uint_fast8_t loop_counter;
  std::uint32_t temporary_32word;

  std::array<std::uint32_t, 80> sequence_32word;
  std::array<std::uint32_t,  5> buffer_32word;

  for(loop_counter = 0; loop_counter < 16; loop_counter++)
  {
    sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(block_message[(loop_counter * 4)    ]) << 24)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 1]) << 16)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 2]) <<  8)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 3]) <<  0));
  }

  for(loop_counter = 16; loop_counter < 80; loop_counter++)
  {
    const std::uint32_t word_shift = (sequence_32word[loop_counter -  3] ^
                                      sequence_32word[loop_counter -  8] ^
                                      sequence_32word[loop_counter - 14] ^
                                      sequence_32word[loop_counter - 16]);

    sequence_32word[loop_counter] = circular_shift(1, word_shift);
  }

  buffer_32word = hash_message;

  for(loop_counter = 0; loop_counter < 80; loop_counter++)
  {
    temporary_32word =  circular_shift(5, buffer_32word[0]) +
                        functions(loop_counter, buffer_32word[1], buffer_32word[2], buffer_32word[3]) +
                        buffer_32word[4] + sequence_32word[loop_counter] + constants(loop_counter);

    buffer_32word[4] = buffer_32word[3];
    buffer_32word[3] = buffer_32word[2];
    buffer_32word[2] = circular_shift(30, buffer_32word[1]);
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

void sha1::process2()
{
  std::uint_fast8_t loop_counter;
  std::uint_fast8_t counter_loop;
  std::uint32_t temporary_32word;

  std::array<std::uint32_t, 16> sequence_32word;
  std::array<std::uint32_t,  5> buffer_32word;

  for(loop_counter = 0; loop_counter < 16; loop_counter++)
  {
    sequence_32word[loop_counter]  = (  (static_cast<std::uint32_t>(block_message[(loop_counter * 4)    ]) << 24)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 1]) << 16)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 2]) <<  8)
                                      | (static_cast<std::uint32_t>(block_message[(loop_counter * 4) + 3]) <<  0));
  }

  buffer_32word = hash_message;

  for(loop_counter = 0; loop_counter < 80; loop_counter++)
  {
    counter_loop = loop_counter & 0x0F;

    if(loop_counter >= 16)
    {
      sequence_32word[counter_loop] = circular_shift(1, sequence_32word[(counter_loop + 13) & 0x0F] ^
                                                        sequence_32word[(counter_loop +  8) & 0x0F] ^
                                                        sequence_32word[(counter_loop +  2) & 0x0F] ^
                                                        sequence_32word[counter_loop]);
    }

    temporary_32word =  circular_shift(5, buffer_32word[0]) +
                        functions(loop_counter, buffer_32word[1], buffer_32word[2], buffer_32word[3]) +
                        buffer_32word[4] + sequence_32word[counter_loop] + constants(loop_counter);

    buffer_32word[4] = buffer_32word[3];
    buffer_32word[3] = buffer_32word[2];
    buffer_32word[2] = circular_shift(30, buffer_32word[1]);
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

std::uint32_t sha1::constants(std::uint_fast8_t looper)
{
  std::array<std::uint32_t, 4> definition = {{0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6}};

  if(looper < 20)
    return definition[0];
  if(looper < 40)
    return definition[1];
  if(looper < 60)
    return definition[2];
  return definition[3];
}

std::uint32_t sha1::functions(std::uint_fast8_t looper, std::uint32_t first_dword, std::uint32_t dword, std::uint32_t last_dword)
{
  if(looper < 20)
    return ((first_dword & dword) | ((~first_dword) & last_dword));
  if(looper < 40)
    return (first_dword ^ dword ^ last_dword);
  if(looper < 60)
    return ((first_dword & dword) | (first_dword & last_dword) | (dword & last_dword));
  return (first_dword ^ dword ^ last_dword);

}



void sha1::finalize()
{
  if (index_block_message > 55)
  {
    block_message[index_block_message++] = 0x80;
    while(index_block_message < 64)
    {
      block_message[index_block_message++] = 0;
    }

    if(method2)
    {
      process2();
    }
    else
    {
      process1();
    }

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

  std::array<std::uint8_t, 8> bytes_padding_length = {{(std::uint8_t)(padding_length >> 56),
                                                        (std::uint8_t)(padding_length >> 48),
                                                        (std::uint8_t)(padding_length >> 40),
                                                        (std::uint8_t)(padding_length >> 32),
                                                        (std::uint8_t)(padding_length >> 24),
                                                        (std::uint8_t)(padding_length >> 16),
                                                        (std::uint8_t)(padding_length >>  8),
                                                        (std::uint8_t)(padding_length >>  0)}};

  std::copy(bytes_padding_length.begin(),
            bytes_padding_length.end(),
            block_message.begin() + 56);

  if(method2)
  {
    process2();
  }
  else
  {
    process1();
  }

  finalized = true;
}

std::array<std::uint8_t, 20> sha1::byte_array_result()
{
  if(!finalized)finalize();

  std::array<std::uint8_t, 20> result;

  convert_uint32_input_to_uint8_output(hash_message.cbegin(), hash_message.cend(), result.begin());

  return result;
}

std::array<std::uint32_t, 5> sha1::dword_array_result()
{
  if(!finalized)finalize();

  return hash_message;
}

std::string sha1::string_result()
{
  if(!finalized)finalize();

  std::stringstream stream;

  std::for_each(hash_message.begin(),
                hash_message.end(),
                [&stream](std::uint32_t this_dword)
                {
                  stream << std::setw(8) << std::setfill('0') << std::hex << this_dword << " ";
                });

  stream << "(Echtzeit)";
  std::string result(stream.str());
  return result;
}



void sha1::reset()
{
  block_message.fill(0);

  hash_message = {{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0}};

  padding_length = 0;
  index_block_message = 0;
  finalized = false;
}

#endif // SHA1_H_INCLUDED
