///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H
  #define MCAL_PORT_2012_06_27_H

  #include <cstdint>

  #include <mcal_reg.h>

  extern auto mcal_port_pin_expander_set_direction_output(const uint8_t bpos) -> void;
  extern auto mcal_port_pin_expander_set_direction_input (const uint8_t bpos) -> void;
  extern auto mcal_port_pin_expander_set_pin_high        (const uint8_t bpos) -> void;
  extern auto mcal_port_pin_expander_set_pin_low         (const uint8_t bpos) -> void;
  extern auto mcal_port_pin_expander_read_input_value    (const uint8_t bpos) -> bool;
  extern auto mcal_port_pin_expander_toggle_pin          (const uint8_t bpos) -> void;

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin
      {
      private:
        using address_uintptr_type = addr_type;
        using register_value_type  = reg_type;

        static constexpr address_uintptr_type port_base_address = port;
        static constexpr address_uintptr_type pdir_set_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(1)));
        static constexpr address_uintptr_type pdir_clr_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(2)));
        static constexpr address_uintptr_type pout_set_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(5)));
        static constexpr address_uintptr_type pout_clr_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(6)));
        static constexpr address_uintptr_type pout_tgl_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(7)));
        static constexpr address_uintptr_type pout_inp_address = static_cast<address_uintptr_type>(port_base_address + static_cast<address_uintptr_type>(UINT8_C(8)));

        static constexpr register_value_type  bpos_value        = bpos;

      public:
        static auto set_direction_output() noexcept -> void
        {
          // Set the port pin's direction to output.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pdir_set_address,
                                       bpos_value>::bit_set();
        }

        static auto set_direction_input() noexcept -> void
        {
          // Set the port pin's direction to input.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pdir_clr_address,
                                       bpos_value>::bit_set();
        }

        static auto set_pin_high() noexcept -> void
        {
          // Set the port output value to high.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pout_set_address,
                                       bpos_value>::bit_set();
        }

        static auto set_pin_low() noexcept -> void
        {
          // Set the port output value to low.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pout_clr_address,
                                       bpos_value>::bit_set();
        }

        static auto read_input_value() noexcept -> bool
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<address_uintptr_type,
                                              register_value_type,
                                              pout_inp_address,
                                              bpos_value>::bit_get();
        }

        static auto toggle_pin() noexcept -> void
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pout_tgl_address,
                                       bpos_value>::bit_set();
        }
      };

      template<const std::uint8_t bpos>
      class port_pin_expander
      {
      public:
        static auto set_direction_output() -> void {        mcal_port_pin_expander_set_direction_output(bpos); }
        static auto set_direction_input () -> void {        mcal_port_pin_expander_set_direction_input (bpos); }
        static auto set_pin_high        () -> void {        mcal_port_pin_expander_set_pin_high        (bpos); }
        static auto set_pin_low         () -> void {        mcal_port_pin_expander_set_pin_low         (bpos); }
        static auto read_input_value    () -> bool { return mcal_port_pin_expander_read_input_value    (bpos); }
        static auto toggle_pin          () -> void {        mcal_port_pin_expander_toggle_pin          (bpos); }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H
