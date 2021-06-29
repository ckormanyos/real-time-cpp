///////////////////////////////////////////////////////////////////////////////
// \author (c) Marco Paland (info@paland.com)
//             2014-2016, PALANDesign Hannover, Germany
//
// \license The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//
// \brief Single Wire Debug Monitor
// This class is the single wire debug monitor, which allows easy inspecting and
// manipulating (setting) memory / variable data over a single wire/pin in embedded systems.
// NO DEPENDENCIES! NO UART! NO REQUIREMENTS! Just a 1 ms periodic tick is needed. That's all.
//
// SWDM uses a simple request/response protocol where the tester/PC is always the
// master generating the request and the device/board is the slave sending the response.
// The class below implements the SWDM slave.
//
// SWDM uses a service tick of 1ms, one bit is oversampled 4 times, which results
// in a baudrate of 250 bit/sec, every byte has a low start bit, a high stop bit and
// 8 data bits (LSB first). So a normal UART with 250 baud 8N1 can be used on the PC master side
// for transmission / reception.
// The line is used in half duplex bidirectional mode. It is high for idle / recessive levels
// and low when active / dominant.
// Use a resistor pulled-up open collector pin on the board site or set the pin as input
// on a high level in your custom set_line() function.
//
// Protocol:
//
// request: | 0x55 | mode | address | data | crc |
//
// 0x55 (1 byte) :
// Request sync byte
//
// mode (1 byte) :
// bit 0-3 : data length, 0: 1 byte, 2: 3 bytes ... 15: 16 bytes
// bit 4-5 : addr length, 0: 2 byte, 1: 3 byte, 2: 4 byte, 3: 8 byte
// bit 6   : 0: byte access, 1: type access valid for uint8, uint16, uint32 and uint64 data length
// bit 7   : 0: read data command, 1: write data command
//
// address (2 - 8 bytes) :
// Big-endian order, MSB - the most significant address byte is sent first
//
// data (0 - 16 bytes) :
// On read command, no data byte is transmitted, data field is skipped
// Byte access: The byte of the specified address is send first, ascending address order byte by byte
// Type access: MSB first, valid are 1,2,4 and 8 data bytes, the most significant data byte is sent first
//
// crc (1 byte) :
// One byte CRC, using CRC-8 (ITU-T), x^8 + x^2 + x + 1 polynomial
// CRC is build over mode, address and data bytes
//
//
// response: | 0xAA | data | crc |
//
// 0xAA (1 byte) :
// Response sync byte
//
// data (0 - 16 bytes)
// Requested data bytes of read command
// On write command no data is sent, the answer is | 0xAA | 0x00 |
// Byte access: The byte of the specified address is send first, ascending address order byte by byte
// Type access: MSB first, valid are 1, 2, 4 and 8 bytes, the most significant data byte is sent first
// 
// crc (1 byte) :
// One byte CRC, using CRC-8 (ITU-T), x^8 + x^2 + x + 1 polynomial
// CRC is built over data bytes, in case of a write command, crc is 0x00
//
//
// Usage:
//
// #include "swdm.h"
//
// Define (implement) the two low level line/pin access routines in your system
// or derive your own my_swdm class from swdm and define your access functions there.
//
// bool swdm::get_line() const
// {
//   return the value of the according swdm interface line/pin
// }
//
// void swdm::set_line(bool value) const
// {
//   set the state of the according swdm line/pin to value (true = high/idle, false = low)
//   if you don't use an open collector driver, you MUST config the pin as input for high/idle levels
//   and before setting the line to false/low it must be configured as an output.
// }
//
// Create a singleton instance of swdm:
//
// static swdm& get_swdm()
// {
//   static swdm _swdm;
//   return _swdm;
// }
// 
// And call the swdm service routine with a rate of 1000 Hz:
//
// void system_tick_1ms()
// {
//   get_swdm().service();
// }
//
//
// \version
// 2014-09-17  0.10  Initial version, ideas
// 2014-09-23  0.80  Alpha version
// 2015-02-05  0.90  Beta version, code clean up
// 2015-02-25  0.91  Minor bug fixes, cleanup, more docu
// 2016-04-13  0.92  Bug fixes and tests by B. Hempelmann and C. Kormanyos
// 2016-04-17  1.00  Minor cleanups, first released version
//
///////////////////////////////////////////////////////////////////////////////

