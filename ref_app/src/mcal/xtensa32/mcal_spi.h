///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_2012_05_24_H_
  #define MCAL_SPI_2012_05_24_H_

  #include <cstdint>

  #include <util/utility/util_communication.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace spi {

  typedef void config_type;

  void init(const config_type*);

  class spi_communication : private util::noncopyable,
                            public util::communication_buffer_depth_one_byte
  {
  public:
    spi_communication() { }

    virtual ~spi_communication() { }

    virtual bool send(const std::uint8_t byte_to_send);
  };

  extern util::communication_base& spi0();

  } }

#endif // MCAL_SPI_2012_05_24_H_
