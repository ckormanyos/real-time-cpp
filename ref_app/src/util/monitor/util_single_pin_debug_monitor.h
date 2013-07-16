///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_SINGLE_PIN_DEBUG_MONITOR_2013_05_16_H_
  #define _UTIL_SINGLE_PIN_DEBUG_MONITOR_2013_05_16_H_

  #include <util/monitor/util_single_pin_debug_monitor_base.h>
  #include <util/utility/util_time.h>

  namespace util
  {
    template<typename port_pin_type>
    class single_pin_debug_monitor : public single_pin_debug_monitor_base
    {
    public:
      single_pin_debug_monitor();
      virtual ~single_pin_debug_monitor() { }
      void driver_task();

    private:
      // Set up the port driver timing.

      // The 250 baud corresponds to a bit-time of approximately 4ms
      // per bit. The polling period is 1ms, such that the driver
      // polls up to four times per bit.

      // * The single-bit timeout is set to 5% less than four poll times.
      // * The receiver automatically resets if it is idle for 12 bit times or more.
      static const std::uint_fast16_t bit_time_microseconds = (475U * 4U) / 2U;
      static const std::uint_fast8_t  receive_reset_limit   =   12U * 4U;

      typedef util::timer<std::uint_fast16_t> timer_type;

      timer_type        driver_wait;
      std::uint_fast8_t driver_current_bit_position;

      static void driver_init_port(const bool set_direction_to_output);
      static void port_pin_send(const bool set_value_to_high);
      static bool port_pin_receive();

      void driver_port_send();
      void driver_port_receive();
    };

    template<typename port_pin_type>
    single_pin_debug_monitor<port_pin_type>::single_pin_debug_monitor() : driver_wait(),
                                                                          driver_current_bit_position(0U)
    {
      port_pin_type::set_direction_input();
    }

    template<typename port_pin_type>
    void single_pin_debug_monitor<port_pin_type>::driver_task()
    {
      if(driver_is_in_send_mode)
      {
        driver_port_send();
      }
      else
      {
        // Clear the buffer if nothing has been received for a while.
        if(port_pin_receive())
        {
          ++driver_received_nothing_counter;

          if(driver_received_nothing_counter >= receive_reset_limit)
          {
            driver_flush_buffer();
            driver_received_nothing_counter = std::uint_fast8_t(0U);
          }
        }
        else
        {
          driver_received_nothing_counter = std::uint_fast8_t(0U);
        }

        driver_port_receive();
      }
    }

    template<typename port_pin_type>
    void single_pin_debug_monitor<port_pin_type>::driver_init_port(const bool set_direction_to_output)
    {
      (set_direction_to_output ? port_pin_type::set_direction_output()
                               : port_pin_type::set_direction_input());
    }

    template<typename port_pin_type>
    void single_pin_debug_monitor<port_pin_type>::port_pin_send(const bool set_value_to_high)
    {
      (set_value_to_high ? port_pin_type::set_pin_high() : port_pin_type::set_pin_low());
    }

    template<typename port_pin_type>
    bool single_pin_debug_monitor<port_pin_type>::port_pin_receive()
    {
      return port_pin_type::read_input_value();
    }

    template<typename port_pin_type>
    void single_pin_debug_monitor<port_pin_type>::driver_port_send()
    {
      // Send the buffer contents over the port pin.
      // Use the UART physical layer protocol.
      if(driver_current_byte_value < driver_buffer_length)
      {
        switch(driver_transmit_state)
        {
          case send_start_bit:
            driver_wait.start_relative(timer_type::microseconds(bit_time_microseconds));

            if(driver_current_byte_value == std::uint_fast8_t(0U))
            {
              driver_init_port(true);
            }

            port_pin_send(false);
            driver_transmit_state = send_data_bits;
            driver_current_bit_position = 0U;

          case send_data_bits:
            if(driver_wait.timeout())
            {
              driver_wait.start_relative(timer_type::microseconds(bit_time_microseconds));

              // Send a single data bit.
              const bool bit_is_high = (uint_fast8_t(std::uint_fast8_t(driver_buffer[driver_current_byte_value]) & std::uint_fast8_t(1U << driver_current_bit_position)) != std::uint_fast8_t(0U));

              port_pin_send(bit_is_high);

              ++driver_current_bit_position;

              if(driver_current_bit_position >= driver_buffer.size())
              {
                driver_transmit_state = send_stop_bit;
              }
            }
            break;

          case send_stop_bit:
            if(driver_wait.timeout())
            {
              driver_wait.start_relative(timer_type::microseconds(bit_time_microseconds));
              port_pin_send(true);
              driver_transmit_state = send_pause_for_next_byte;
            }
            break;

          case send_pause_for_next_byte:
            if(driver_wait.timeout())
            {
              ++driver_current_byte_value;

              driver_transmit_state = send_start_bit;

              if(driver_current_byte_value >= driver_buffer_length)
              {
                driver_is_in_send_mode = false;
                driver_flush_buffer();
                driver_init_port(driver_is_in_send_mode);
              }
            }
            break;

          default:
            break;
        }
      }
    }

    template<typename port_pin_type>
    void single_pin_debug_monitor<port_pin_type>::driver_port_receive()
    {
      // Read incoming data bytes on the port pin and store them in the buffer.
      // Use the UART physical layer protocol.
      if(driver_buffer_length < driver_buffer.size())
      {
        switch(driver_transmit_state)
        {
          case recieve_start_bit:
            if((!port_pin_receive()))
            {
              driver_transmit_state = recieve_start_bit_validation;
            }
            break;

          case recieve_start_bit_validation:
            if((!port_pin_receive()))
            {
              driver_wait.start_relative(timer_type::microseconds(bit_time_microseconds));
              driver_current_bit_position = std::uint_fast8_t(0U);
              driver_current_byte_value   = std::uint_fast8_t(0U);
              driver_transmit_state       = recieve_data_bits;
            }
            else
            {
              // If the start bit can not be validated, then flush
              // the buffer and thereby revert to the receive state.
              driver_flush_buffer();
            }
            break;

          case recieve_data_bits:
            if(driver_wait.timeout())
            {
              driver_wait.start_relative(timer_type::microseconds(bit_time_microseconds));

              // Append the bit value to the current byte value.
              if(port_pin_receive())
              {
                driver_current_byte_value |= std::uint_fast8_t(std::uint_fast8_t(1U) << driver_current_bit_position);
              }

              ++driver_current_bit_position;

              if(driver_current_bit_position >= std::uint_fast8_t(8U))
              {
                driver_transmit_state = recieve_stop_bit;
              }
            }
            break;

          case recieve_stop_bit:
            if(driver_wait.timeout())
            {
              if(port_pin_receive())
              {
                driver_buffer[driver_buffer_length] = std::uint8_t(driver_current_byte_value);

                ++driver_buffer_length;
              }

              driver_transmit_state = recieve_pause_for_next_byte;
            }
            break;

          case recieve_pause_for_next_byte:
            driver_transmit_state = recieve_start_bit;
            break;

          default:
            break;
        }
      }
    }
  }

#endif // _UTIL_SINGLE_PIN_DEBUG_MONITOR_2013_05_16_H_
