///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <math/checksums/crc/cpp_crc_base.h>

math::checksums::crc::cpp_crc_base& math::checksums::crc::cpp_crc_base::operator=(const cpp_crc_base& other_crc)
{
  if(this != &other_crc)
  {
    // Make sure that the size of the assignment remains
    // within bounds, even if it truncates the result.
    const std::uint_fast8_t assignment_size =
      (std::min)(my_size(), other_crc.my_size());

    for(std::uint_fast8_t i = 0U; i < assignment_size; ++i)
    {
      // Set the result of the checksum one byte at a time.
      *(reinterpret_cast<      std::uint8_t*>(storage())            + i) =
      *(reinterpret_cast<const std::uint8_t*>(other_crc.cstorage()) + i);
    }
  }

  return *this;
}
