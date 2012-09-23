#ifndef _MD5_2012_01_13_H_
  #define _MD5_2012_01_13_H_

  /* MD5

   January 2012:
   Modified by Christopher Kormanyos
   for C++2011 and port to microcontrollers

   converted to C++ class by Frank Thilo (thilo@unix-ag.org)
   for bzflag (http://www.bzflag.org)

   based on:

   md5.h and md5.c
   reference implementation of RFC 1321

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD5 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
   */

  #include <cstdint>
  #include <cstddef>
  #include <array>

  std::array<std::uint8_t, 16U> md5(const std::uint8_t* buffer, const std::size_t byte_count);

  inline std::array<std::uint8_t, 16U> md5(const char* str, const std::size_t len)
  {
    const std::uint8_t* buffer = static_cast<const std::uint8_t*>(static_cast<const void*>(str));
    return md5(buffer, len);
  }

#endif // _MD5_2012_01_13_H_
