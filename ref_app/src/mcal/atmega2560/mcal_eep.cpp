#include <mcal_cpu.h>
#include <mcal_eep.h>
#include <mcal_reg.h>

namespace
{
  bool mcal_eep_is_busy()
  {
    return (mcal::reg::reg_access_static<std::uint8_t,
                                         std::uint8_t,
                                         mcal::reg::eecr,
                                         UINT8_C(1)>::bit_get());
  }
}

void mcal::eep::init(const config_type*)
{
}

void mcal::eep::write(const address_type addr, const std::uint8_t data)
{
  while(mcal_eep_is_busy())
  {
    mcal::cpu::nop();
  }

  // Write the address register.
  mcal::reg::reg_access_dynamic<std::uint8_t,
                                address_type>::reg_set(mcal::reg::eear, addr);

  // Write the data register.
  mcal::reg::reg_access_dynamic<std::uint8_t,
                                std::uint8_t>::reg_set(mcal::reg::eedr, data);

  // Set eecr.eempe (bit 2).
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::eecr,
                               UINT8_C(2)>::bit_set();

  // Set eecr.eepe (bit 1).
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::eecr,
                               UINT8_C(1)>::bit_set();
}

std::uint8_t mcal::eep::read(const address_type addr)
{
  while(mcal_eep_is_busy())
  {
    mcal::cpu::nop();
  }

  // Write the address register.
  mcal::reg::reg_access_dynamic<std::uint8_t,
                                address_type>::reg_set(mcal::reg::eear, addr);

  // Set eecr.eere (bit 0).
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::eecr,
                               UINT8_C(0)>::bit_set();

  // Read one data byte.
  const std::uint8_t data =
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint8_t,
                                 mcal::reg::eedr>::reg_get();

  return data;
}

/*
#define EERE  0
#define EEPE  1
#define EEMPE 2
#define EERIE 3
#define EEPM0 4
#define EEPM1 5
*/

/*
while(EECR & (1 << EEPE));
EEAR = uiAddress;
EEDR = ucData;
EECR |= 1 << EEMPE;
EECR |= 1 << EEPE;
*/

/*
  while (EECR & (1 << EEPE));
  EEAR = uiAddress;
  EECR |= (1 << EERE);
  return EEDR;
*/
