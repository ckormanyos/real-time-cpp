#include <mcal_eep.h>

auto mcal::eep::write(const address_type addr, const std::uint8_t data) -> void
{
  static_cast<void>(addr);
  static_cast<void>(data);
}

auto mcal::eep::read(const address_type addr) -> std::uint8_t
{
  static_cast<void>(addr);

  return std::uint8_t(0U);
}
