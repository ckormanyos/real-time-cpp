#include <cstdint>

#include <mcal_eep.h>
#include <mcal_reg.h>

void mcal::eep::init(const config_type*)
{
}

void mcal::eep::write(const address_type addr, const std::uint8_t data)
{
  static_cast<void>(addr);
  static_cast<void>(data);
}

std::uint8_t mcal::eep::read(const address_type addr)
{
  static_cast<void>(addr);

  return UINT8_C(0);
}