#ifndef UTIL_SWDM_2016_04_11_H_
#define UTIL_SWDM_2016_04_11_H_

#include <cstdint>
#include <mcal_debug_monitor.h>
#include <util/utility/util_noncopyable.h>

// Defines the oversampling rate
// The effective baud rate is the service_tick_rate / SWD_OVERSAMPLING_COUNT
// For a service_tick_rate of 1 ms, the baud rate is 250 for 4 times oversampling
#define SWDM_SAMPLE_PERIOD      UINT8_C(4)

// Defines the position where the bit is detected as a constant valid bit.
// Should be at 50 to 75% of the SAMPLE period, 0 is the first sample position
#define SWDM_SAMPLE_VALID_POS   UINT8_C(2)

// Defines the number of consecutive high samples to detect a line idle condition
#define SWDM_SAMPLE_IDLE_COUNT  UINT8_C(40)

// Define this switch for 64 bit address support. If undefined, up to 32 bit addresses are supported
// #define SWDM_64_BIT_ADDRESS_SUPPORT


namespace util {

class swdm : private util::noncopyable
{
public:
  // default ctor
  swdm() : uart_state_             (rx_start_bit),
           prot_state_             (rx_sync),
           bit_detect_last_state_  (true),
           bit_detect_sample_count_(UINT8_C(0)),
           bit_detect_idle_count_  (UINT8_C(0))
  {
    // set pin to idle / recessive value
    set_line(true);
  }

  // Service routine, MUST be called periodically with 1000 Hz (1 ms)
  void service()
  {
    if(   (uart_state_ == tx_data_bits)
       || (uart_state_ == tx_start_bit)
       || (uart_state_ == tx_stop_bit))
    {
      // transmission
      if(bit_detect_sample_count_ == UINT8_C(0))
      {
        // bit period done
        uart(true);
      }
    }
    else
    {
      // reception
      bool line = get_line();

      // sync is done on every level change
      if(line != bit_detect_last_state_)
      {
        // line level has changed, new bit cell started
        bit_detect_last_state_   = line;
        bit_detect_sample_count_ = UINT8_C(0);
      }
      else
      {
        // no level change
        if((bit_detect_sample_count_ == SWDM_SAMPLE_VALID_POS) &&
           (bit_detect_idle_count_   <  SWDM_SAMPLE_IDLE_COUNT))
        {
          // valid bit detected
          uart(line);
        }

        // idle detection
        bit_detect_idle_count_ = (line ? (bit_detect_idle_count_ + UINT8_C(1)) : UINT8_C(0));

        if(bit_detect_idle_count_ >= SWDM_SAMPLE_IDLE_COUNT)
        {
          // line is idle, reset uart
          bit_detect_idle_count_ = SWDM_SAMPLE_IDLE_COUNT;
          uart_state_ = rx_start_bit;
        }
      }
    }

    if(++bit_detect_sample_count_ == SWDM_SAMPLE_PERIOD)
    {
      bit_detect_sample_count_ = UINT8_C(0);
    }
  }

protected:
  // Line (pin) access function to get the actual line / pin state
  // This function MUST be defined somewhere in your project or in your derived class
  // \return The actual state of the swdm line / pin: true = high (idle/recessive), false = low (active/dominant)
  virtual bool get_line() const
  {
    return mcal::debug::debug_monitor_port_type::read_input_value();
  }


