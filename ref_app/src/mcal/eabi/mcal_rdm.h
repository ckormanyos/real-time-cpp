///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_RDM_2013_06_07_H_
  #define _MCAL_RDM_2013_06_07_H_

  #include <cstdint>

  namespace mcal
  {
    namespace rdm
    {
      typedef std::uint32_t address_type;
      constexpr address_type address_offset = address_type(0x20000000UL);
    }
  }

#endif // _MCAL_RDM_2013_06_07_H_
