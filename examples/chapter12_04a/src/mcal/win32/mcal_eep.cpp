#include <mcal_eep.h>

auto mcal::eep::write(const address_type addr, const std::uint8_t data) -> void // NOLINT(bugprone-easily-swappable-parameters)
{
  static_cast<void>(addr);
  static_cast<void>(data);
}

auto mcal::eep::read(const address_type addr) -> std::uint8_t
{
  static_cast<void>(addr);

  return static_cast<std::uint8_t>(UINT8_C(0));
}
