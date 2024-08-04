///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_EEP_2018_12_15_H
  #define MCAL_EEP_2018_12_15_H

  #include <cstdint>

  namespace mcal
  {
    namespace eep
    {
      using config_type  = void;
      using address_type = std::uint32_t;

      inline auto init(const config_type*) -> void { }

      auto write(const address_type addr, const std::uint8_t data) -> void;
      auto read (const address_type addr) -> std::uint8_t;
    }
  }

#endif // MCAL_EEP_2018_12_15_H
