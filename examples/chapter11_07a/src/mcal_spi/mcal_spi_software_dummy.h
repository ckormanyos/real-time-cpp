///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H
  #define MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H

  #include <cstdint>

  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  class spi_software_dummy final
  {
  private:
    using communication_type = ::util::communication_base;

  public:
    // This class implements a dummy SPI with no real functionality.

    static auto init() -> void { }

    static auto send(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> bool
    {
      static_cast<void>(byte_to_send);

      byte_to_recv = std::uint8_t { UINT8_C(0) };

      return true;
    }

    static auto send_n(communication_type::send_iterator_type first,
                       communication_type::send_iterator_type last,
                       std::uint8_t& byte_to_recv) -> bool
    {
      while(first != last)
      {
        const auto byte_to_send = static_cast<communication_type::buffer_value_type>(*first++);

        static_cast<void>(send(byte_to_send, byte_to_recv));
      }

      return true;
    }

    static auto   select() -> void { }
    static auto deselect() -> void { }
  };

  } // namespace spi
  } // namespace mcal

#endif // MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H
