#include <mcal_spi.h>

mcal::spi::spi_communication mcal::spi::the_spi;


mcal::spi::spi_communication::spi_communication()
{
}

bool mcal::spi::spi_communication::send(const std::uint8_t)
{
  return false;
}

bool mcal::spi::spi_communication::send(const data_type&)
{
  return false;
}

bool mcal::spi::spi_communication::recv(std::uint8_t&)
{
  return false;
}

bool mcal::spi::spi_communication::recv(data_type& rsp)
{
  return false;
}

std::size_t mcal::spi::spi_communication::recv_ready() const
{
  return 0U;
}

bool mcal::spi::spi_communication::idle() const
{
  return true;
}
