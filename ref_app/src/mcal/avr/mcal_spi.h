///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_SPI_2012_05_24_H_
  #define _MCAL_SPI_2012_05_24_H_

  #include <util/utility/util_communication.h>

  extern "C" void __vector_17() __attribute__((signal, used, externally_visible));

  namespace mcal
  {
    namespace spi
    {
      typedef void config_type;

      void init(const config_type*);

      class spi_communication : public util::communication<16U>
      {
      public:
        spi_communication();
        virtual ~spi_communication();

        virtual bool send           (const std::uint8_t byte_to_send);
        virtual bool send           (const buffer_type& data_to_send);
        virtual bool recv           (std::uint8_t& byte_to_recv);
        virtual bool recv           (buffer_type& data_to_recv);
        virtual size_type recv_ready() const;
        virtual bool idle           () const;

        bool select_channel(const std::uint8_t ch);

      private:
        volatile bool send_is_active;
        std::uint8_t  channel;

        friend void ::__vector_17();
      };

      extern spi_communication the_spi;
    }
  }

#endif // _MCAL_SPI_2012_05_24_H_