///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_RDM_2013_06_07_H_
  #define _MCAL_RDM_2013_06_07_H_

  #include <cstdint>
  #include <mcal_port.h>

  namespace mcal
  {
    namespace rdm
    {
      typedef std::uint32_t address_type;
      constexpr address_type address_offset = address_type(0x402F0000UL);

      typedef mcal::port::port_pin<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::gpio1_base,
                                   UINT32_C(14)> port_rdm_type;
    }
  }

#endif // _MCAL_RDM_2013_06_07_H_
