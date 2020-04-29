///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_2012_05_24_H_
  #define MCAL_SPI_2012_05_24_H_

  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  typedef void config_type;

  void init(const config_type*);

  util::communication_base& spi0();

  } }

#endif // MCAL_SPI_2012_05_24_H_
