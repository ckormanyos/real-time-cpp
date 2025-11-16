///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H
  #define MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H

  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  class spi_software_dummy : public util::communication_buffer_depth_one_byte // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using base_class_type = util::communication_buffer_depth_one_byte;

  public:
    // This class implements a dummy SPI with no real functionality.

    spi_software_dummy() = default;

    ~spi_software_dummy() override = default;

    auto send(const std::uint8_t byte_to_send) -> bool override
    {
      static_cast<void>(byte_to_send);

      base_class_type::recv_buffer = 0U;

      return true;
    }

    auto   select() -> void override { }
    auto deselect() -> void override { }
  };

  } // namespace spi
  } // namespace mcal

#endif // MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H