  // Line (pin) access function to set the actual line / pin state
  // This function MUST be defined somewhere in your project
  // \param value The new state of the swdm line / pin: true = high (idle/recessive), false = low (active/dominant)
  virtual void set_line(const bool value) const
  {
    if(value)
    {
      mcal::debug::debug_monitor_port_type::set_direction_input();
    }
    else
    {
      mcal::debug::debug_monitor_port_type::set_direction_output();
      mcal::debug::debug_monitor_port_type::set_pin_low();
    }
  }

private:
  // Software UART, called by the service routine, when a valid bit is received or when a bit should be transmitted
  // \param bit The value of the received bit
  void uart(const bool bit)
  {
    switch(uart_state_)
    {
      case rx_start_bit:
        if((!bit))
        {
          // start bit detected
          uart_data_bit_count_ = UINT8_C(0);
          uart_state_ = rx_data_bits;
        }
        break;

      case rx_data_bits:
        // LSB is transmitted first
        uart_buffer_ = static_cast<std::uint8_t>(std::uint_fast8_t(uart_buffer_ >> UINT8_C(1)) | std::uint_fast8_t(bit ? UINT8_C(0x80) : UINT8_C(0x00)));

        if(++uart_data_bit_count_ >= UINT8_C(8))
        {
          uart_state_ = rx_stop_bit;
        }

        break;

      case rx_stop_bit:
        uart_state_ = rx_start_bit;

        if(bit)
        {
          // valid byte received, if no stop bit is detected, it's a framing error, discard data
          uart_rx_full(uart_buffer_);
        }
        else
        {
          // framing error, discard data
          prot_state_ = rx_sync;        // reset the protocol state, because a byte error decays the whole command
        }

        break;

      case tx_start_bit:
        // send start bit
        set_line(false);

        uart_data_bit_count_ = UINT8_C(0);
        uart_state_ = tx_data_bits;

        break;

      case tx_data_bits:
        // send data bits, LSB is first
        set_line((uart_buffer_ & UINT8_C(0x01)) != UINT8_C(0));
        uart_buffer_ >>= UINT8_C(1);

        if(++uart_data_bit_count_ >= UINT8_C(8))
        {
          uart_state_ = tx_stop_bit;
        }

        break;

      case tx_stop_bit:
        // send stop bit
        set_line(true);

        uart_state_ = rx_start_bit;

        // byte transmission complete, inform protocol (transmitter empty)
        uart_tx_empty();

        break;

      default:
        break;
    }
  }


  // UART transmit function
  // \param data The character to send
  void uart_send(const std::uint_fast8_t data)
  {
    uart_buffer_ = std::uint8_t(data);
    uart_state_  = tx_start_bit;
  }

  // This function is called by the (software) UART when the receiver is full
  // \param data The received character
  void uart_rx_full(const std::uint_fast8_t data)
  {
    switch(prot_state_)
    {
      case rx_sync:
        if(data == request_sync_field)
        {
          prot_state_ = rx_mode;
        }

        break;

      case rx_mode:
        prot_mode_  = data;
        prot_idx_   = UINT8_C(0);
        prot_crc_   = UINT8_C(0);
        prot_state_ = rx_addr;

        crc8(data);

        break;

      case rx_addr:
      {
        prot_addr_[prot_idx_++] = data;
        crc8(data);

        const std::uint_fast8_t addr_width = (prot_mode_ & UINT8_C(0x30)) >> UINT8_C(4);

        if(   ((addr_width == UINT8_C(0)) && (prot_idx_ == UINT8_C(2)))  // 16 bit address
           || ((addr_width == UINT8_C(1)) && (prot_idx_ == UINT8_C(3)))  // 24 bit address
           || ((addr_width == UINT8_C(2)) && (prot_idx_ == UINT8_C(4)))  // 32 bit address
          #if defined(SWDM_64_BIT_ADDRESS_SUPPORT)
           || ((addr_width == UINT8_C(3)) && (prot_idx_ == UINT8_C(8)))  // 64 bit address
          #endif
          )
        {
          prot_idx_   = UINT8_C(0);
          prot_state_ = (((prot_mode_ & UINT8_C(0x80)) != UINT8_C(0))? rx_data : rx_crc);
        }
 
        break;
      }
 
      case rx_data:
        prot_data_[prot_idx_++] = data;
        crc8(data);

        if(prot_idx_ > (prot_mode_ & UINT8_C(0x0F)))
        {
          prot_state_ = rx_crc;
        }

        break;

      case rx_crc:
        if(data == prot_crc_)
        {
          // CRC correct - execute request
          request();

          // send response
          prot_state_ = tx_sync;

          // start the transmission
          uart_tx_empty();
        }
        else
        {
          // CRC error - discard command, wait for next rx sync byte
          prot_state_ = rx_sync;
        }

        break;

      default:
        prot_state_ = rx_sync;
        break;

      case tx_sync:
      case tx_data:
      case tx_crc:
        break;
    }
  }

