///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H
  #define MCAL_PORT_2014_01_10_H

  #include <mcal_cpu.h>
  #include <mcal_reg.h>

  #include <cstddef>
  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      void init(const config_type*);

      template<const std::uintptr_t InstanceBase, const unsigned PIN_ID>
      class port_pin
      {
      private:
        static constexpr std::uintptr_t instance_base { InstanceBase };
        static constexpr unsigned pin { PIN_ID };
        static constexpr unsigned pin_mod32 { static_cast<unsigned>(pin % UINT32_C(32)) };

      public:
        static auto set_direction_output() noexcept -> void
        {
          mcal::cpu::secure::acquire_spin_lock(&sync_object);
          GPIO_CONFIG_AS_OUTPUT();
          mcal::cpu::secure::release_spin_lock(&sync_object);
        }

        static auto set_direction_input() noexcept -> void
        {
          // Not yet implemented.
        }

        static auto set_pin_high() noexcept -> void
        {
          mcal::cpu::secure::acquire_spin_lock(&sync_object);
          OUTPUT_HIGH();
          output_is_high = true;
          mcal::cpu::secure::release_spin_lock(&sync_object);
        }

        static auto set_pin_low() noexcept -> void
        {
          mcal::cpu::secure::acquire_spin_lock(&sync_object);
          OUTPUT_LOW();
          output_is_high = false;
          mcal::cpu::secure::release_spin_lock(&sync_object);
        }

        static auto read_input_value() noexcept -> bool
        {
          // Not yet implemented.
          return false;
        }

        static auto toggle_pin() noexcept -> void
        {
          mcal::cpu::secure::acquire_spin_lock(&sync_object);
          (output_is_high ? OUTPUT_LOW() : OUTPUT_HIGH());
          output_is_high = (!output_is_high);
          mcal::cpu::secure::release_spin_lock(&sync_object);
        }

      private:
        static volatile std::uint32_t sync_object;
        static bool output_is_high;

        static auto GPIO_CONFIG_AS_OUTPUT() noexcept -> void
        {
          if(instance_base == mcal::reg::gpio0)
          {
            *reinterpret_cast<volatile std::uint32_t*>(static_cast<std::uintptr_t>(UINT32_C(0x000F4000) + (pin * 4U))) /* PADCFG_CTRL0_CFG0_PADCONFIG */ = UINT32_C(0x08014007);
          }
          else if(instance_base == mcal::reg::mcu_gpio0)
          {
            *reinterpret_cast<volatile std::uint32_t*>(static_cast<std::uintptr_t>(UINT32_C(0x04084000) + (pin * 4U))) /* MCU_PADCFG_CTRL0_CFG0_PADCONFIG */ = UINT32_C(0x08014007);
          }
          else
          {
            /* GPIO1 has no pad configuration */
          }

          *reinterpret_cast<volatile std::uint32_t*>(static_cast<std::uintptr_t>(instance_base + static_cast<std::uintptr_t>((pin/32U) * UINT32_C(0x28)) + static_cast<std::uintptr_t>(UINT32_C(0x00)) /* GPIO_DIR      */)) &= static_cast<std::uint32_t>(~(static_cast<std::uint32_t>(UINT32_C(1) << pin_mod32)));
        }

        static auto OUTPUT_HIGH() noexcept -> void { *reinterpret_cast<volatile std::uint32_t*>(static_cast<std::uintptr_t>(instance_base + static_cast<std::uintptr_t>((pin/32) * 0x28) + UINT32_C(0x08) /* GPIO_SET_DATA */)) = static_cast<std::uint32_t>(UINT32_C(1) << pin_mod32); }
        static auto OUTPUT_LOW () noexcept -> void { *reinterpret_cast<volatile std::uint32_t*>(static_cast<std::uintptr_t>(instance_base + static_cast<std::uintptr_t>((pin/32) * 0x28) + UINT32_C(0x0C) /* GPIO_CLR_DATA */)) = static_cast<std::uint32_t>(UINT32_C(1) << pin_mod32); }

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
