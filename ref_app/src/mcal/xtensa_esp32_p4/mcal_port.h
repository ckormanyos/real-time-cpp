///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Register port manipulations are originally from:

/******************************************************************************************
  Filename    : gpio.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : GPIO driver implementation
  
******************************************************************************************/

#ifndef MCAL_PORT_2025_02_22_H
  #define MCAL_PORT_2025_02_22_H

  #include <mcal_reg.h>

  #include <cstddef>
  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      template<const unsigned PortIndex>
      class port_pin
      {
      private:
        static constexpr std::uint8_t my_pin { static_cast<std::uint8_t>(PortIndex) };

        static constexpr uintptr_t GPIO_BASE      { (uintptr_t) UINT32_C(0x500E0000) };
        static constexpr uintptr_t LP_IO_MUX_BASE { (uintptr_t) UINT32_C(0x5012B000) };
        static constexpr uintptr_t IO_MUX_BASE    { (uintptr_t) UINT32_C(0x500E1000) };

        typedef union
        {
          volatile uint32_t reg;

          struct
          {
            volatile uint32_t MCU_OE     : 1;
            volatile uint32_t SLP_SEL    : 1;
            volatile uint32_t MCU_WPD    : 1;
            volatile uint32_t MCU_WPU    : 1;
            volatile uint32_t MCU_IE     : 1;
            volatile uint32_t MCU_DRV    : 2;
            volatile uint32_t FUN_WPD    : 1;
            volatile uint32_t FUN_WPU    : 1;
            volatile uint32_t FUN_IE     : 1;
            volatile uint32_t FUN_DRV    : 2;
            volatile uint32_t MCU_SEL    : 3;
            volatile uint32_t FILTER_EN  : 1;
                     uint32_t            : 16;
          }
          bit;
        }
        IO_MUX_GPIO;

        typedef union
        {
          volatile uint32_t reg;

          struct
          {
            volatile uint32_t OUT_SEL     : 9;
            volatile uint32_t INV_SEL     : 1;
            volatile uint32_t OEN_SEL     : 1;
            volatile uint32_t OEN_INV_SEL : 1;
                     uint32_t             : 20;
          }
          bit;
        }
        GPIO_FUNC_OUT_SEL_CFG;

        typedef union
        {
          volatile uint32_t reg;

          struct
          {
            volatile uint32_t REG_PAD_DRV       : 2;
            volatile uint32_t REG_PAD_RDE       : 1;
            volatile uint32_t REG_PAD_RUE       : 1;
            volatile uint32_t REG_PAD_MUX_SEL   : 1;
            volatile uint32_t REG_PAD_FUN_SEL   : 2;
            volatile uint32_t REG_PAD_SLP_SEL   : 1;
            volatile uint32_t REG_PAD_SLP_IE    : 1;
            volatile uint32_t REG_PAD_SLP_OE    : 1;
            volatile uint32_t REG_PAD_FUN_IE    : 1;
            volatile uint32_t REG_PAD_FILTER_EN : 1;
                     uint32_t                   : 20;
          }
          bit;
        }
        LP_IO_MUX_GPIO;

        static void gpio_cfg_output()
        {
          if((unsigned) my_pin <= 54u)
          {
            volatile IO_MUX_GPIO* pIO_MUX_GPIO = (volatile IO_MUX_GPIO*)(IO_MUX_BASE + 4u + 4u * (unsigned) my_pin);
            volatile GPIO_FUNC_OUT_SEL_CFG* pGPIO_FUNC_OUT_SEL_CFG = (volatile GPIO_FUNC_OUT_SEL_CFG*)(GPIO_BASE + 0x558ul + 4u * (unsigned) my_pin);
            volatile LP_IO_MUX_GPIO* pLP_IO_MUX_GPIO = (volatile LP_IO_MUX_GPIO*)(LP_IO_MUX_BASE + 8u + 4u * (unsigned) my_pin);
            volatile uint32_t* pGPIO_OUTx_W1TC     = (volatile uint32_t*)(GPIO_BASE + (((unsigned) my_pin < 32u) ? 0x0Cu : 0x18u));
            volatile uint32_t* pGPIO_ENABLE1x_W1TS = (volatile uint32_t*)(GPIO_BASE + (((unsigned) my_pin < 32u) ? 0x24u : 0x30u));

            /* configure the pinmux */
            pIO_MUX_GPIO->bit.FUN_DRV = 2;
            pIO_MUX_GPIO->bit.FUN_IE  = 0;
            pIO_MUX_GPIO->bit.MCU_SEL = 1;

            /* set the output configuration */
            pGPIO_FUNC_OUT_SEL_CFG->bit.OUT_SEL = 256;
            pGPIO_FUNC_OUT_SEL_CFG->bit.OEN_SEL = 1;

            if((unsigned) my_pin < 16u)
            {
              /* make LP_GPIO use HP_IO_MUX */
              pLP_IO_MUX_GPIO->bit.REG_PAD_MUX_SEL = 0;
            }
  
            /* drive the IO output low */
            *pGPIO_OUTx_W1TC     = (uint32_t)(1u << (((unsigned) my_pin < 32u) ? (unsigned) my_pin : ((unsigned) my_pin - 32u)));
            *pGPIO_ENABLE1x_W1TS = (uint32_t)(1u << (((unsigned) my_pin < 32u) ? (unsigned) my_pin : ((unsigned) my_pin - 32u)));
          }
        }

        static void gpio_set_output_level(const uint8_t level)
        {
          if(((unsigned) my_pin <= 54u) && ((unsigned) level <= 1u))
          {
            volatile uint32_t* pGPIO_OUT_W1Tx = (volatile uint32_t*)(GPIO_BASE + (((unsigned) my_pin < 32u) ? 8u : 0x14u) + (((unsigned) level == 1u) ? (0u) : (4u)));

            *pGPIO_OUT_W1Tx = (uint32_t)(1u << (((unsigned) my_pin < 32u) ? (unsigned) my_pin : ((unsigned) my_pin - 32u)));
          }
        }

        static void gpio_toggle_output_level()
        {
          if((unsigned) my_pin <= 54u)
          {
            volatile uint32_t* pGPIO_OUT = (volatile uint32_t*)(GPIO_BASE + 4u + (((unsigned) my_pin < 32u) ? 0u : 0xCu));

            *pGPIO_OUT ^= (uint32_t)(1u << (((unsigned) my_pin < 32u) ? (unsigned) my_pin : ((unsigned) my_pin - 32u)));
          }
        }

      public:
        static auto set_direction_output() -> void
        {
          gpio_cfg_output();
        }

        static auto set_direction_input() -> void
        {
        }

        static auto set_pin_high() -> void
        {
          gpio_set_output_level(std::uint8_t { UINT8_C(1) });
        }

        static auto set_pin_low() -> void
        {
          gpio_set_output_level(std::uint8_t { UINT8_C(0) });
        }

        static auto read_input_value() -> bool
        {
          return false;
        }

        static auto toggle_pin() -> void
        {
          gpio_toggle_output_level();
        }
      };
    }
  }

#endif // MCAL_PORT_2025_02_22_H
