///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_spi.h>
#include <mcal_reg_access.h>

void mcal::spi::init(const mcal::spi::config_type*)
{
/*
  // Initialize spi2.

  // pb13 = sck
  // pb14 = miso
  // pb15 = mosi

  // Set pb13...pb15 to port alternate function mode.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpiob_moder,
                    std::uint32_t(  std::uint32_t(UINT32_C(0x02) << 26)
                                  | std::uint32_t(UINT32_C(0x02) << 28)
                                  | std::uint32_t(UINT32_C(0x02) << 30))>::reg_or();

  // Set pb13...pb15 to port output type push-pull.
  mcal::reg::access<std::uint32_t,
                    std::uint16_t,
                    mcal::reg::gpiob_otyper,
                    std::uint16_t(~std::uint16_t(UINT16_C(0x07) << 13))>::reg_and();

  // Set pb13...pb15 to port speed 50MHz.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpiob_ospeedr,
                    std::uint32_t(  std::uint32_t(UINT32_C(0x03) << 26)
                                  | std::uint32_t(UINT32_C(0x03) << 28)
                                  | std::uint32_t(UINT32_C(0x03) << 30))>::reg_or();

  // Set pb13...pb15 for no pull up, no pull down.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpiob_pupdr,
                    ~std::uint32_t(  std::uint32_t(UINT32_C(0x03) << 26)
                                   | std::uint32_t(UINT32_C(0x03) << 28)
                                   | std::uint32_t(UINT32_C(0x03) << 30))>::reg_and();

  // Connect the pb13...pb15 pins to spi2 alternate function.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpiob_afrh,
                    std::uint32_t(  std::uint32_t(UINT32_C(0x05) << 20)
                                  | std::uint32_t(UINT32_C(0x05) << 24)
                                  | std::uint32_t(UINT32_C(0x05) << 28))>::reg_or();

  // Power management: Enable the power for spi2.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_apb1enr,
                    std::uint32_t(UINT32_C(0x01) << 14)>::reg_or();

  // Set the spi2 control register.
  // Serial clock idles to low.
  // Prescaler is 4.
  // Data is sampled at the first rising edge.
  // Set to full duplex mode.
  // Set master mode, nss pin high.
  // Set nss management to internal and pull the internal nss high.

  static constexpr std::uint32_t spi2_cr1_setting =
    std::uint32_t(  std::uint32_t(UINT32_C(1) << 2)   // mstr
                  | std::uint32_t(UINT32_C(4) << 3)   // br[2:0]
                  | std::uint32_t(UINT32_C(1) << 6)   // spe
                  | std::uint32_t(UINT32_C(1) << 8)   // ssi
                  | std::uint32_t(UINT32_C(1) << 9)); // ssm

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::spi2_cr1,
                    spi2_cr1_setting>::reg_set();
*/
}

/*
void dummy_spi_send()
{
  mcal::reg::access<std::uint32_t,
                    std::uint8_t,
                    mcal::reg::spi2_dr,
                    UINT8_C(0x55)>::reg_set();
}
*/
