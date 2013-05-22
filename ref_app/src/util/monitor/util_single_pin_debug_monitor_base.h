#ifndef _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_
  #define _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_

  #include <cstdint>
  #include <algorithm>
  #include <array>
  #include <mcal_port.h>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_two_part_data_manipulation.h>

  namespace util
  {
    class single_pin_debug_monitor_base : private util::noncopyable
    {
    public:
      virtual ~single_pin_debug_monitor_base() { }

      template<typename addr_type, const addr_type addr_offset>
      void protocol_task();

    protected:
      static const std::uint_least8_t driver_buffer_length      = 8U;
      static const std::uint_least8_t driver_delay_milliseconds = 4U;
      static const std::uint_least8_t driver_receive_reset      = driver_delay_milliseconds * 12U;

      typedef std::array<std::uint8_t, driver_buffer_length> driver_byte_buffer_type;

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

      driver_byte_buffer_type     driver_byte_buffer;
      std::uint_least8_t          driver_byte_buffer_length;
      bool                        driver_is_in_send_mode;
      std::uint_least8_t          driver_current_byte_value_or_position;
      std::uint_least8_t          driver_received_nothing_counter;
      driver_transmit_state_type  driver_transmit_state;

      single_pin_debug_monitor_base() : driver_byte_buffer(),
                                        driver_byte_buffer_length(0U),
                                        driver_is_in_send_mode(false),
                                        driver_current_byte_value_or_position(0U),
                                        driver_received_nothing_counter(0U),
                                        driver_transmit_state(recieve_start_bit)
      {
        driver_flush_buffer();
      }

      void driver_send_buffer()
      {
        driver_is_in_send_mode                = true;
        driver_transmit_state                 = send_start_bit;
        driver_current_byte_value_or_position = 0U;
      }

      void driver_flush_buffer()
      {
        driver_byte_buffer_length = 0U;
        driver_transmit_state     = recieve_start_bit;
        std::fill(driver_byte_buffer.begin(), driver_byte_buffer.end(), driver_byte_buffer_type::value_type(0U));
      }
    };

    template<typename addr_type, const addr_type addr_offset>
    void single_pin_debug_monitor_base::protocol_task()
    {
      if(driver_is_in_send_mode)
      {
        return;
      }

      // Obtain the service ID for a read or write command,
      // and set the number of data elements in the command.

      // Note: These variables are shielded from aggressive optimization.
      volatile std::uint_least8_t data_elements;
      volatile std::uint_least8_t service_id;

      switch(driver_byte_buffer[0U])
      {
        default:
        case 0x62:  // 'b'
          service_id    = 1U;
          data_elements = 1U;
          break;

        case 0x77:  // 'w'
          service_id    = 1U;
          data_elements = 2U;
          break;

        case 0x64:  // 'd'
          service_id    = 1U;
          data_elements = 4U;
          break;

        case 0x42:  // 'B'
          service_id    = 2U;
          data_elements = 1U;
          break;

        case 0x57:  // 'W'
          service_id    = 2U;
          data_elements = 2U;
          break;

        case 0x44:  // 'D'
          service_id    = 2U;
          data_elements = 4U;
          break;
      }

      // Create the total address using the offset.
      // The width of this address might exceed 16 bits.
      const addr_type address = 
         addr_offset
       + addr_type(util::make_long<std::uint8_t, std::uint16_t>(driver_byte_buffer[1U],
                                                                driver_byte_buffer[2U]));

      // Evaluate the service ID and issue the read or write command.
      if(service_id == 1U)
      {
        if(driver_byte_buffer_length == 3U)
        {
          switch(data_elements)
          {
            case 1U:
            default:
              {
                // Read a byte with the command 'b'.
                driver_byte_buffer[0U] = *reinterpret_cast<volatile std::uint8_t*>(address);
              }
              break;

            case 2U:
              {
                // Read a word with the command 'w'.
                const std::uint16_t value = *reinterpret_cast<volatile std::uint16_t*>(address);

                driver_byte_buffer[1U] = util::hi_part<std::uint8_t, std::uint16_t>(value);
                driver_byte_buffer[0U] = util::lo_part<std::uint8_t, std::uint16_t>(value);
              }
              break;

            case 4U:
              {
                // Read a dword with the command 'd'.
                const std::uint32_t value = *reinterpret_cast<volatile std::uint32_t*>(address);

                const std::uint16_t value_lo = util::lo_part<std::uint16_t, std::uint32_t>(value);
                const std::uint16_t value_hi = util::hi_part<std::uint16_t, std::uint32_t>(value);

                driver_byte_buffer[3U] = util::hi_part<std::uint8_t, std::uint16_t>(value_hi);
                driver_byte_buffer[2U] = util::lo_part<std::uint8_t, std::uint16_t>(value_hi);
                driver_byte_buffer[1U] = util::hi_part<std::uint8_t, std::uint16_t>(value_lo);
                driver_byte_buffer[0U] = util::lo_part<std::uint8_t, std::uint16_t>(value_lo);
              }
              break;
          }

          driver_byte_buffer_length = data_elements;

          driver_send_buffer();
        }
      }
      else if(service_id == 2U)
      {
        if(driver_byte_buffer_length == (data_elements + 3U))
        {
          switch(data_elements)
          {
            case 1U:
            default:
              {
                // Write a byte with the command 'B'.
                *reinterpret_cast<std::uint8_t*>(address) = driver_byte_buffer[3U];
              }
              break;

            case 2U:
              {
                // Write a word with the command 'W'.
                const std::uint16_t value =
                  util::make_long<std::uint8_t, std::uint16_t>(static_cast<std::uint8_t>(driver_byte_buffer[3U]),
                                                                static_cast<std::uint8_t>(driver_byte_buffer[4U]));

                *reinterpret_cast<volatile std::uint16_t*>(address) = value;
              }
              break;

            case 4U:
              {
                // Write a dword with the command 'D'.
                const std::uint16_t value_lo =
                  util::make_long<std::uint8_t, std::uint16_t>(static_cast<std::uint8_t>(driver_byte_buffer[3U]),
                                                                static_cast<std::uint8_t>(driver_byte_buffer[4U]));

                const std::uint16_t value_hi =
                  util::make_long<std::uint8_t, std::uint16_t>(static_cast<std::uint8_t>(driver_byte_buffer[5U]),
                                                                static_cast<std::uint8_t>(driver_byte_buffer[6U]));

                *reinterpret_cast<volatile std::uint32_t*>(address) = util::make_long<std::uint16_t, std::uint32_t>(value_lo, value_hi);
              }
              break;
          }

          driver_flush_buffer();
        }
      }
    }
  }

#endif // _UTIL_SINGLE_PIN_DEBUG_MONITOR_BASE_2013_05_16_H_
