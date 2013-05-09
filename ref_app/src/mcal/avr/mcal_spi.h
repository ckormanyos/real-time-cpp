///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_SPI_2012_05_24_H_
  #define _MCAL_SPI_2012_05_24_H_

  #include <util/utility/util_type.h>
  #include <util/utility/util_communication.h>
  #include <util/utility/util_circular_buffer.h>

  namespace mcal
  {
    namespace spi
    {
      typedef void config_type;

      void init(const config_type*);

      class spi_communication : public util::communication
      {
      public:
        spi_communication() { }
        virtual ~spi_communication();
      };
    }
  }

#endif // _MCAL_SPI_2012_05_24_H_
