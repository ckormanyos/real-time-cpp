///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H_
  #define MCAL_PORT_2014_01_10_H_

  #include <mcal_cpu.h>
  #include <mcal_reg.h>

  #include <cstddef>
  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      inline void init(const config_type*) { }

      template<const std::uintptr_t InstanceBase, const unsigned PIN_ID>
      class port_pin
      {
      private:
        static constexpr std::uintptr_t instance_base { InstanceBase };
        static constexpr unsigned pin { PIN_ID };

      public:
        static auto set_direction_output() -> void
        {
          mcal::cpu::acquire_spin_lock(&sync_object);
          GPIO_CONFIG_AS_OUTPUT();
          mcal::cpu::release_spin_lock(&sync_object);
        }

        static auto set_direction_input() -> void
        {
          // Not yet implemented.
        }

        static auto set_pin_high() -> void
        {
          mcal::cpu::acquire_spin_lock(&sync_object);
          output_is_high = true;
          OUTPUT_HIGH();
          mcal::cpu::release_spin_lock(&sync_object);
        }

        static auto set_pin_low() -> void
        {
          mcal::cpu::acquire_spin_lock(&sync_object);
          output_is_high = false;
          OUTPUT_LOW();
          mcal::cpu::release_spin_lock(&sync_object);
        }

        static auto read_input_value() -> bool
        {
          // Not yet implemented.
          return false;
        }

        static auto toggle_pin() -> void
        {
          mcal::cpu::acquire_spin_lock(&sync_object);
          (output_is_high ? OUTPUT_LOW() : OUTPUT_HIGH());
          output_is_high = (!output_is_high);
          mcal::cpu::release_spin_lock(&sync_object);
        }

      private:
        static volatile std::uint32_t sync_object;
        static bool output_is_high;

        static auto GPIO_CONFIG_AS_OUTPUT() -> void
        {
          if(instance_base == mcal::reg::gpio0)
          {
            *(volatile uint32_t*)(uintptr_t)(0x000F4000 + (pin * 4)) /* PADCFG_CTRL0_CFG0_PADCONFIG */ = 0x08014007ul;
          }
          else if(instance_base == mcal::reg::mcu_gpio0)
          {
            *(volatile uint32_t*)(uintptr_t)(0x4084000 + (pin * 4)) /* MCU_PADCFG_CTRL0_CFG0_PADCONFIG */ = 0x08014007ul;
          }
          else
          {
            /* GPIO1 has no pad configuration */
          }

          *(volatile uint32_t*)(instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x0C /* GPIO_CLR_DATA */) |= (1ul << (pin % 32));
          *(volatile uint32_t*)(instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x04 /* GPIO_OUT_DATA */) &= ~((uint32_t)(1ul << (pin % 32)));
          *(volatile uint32_t*)(instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x00 /* GPIO_DIR      */) &= ~((uint32_t)(1ul << (pin % 32)));
        }

        static auto OUTPUT_HIGH() -> void { *(volatile uint32_t*)(instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x08 /* GPIO_SET_DATA */) = (1ul << (pin % 32)); }
        static auto OUTPUT_LOW () -> void { *(volatile uint32_t*)(instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x0C /* GPIO_CLR_DATA */) = (1ul << (pin % 32)); }

        #if 0
        // Notes on gpio registers.
        instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x00 /* GPIO_DIR      */
        instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x04 /* GPIO_OUT_DATA */
        instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x08 /* GPIO_SET_DATA */
        instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x0C /* GPIO_CLR_DATA */
        instance_base + (uintptr_t)((pin/32) * 0x28) + (uintptr_t)0x10 /* GPIO_IN_DATA  */
        #endif
      };

      template<const std::uintptr_t InstanceBase, const unsigned PIN_ID>
      volatile std::uint32_t port_pin<InstanceBase, PIN_ID>::sync_object { };

      template<const std::uintptr_t InstanceBase, const unsigned PIN_ID>
      bool port_pin<InstanceBase, PIN_ID>::output_is_high { };
    }
  }

#endif // MCAL_PORT_2014_01_10_H
