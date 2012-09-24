#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_port.h>
#include <mcal_spi.h>
#include <mcal_reg_access.h>

//mcal::spi::spi_communication mcal::spi::the_spi;

namespace
{
  void enable_rx_tx_interrupt()
  {
    // Enable the SPI(TM) end-of-transmission interrupt
    // by setting the spie bit in the spcr register.
    mcal::reg_access<std::uint8_t,
                     std::uint8_t,
                     mcal::reg::spcr,
                     7U>::bit_set();
  }

  void disable_rx_tx_interrupt()
  {
    // Disable the SPI(TM) end-of-transmission interrupt
    // by clearing the spie bit in the spcr register.
    mcal::reg_access<std::uint8_t,
                     std::uint8_t,
                     mcal::reg::spcr,
                     7U>::bit_clr();
  }
}

mcal::spi::spi_communication::spi_communication() : send_is_active(false),
                                                    send_buffer(),
                                                    recv_buffer(),
                                                    channel(0U)
{
  // Set the special port pins SS, MOSI and SCK to output.
  // (Even though the SS pin will not be used.)
  constexpr std::uint8_t pdir_mask =   mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval5;

  mcal::reg_access<std::uint8_t,
                   std::uint8_t,
                   mcal::reg::ddrb,
                   pdir_mask>::reg_or();

  // Enable SPI(TM) as master mode, clock idle to high, etc.
  // Set the SPI(TM) clock to f_osc/64 = (1/4)MHz.
  constexpr std::uint8_t spcr_mask =   mcal::reg::bval1
                                     | mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval4
                                     | mcal::reg::bval6;

  mcal::reg_access<std::uint8_t,
                   std::uint8_t,
                   mcal::reg::spcr,
                   spcr_mask>::reg_set();

  // Set the chip-select-not ports to output high.
  mcal::port::port2::set_pin_high();
  mcal::port::port2::set_direction_output();

  mcal::port::port3::set_pin_high();
  mcal::port::port3::set_direction_output();
}

mcal::spi::spi_communication::~spi_communication()
{
}

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{
  mcal::irq::disable_all();

  // If the SPI(TM) is idle, begin transmission.
  if(!send_is_active)
  {
    // Set the send-active flag.
    send_is_active = true;

    // Set the chip-select-not for the appropriate channel to low.
    if(channel == static_cast<std::uint8_t>(1U))
    {
      mcal::port::port3::set_pin_low();
    }
    else
    {
      mcal::port::port2::set_pin_low();
    }

    // Send the first byte over SPI(TM).
    mcal::reg_access<std::uint8_t,
                     std::uint8_t,
                     mcal::reg::spdr>::reg_set(byte_to_send);

    // Enable the SPI(TM) rx/tx interrupt.
    enable_rx_tx_interrupt();

    mcal::irq::enable_all();
  }
  else
  {
    // A transmission is already in progress.
    // Pack the next byte-to-send in the send-buffer.
    send_buffer.in(byte_to_send);

    mcal::irq::enable_all();
  }

  return true;
}

bool mcal::spi::spi_communication::send(const data_type& data_to_send)
{
  // Sequentially send all the bytes in the command.
  for(std::size_t count = 0U; count < data_to_send.size(); ++count)
  {
    static_cast<void>(send(data_to_send[count]));
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

bool mcal::spi::spi_communication::recv(data_type& data_to_recv)
{
  const std::size_t count_to_recv = (std::min)(data_to_recv.size(), recv_ready());

  for(std::size_t count = 0U; count < count_to_recv; ++count)
  {
    std::uint8_t byte_to_recv;

    recv(byte_to_recv);

    data_to_recv[count] = byte_to_recv;
  }

  return true;
}

std::size_t mcal::spi::spi_communication::recv_ready() const
{
  disable_rx_tx_interrupt();

  // Get the count of bytes in the receive buffer.
  const std::size_t count = recv_buffer.inque();

  enable_rx_tx_interrupt();

  return count;
}

bool mcal::spi::spi_communication::idle() const
{
  disable_rx_tx_interrupt();

  const bool is_active = send_is_active;

  enable_rx_tx_interrupt();

  return (!is_active);
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
/*
  // The SPI(TM) interrupt is on end-of-transmission.

  // Receive the byte from the previous transmission.
  const std::uint8_t byte_to_recv = mcal::reg_access<std::uint8_t,
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
      mcal::port::port3::set_pin_high();
    }
    else
    {
      mcal::port::port2::set_pin_high();
    }

    // Disable the SPI(TM) rx/tx interrupt.
    disable_rx_tx_interrupt();
  }
  else
  {
    // Send the next byte if there is at least one in the send queue.
    const std::uint8_t byte_to_send = mcal::spi::the_spi.send_buffer.out();

    mcal::reg_access<std::uint8_t,
                     std::uint8_t,
                     mcal::reg::spdr>::reg_set(byte_to_send);
  }
*/
}
