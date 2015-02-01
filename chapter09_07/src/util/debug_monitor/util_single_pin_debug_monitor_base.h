///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_
  #define _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_

  #include <algorithm>
  #include <array>
  #include <cstdint>
  #include <iterator>
  #include <mcal_port.h>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_two_part_data_manipulation.h>

  // Here, we are implementing a single-pin debug monituor.
  // It uses a UART emulated in software on a digitial I/O port
  // using a baud rate of 250 bits-per-second. A driver task
  // in the derived class implements the UART physical layer.

  // A skinny protocol called "BWD" is built on top of the
  // UART in order to support read/write of byte, word
  // and dword sized variables and data chunks. A protocol
  // task in the base class implements the BWD protocol.

  // Description of the BWD protocol:
  // 'b' means read a byte.
  // 'w' means read a word.
  // 'd' means read a dword.
  // 'B' means write a byte.
  // 'W' means write a word.
  // 'D' means write a dword.

  namespace util
  {
    class single_pin_debug_monitor_base : private util::noncopyable
    {
    public:
      template<typename addr_type, const addr_type addr_offset>
      void protocol_task();

      virtual ~single_pin_debug_monitor_base();

    protected:
      // Set up the driver buffer.
      static const std::uint_fast8_t driver_buffer_size = std::uint_fast8_t(8U);

      typedef std::array<std::uint8_t, driver_buffer_size> driver_buffer_type;

      typedef enum enum_driver_transmit_state_type
      {
        recieve_start_bit,
        recieve_start_bit_validation,
        recieve_data_bits,
        recieve_stop_bit,
        recieve_pause_for_next_byte,
        send_start_bit,
        send_data_bits,
        send_stop_bit,
        send_pause_for_next_byte
      }
      driver_transmit_state_type;

      std::uint_fast8_t          driver_buffer_length;
      bool                       driver_is_in_send_mode;
      std::uint_fast8_t          driver_current_byte_value;
      std::uint_fast8_t          driver_received_nothing_counter;
      driver_transmit_state_type driver_transmit_state;
      volatile std::uint8_t      driver_buffer[driver_buffer_size];

      single_pin_debug_monitor_base() : driver_buffer_length(0U),
                                        driver_is_in_send_mode(false),
                                        driver_current_byte_value(0U),
                                        driver_received_nothing_counter(0U),
                                        driver_transmit_state(recieve_start_bit)
      {
        std::fill(driver_buffer, driver_buffer + driver_buffer_size, UINT8_C(0));

        driver_flush_buffer();
      }

      void driver_send_buffer()
      {
        driver_is_in_send_mode    = true;
        driver_transmit_state     = send_start_bit;
        driver_current_byte_value = std::uint_fast8_t(0U);
      }

      void driver_flush_buffer()
      {
        driver_buffer_length  = std::uint_fast8_t(0U);
        driver_transmit_state = recieve_start_bit;
        std::fill(std::begin(driver_buffer), std::end(driver_buffer), driver_buffer_type::value_type(0U));
      }
    };

  }

  template<typename addr_type, const addr_type addr_offset>
  void util::single_pin_debug_monitor_base::protocol_task()
  {
    // This protocol task embodies the "bwd" protocol.

    if(driver_is_in_send_mode)
    {
      return;
    }

    std::uint_fast8_t data_elements;
    std::uint_fast8_t service_id;

    // Obtain the service ID for a read or write command,
    // and set the number of data elements in the command.

    switch(driver_buffer[0U])
    {
      case 0x62:  // 'b'
        service_id    = std::uint_fast8_t(1U);
        data_elements = std::uint_fast8_t(1U);
        break;

      case 0x77:  // 'w'
        service_id    = std::uint_fast8_t(1U);
        data_elements = std::uint_fast8_t(2U);
        break;

      case 0x64:  // 'd'
        service_id    = std::uint_fast8_t(1U);
        data_elements = std::uint_fast8_t(4U);
        break;

      case 0x42:  // 'B'
        service_id    = std::uint_fast8_t(2U);
        data_elements = std::uint_fast8_t(1U);
        break;

      case 0x57:  // 'W'
        service_id    = std::uint_fast8_t(2U);
        data_elements = std::uint_fast8_t(2U);
        break;

      case 0x44:  // 'D'
        service_id    = std::uint_fast8_t(2U);
        data_elements = std::uint_fast8_t(4U);
        break;

      default:    // undefined
        service_id    = std::uint_fast8_t(0U);
        data_elements = std::uint_fast8_t(0U);
        break;
    }

    // Create the total address using the address offset combined
    // with the address obtained from the communication buffer.
    // The total address is of type addr_type, which may have a
    // width that exceeds 16 bits based on the memory characteristics
    // of the target system.

    const std::uint_least16_t address_from_buffer =
      std::uint_least16_t(util::make_long(driver_buffer[1U], driver_buffer[2U]));

    const addr_type address = addr_type(addr_offset + address_from_buffer);

    // Evaluate the service ID and issue the read or write command.
    if(service_id == std::uint_fast8_t(1U))
    {
      if(driver_buffer_length == std::uint_fast8_t(3U))
      {
        std::fill(std::begin(driver_buffer), std::begin(driver_buffer) + 4U, std::uint8_t(0U));

        switch(data_elements)
        {
          case 1U:
          default:
            // Read a byte with the command 'b'.
            driver_buffer[0U] = *reinterpret_cast<volatile std::uint8_t*>(address);
            break;

          case 2U:
            {
              // Read a word with the command 'w'.
              const std::uint16_t value = *reinterpret_cast<volatile std::uint16_t*>(address);

              driver_buffer[1U] = util::hi_part<std::uint8_t>(value);
              driver_buffer[0U] = util::lo_part<std::uint8_t>(value);
            }
            break;

          case 4U:
            {
              // Read a dword with the command 'd'.
              const std::uint32_t value = *reinterpret_cast<volatile std::uint32_t*>(address);

              const std::uint16_t value_lo = util::lo_part<std::uint16_t>(value);
              const std::uint16_t value_hi = util::hi_part<std::uint16_t>(value);

              driver_buffer[3U] = util::hi_part<std::uint8_t>(value_hi);
              driver_buffer[2U] = util::lo_part<std::uint8_t>(value_hi);
              driver_buffer[1U] = util::hi_part<std::uint8_t>(value_lo);
              driver_buffer[0U] = util::lo_part<std::uint8_t>(value_lo);
            }
            break;
        }

        driver_buffer_length = data_elements;

        driver_send_buffer();
      }
    }
    else if(service_id == std::uint_fast8_t(2U))
    {
      if(driver_buffer_length == std::uint_fast8_t(data_elements + std::uint_fast8_t(3U)))
      {
        switch(data_elements)
        {
          case 1U:
          default:
            // Write a byte with the command 'B'.
            *reinterpret_cast<std::uint8_t*>(address) = driver_buffer[3U];
            break;

          case 2U:
            {
              // Write a word with the command 'W'.
              const std::uint16_t value =
                util::make_long(driver_buffer[3U], driver_buffer[4U]);

              *reinterpret_cast<volatile std::uint16_t*>(address) = value;
            }
            break;

          case 4U:
            {
              // Write a dword with the command 'D'.
              const std::uint16_t value_lo =
                util::make_long(driver_buffer[3U], driver_buffer[4U]);

              const std::uint16_t value_hi =
                util::make_long(driver_buffer[5U], driver_buffer[6U]);

              *reinterpret_cast<volatile std::uint32_t*>(address) = util::make_long(value_lo, value_hi);
            }
            break;
        }

        driver_flush_buffer();
      }
    }
  }

  util::single_pin_debug_monitor_base::~single_pin_debug_monitor_base() { }

#endif // _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_