  // This function is called by the (software) UART when the transmitter is empty
  void uart_tx_empty()
  {
    switch(prot_state_)
    {
      case tx_sync:
        prot_idx_   = UINT8_C(0);
        prot_crc_   = UINT8_C(0);
        prot_state_ = (((prot_mode_ & UINT8_C(0x80)) != UINT8_C(0)) ? tx_crc : tx_data);  // skip data on write command

        uart_send(response_sync_field);

        break;

      case tx_data:
        uart_send(prot_data_[prot_idx_]);
        crc8(prot_data_[prot_idx_]);

        if(++prot_idx_ >= ((prot_mode_ & UINT8_C(0x0F)) + UINT8_C(1)))
        {
          prot_state_ = tx_crc;
        }

        break;

      case tx_crc:
        uart_send(prot_crc_);
        prot_state_ = rx_sync;

        break;

      default:
        prot_state_ = rx_sync;
        break;

      case rx_sync:
      case rx_mode:
      case rx_addr:
      case rx_data:
      case rx_crc:
        break;
    }
  }

  // Process and execute the received request
  void request()
  {
    // get address width
    std::uint_fast8_t addr_width;

    switch((prot_mode_ & UINT32_C(0x30)) >> UINT8_C(4))
    {
      case UINT8_C(0): addr_width = UINT8_C(2); break;   // 16 bit address
      case UINT8_C(1): addr_width = UINT8_C(3); break;   // 24 bit address

      default        :
      case UINT8_C(2): addr_width = UINT8_C(4); break;   // 32 bit address

      #if defined(SWDM_64_BIT_ADDRESS_SUPPORT)
      case UINT8_C(3): addr_width = UINT8_C(8); break;  // 64 bit address
      #endif
    }

    #if defined(SWDM_64_BIT_ADDRESS_SUPPORT)
      std::uint64_t addr = UINT64_C(0);
    #else
      std::uint32_t addr = UINT32_C(0);
    #endif

    // assemble address
    for(std::uint_fast8_t i = UINT8_C(0); i < addr_width; ++i)
    {
      addr <<= UINT8_C(8);
      addr |= prot_addr_[i];
    }

    // data length
    const std::uint_fast8_t data_length = (prot_mode_ & UINT8_C(0x0F)) + UINT8_C(1);

    if((prot_mode_ & UINT8_C(0x80)) != UINT8_C(0))
    {
      // write command
      if(prot_mode_ & UINT8_C(0x40))
      {
        // write type access
        switch(data_length)
        {
          case 1U:
            *reinterpret_cast<volatile std::uint8_t*>(addr) = prot_data_[0U];
            break;

          case 2U:
          {
            const std::uint16_t value =
                (static_cast<std::uint16_t>(prot_data_[0U]) << UINT8_C(8))
              | (static_cast<std::uint16_t>(prot_data_[1U]));

            *reinterpret_cast<volatile std::uint16_t*>(addr) = value;

            break;
          }

          case 4U:
          {
            const std::uint32_t value =
                (static_cast<std::uint32_t>(prot_data_[0U]) << UINT8_C(24))
              | (static_cast<std::uint32_t>(prot_data_[1U]) << UINT8_C(16))
              | (static_cast<std::uint32_t>(prot_data_[2U]) << UINT8_C( 8))
              | (static_cast<std::uint32_t>(prot_data_[3U]));

            *reinterpret_cast<volatile std::uint32_t*>(addr) = value;

            break;
          }

          case 8U:
          {
            const std::uint64_t value =
                (static_cast<std::uint64_t>(prot_data_[0U]) << UINT8_C(56))
              | (static_cast<std::uint64_t>(prot_data_[1U]) << UINT8_C(48))
              | (static_cast<std::uint64_t>(prot_data_[2U]) << UINT8_C(40))
              | (static_cast<std::uint64_t>(prot_data_[3U]) << UINT8_C(32))
              | (static_cast<std::uint64_t>(prot_data_[4U]) << UINT8_C(24))
              | (static_cast<std::uint64_t>(prot_data_[5U]) << UINT8_C(16))
              | (static_cast<std::uint64_t>(prot_data_[6U]) << UINT8_C( 8))
              | (static_cast<std::uint64_t>(prot_data_[7U]));

            *reinterpret_cast<volatile std::uint64_t*>(addr) = value;

            break;
          }

          default:
            // invalid data type, use byte access
            for(std::uint_fast8_t i = UINT8_C(0); i < data_length; i++)
            {
              *reinterpret_cast<volatile std::uint8_t*>(addr++) = prot_data_[i];
            }

            break;
        }
      }
      else
      {
        // write byte access
        for(std::uint_fast8_t i = UINT8_C(0); i < data_length; i++)
        {
          *reinterpret_cast<volatile std::uint8_t*>(addr++) = prot_data_[i];
        }
      }
    }
    else
    {
      // read command
      if((prot_mode_ & UINT8_C(0x40)) != UINT8_C(0))
      {
        // read type access
        switch(data_length)
        {
          case UINT8_C(1):
            prot_data_[0U] = *reinterpret_cast<volatile std::uint8_t*>(addr);
            break;

          case UINT8_C(2):
          {
            std::uint16_t value = *reinterpret_cast<volatile std::uint16_t*>(addr);

            for(std::int_fast8_t tries = UINT8_C(4); --tries && (value != *reinterpret_cast<volatile std::uint16_t*>(addr)); value = *reinterpret_cast<volatile std::uint16_t*>(addr))
            {
              ;
            }

            prot_data_[0U] = byte_part<std::uint16_t, 1U>(value);     // MSB
            prot_data_[1U] = byte_part<std::uint16_t, 0U>(value);     // LSB

            break;
          }

          case UINT8_C(4):
          {
            std::uint32_t value = *reinterpret_cast<volatile std::uint32_t*>(addr);

            for(std::int_fast8_t tries = UINT8_C(4); --tries && (value != *reinterpret_cast<volatile std::uint32_t*>(addr)); value = *reinterpret_cast<volatile std::uint32_t*>(addr))
            {
              ;
            }

            prot_data_[0U] = byte_part<std::uint32_t, 3U>(value);     // MSB
            prot_data_[1U] = byte_part<std::uint32_t, 2U>(value);
            prot_data_[2U] = byte_part<std::uint32_t, 1U>(value);
            prot_data_[3U] = byte_part<std::uint32_t, 0U>(value);     // LSB

            break;
          }

          case UINT8_C(8):
          {
            std::uint64_t value = *reinterpret_cast<volatile std::uint64_t*>(addr);

            for(std::int_fast8_t tries = UINT8_C(4); --tries && (value != *reinterpret_cast<volatile std::uint64_t*>(addr)); value = *reinterpret_cast<volatile std::uint64_t*>(addr))
            {
              ;
            }

            prot_data_[0U] = byte_part<std::uint64_t, 7U>(value);     // MSB
            prot_data_[1U] = byte_part<std::uint64_t, 6U>(value);
            prot_data_[2U] = byte_part<std::uint64_t, 5U>(value);
            prot_data_[3U] = byte_part<std::uint64_t, 4U>(value);
            prot_data_[4U] = byte_part<std::uint64_t, 3U>(value);
            prot_data_[5U] = byte_part<std::uint64_t, 2U>(value);
            prot_data_[6U] = byte_part<std::uint64_t, 1U>(value);
            prot_data_[7U] = byte_part<std::uint64_t, 0U>(value);     // LSB

            break;
          }

          default:
            // invalid data type, use byte access
            for(std::uint_fast8_t i = UINT8_C(0); i < data_length; i++)
            {
              prot_data_[i] = *reinterpret_cast<volatile std::uint8_t*>(addr++);
            }

            break;
        }
      }
      else
      {
        // read byte access
        for(std::uint_fast8_t i = UINT8_C(0); i < data_length; i++)
        {
          prot_data_[i] = *reinterpret_cast<volatile std::uint8_t*>(addr++);
        }
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////
  // H E L P E R   F U N C T I O N S

  // CRC-8 algorithm, using x^8 + x^2 + x + 1 polynomial
  // Process data, CRC result is in prot_crc_
  // We use a shifter here instead of a table lookup to save code size, speed
  // is not so important at the swdm baudrate of 250 baud.
  // \param data Data to process
  void crc8(std::uint_fast8_t data)
  {
    for(std::uint_fast8_t i = UINT8_C(8); i; i--)
    {
      const std::uint_fast8_t sum = (prot_crc_ ^ data) & UINT8_C(0x01);

      prot_crc_ >>= UINT8_C(1);

      if(sum != UINT8_C(0))
      {
        prot_crc_ ^= UINT8_C(0x8C);
      }

      data >>= UINT8_C(1);
    }
  }

  // Return the according byte of the given position
  // \param Long Type of the value
  // \param Position Byte position to return, 0 is LSB
  // \param value The Long value
  // \return The byte of the Long value at the given position
  template<typename LongType,
           const std::uint_fast8_t Position>
  std::uint8_t byte_part(const LongType& value) const
  {
    return static_cast<std::uint8_t>(value >> (Position * UINT8_C(8)));
  }

private:
  static const std::uint_fast8_t request_sync_field  = UINT8_C(0x55);    // Request sync field
  static const std::uint_fast8_t response_sync_field = UINT8_C(0xAA);    // Response sync field

  typedef enum enum_state_type
  {
    rx_start_bit,
    rx_data_bits,
    rx_stop_bit,
    tx_start_bit,
    tx_data_bits,
    tx_stop_bit
  }
  state_type;

  typedef enum enum_prot_state_type
  {
    rx_sync,
    rx_mode,
    rx_addr,
    rx_data,
    rx_crc,
    tx_sync,
    tx_data,
    tx_crc
  }
  prot_state_type;

  state_type         uart_state_;
  std::uint_fast8_t  uart_buffer_;
  std::uint_fast8_t  uart_data_bit_count_;

  prot_state_type    prot_state_;
  std::uint_fast8_t  prot_mode_;
  std::uint8_t       prot_addr_[ 8U];
  std::uint8_t       prot_data_[16U];
  std::uint_fast8_t  prot_crc_;
  std::uint_fast8_t  prot_idx_;

  bool               bit_detect_last_state_;
  std::uint_fast8_t  bit_detect_sample_count_;
  std::uint_fast8_t  bit_detect_idle_count_;
};

} // namespace util

#endif // UTIL_SWDM_2016_04_11_H_
