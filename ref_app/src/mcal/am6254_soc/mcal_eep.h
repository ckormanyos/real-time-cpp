///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_EEP_2018_12_15_H_
  #define MCAL_EEP_2018_12_15_H_

  #include <cstdint>

  namespace mcal
  {
    namespace eep
    {
      using config_type  = void;
      using address_type = std::uint32_t;

      inline void init(const config_type*) { }

      inline void         write(const address_type addr, const std::uint8_t data) { static_cast<void>(addr); static_cast<void>(data); }
      inline std::uint8_t read (const address_type addr) { static_cast<void>(addr); return UINT8_C(0); }
    }
  }

#endif // MCAL_EEP_2018_12_15_H_
