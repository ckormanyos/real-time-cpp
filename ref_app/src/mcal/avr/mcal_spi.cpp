///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_port.h>
#include <mcal_spi.h>
#include <mcal_reg_access.h>

void mcal::spi::init(const mcal::spi::config_type*)
{
}

mcal::spi::spi_communication mcal::spi::the_spi;

namespace
{
  typedef mcal::port::port_pin<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::portd,
                               0U> portd0_type;

  typedef mcal::port::port_pin<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::portd,
                               1U> portd1_type;

  void enable_rx_tx_interrupt()
  {
    // Enable the spi end-of-transmission interrupt
    // by setting the spie bit in the spcr register.
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::spcr,
                      7U>::bit_set();
  }

  void disable_rx_tx_interrupt()
  {
    // Disable the spi end-of-transmission interrupt
    // by clearing the spie bit in the spcr register.
    mcal::reg::access<std::uint8_t,
                      std::uint8_t,
                      mcal::reg::spcr,
                      7U>::bit_clr();
  }
}

mcal::spi::spi_communication::spi_communication() : send_is_active(false),
                                                    channel(0U)
{
  // Set the special port pins ss, mosi and sck to output.
  // Do this even though the ss pin will not be used.
  constexpr std::uint8_t pdir_mask =   mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval5;

  mcal::reg::access<std::uint8_t,
                    std::uint8_t,
                    mcal::reg::ddrb,
                    pdir_mask>::reg_or();

  // Enable spi as master mode, clock idle to high, etc.
  // Set the spi clock to f_osc/64 = (1/4)MHz.
  constexpr std::uint8_t spcr_mask =   mcal::reg::bval1
                                     | mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval4
                                     | mcal::reg::bval6;

  mcal::reg::access<std::uint8_t,
                    std::uint8_t,
                    mcal::reg::spcr,
                    spcr_mask>::reg_set();

  // Set the chip-select-not ports to output high.
  portd0_type::set_pin_high();
  portd0_type::set_direction_output();

  portd1_type::set_pin_high();
  portd1_type::set_direction_output();
}

mcal::spi::spi_communication::~spi_communication()
{
}

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{
  mcal::irq::disable_all();

  // If the spi is idle, begin transmission.
  if(send_is_active == false)
  {
    // Set the send-active flag.
    send_is_active = true;

    // Set the chip-select-not for the appropriate channel to low.
    if(channel == static_cast<std::uint8_t>(1U))
    {
      portd1_type::set_pin_low();
    }
    else
    {
      portd0_type::set_pin_low();
    }

    // Send the first byte over spi.
    mcal::reg::dynamic_access<std::uint8_t,
                              std::uint8_t>::reg_set(mcal::reg::spdr, byte_to_send);

    // Enable the spi rx/tx interrupt.
    enable_rx_tx_interrupt();

    mcal::irq::enable_all();
  }
  else
  {
    // A transmission is already in progress.
    // Pack the next byte-to-send into the send-buffer.
    send_buffer.in(byte_to_send);

    mcal::irq::enable_all();
  }

  return true;
}

bool mcal::spi::spi_communication::send(const buffer_type& data_to_send)
{
  // TBD: Replace this temporary copy of the data-to-send-buffer
  // with iterators as soon as the circular_buffer class gets
  // proper iterator support.
  buffer_type tmp(data_to_send);

  // Sequentially send all the bytes in the command.
  for(size_type count = 0U; count < data_to_send.size(); ++count)
  {
    static_cast<void>(send(tmp.out()));
  }

  return true;
}

bool mcal::spi::spi_communication::recv(std::uint8_t& byte_to_recv)
{
  disable_rx_tx_interrupt();

  byte_to_recv = recv_buffer.out();

  enable_rx_tx_interrupt();

  return true;
}

bool mcal::spi::spi_communication::recv(buffer_type& data_to_recv)
{
  const size_type count_to_recv = (std::min)(data_to_recv.size(), recv_ready());

  for(size_type count = 0U; count < count_to_recv; ++count)
  {
    std::uint8_t byte_to_recv;

    recv(byte_to_recv);

    data_to_recv.in(byte_to_recv);
  }

  return true;
}

mcal::spi::spi_communication::size_type mcal::spi::spi_communication::recv_ready() const
{
  disable_rx_tx_interrupt();

  // Get the count of bytes in the receive buffer.
  const size_type count = recv_buffer.size();

  enable_rx_tx_interrupt();

  return count;
}

bool mcal::spi::spi_communication::idle() const
{
  disable_rx_tx_interrupt();

  const bool is_active = send_is_active;

  enable_rx_tx_interrupt();

  return (is_active == false);
}

bool mcal::spi::spi_communication::select_channel(const std::uint8_t ch)
{
  // Support for two channels 0 and 1.
  if(ch <= static_cast<std::uint8_t>(2U))
  {
    channel = ch;

    return true;
  }
  else
  {
    return false;
  }
}

void __vector_17()
{
  // The spi interrupt is on end-of-transmission.

  // Receive the byte from the previous transmission.
  const std::uint8_t byte_to_recv = mcal::reg::access<std::uint8_t,
                                                      std::uint8_t,
                                                      mcal::reg::spdr>::reg_get();

  mcal::spi::the_spi.recv_buffer.in(byte_to_recv);

  const bool send_buffer_is_empty = mcal::spi::the_spi.send_buffer.empty();

  if(send_buffer_is_empty)
  {
    // The send-buffer is empty and reception from
    // the previous (final) transmission is done.
    // Deactivate the send-active flag.
    mcal::spi::the_spi.send_is_active = false;

    // Reset the chip-select-not on the channel to high.
    if(mcal::spi::the_spi.channel == static_cast<std::uint8_t>(1U))
    {
      portd1_type::set_pin_high();
    }
    else
    {
      portd0_type::set_pin_high();
    }

    // Disable the spi rx/tx interrupt.
    disable_rx_tx_interrupt();
  }
  else
  {
    // Send the next byte if there is at least one in the send queue.
    const std::uint8_t byte_to_send = mcal::spi::the_spi.send_buffer.out();

    mcal::reg::dynamic_access<std::uint8_t,
                              std::uint8_t>::reg_set(mcal::reg::spdr, byte_to_send);
  }
}
