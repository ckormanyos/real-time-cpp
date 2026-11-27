#include <mcal_eep.h>

void mcal::eep::write(const address_type addr, const std::uint8_t data)
{
  static_cast<void>(addr);
  static_cast<void>(data);
}

std::uint8_t mcal::eep::read(const address_type addr)
{
  static_cast<void>(addr);

  return std::uint8_t(0U);
}
