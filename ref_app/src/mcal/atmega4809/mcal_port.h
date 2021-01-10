///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H_
  #define MCAL_PORT_2012_06_27_H_

  #include <cstdint>

  #include <mcal_reg.h>

  void mcal_port_pin_expander_set_direction_output(const uint8_t bpos);
  void mcal_port_pin_expander_set_direction_input (const uint8_t bpos);
  void mcal_port_pin_expander_set_pin_high        (const uint8_t bpos);
  void mcal_port_pin_expander_set_pin_low         (const uint8_t bpos);
  bool mcal_port_pin_expander_read_input_value    (const uint8_t bpos);
  void mcal_port_pin_expander_toggle_pin          (const uint8_t bpos);

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

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
        static constexpr address_uintptr_type pdir_set__address = port_base_address + address_uintptr_type(1U);
        static constexpr address_uintptr_type pdir_clr__address = port_base_address + address_uintptr_type(2U);
        static constexpr address_uintptr_type pout_set__address = port_base_address + address_uintptr_type(5U);
        static constexpr address_uintptr_type pout_clr__address = port_base_address + address_uintptr_type(6U);
        static constexpr address_uintptr_type pout_tgl__address = port_base_address + address_uintptr_type(7U);
        static constexpr address_uintptr_type pout_inp__address = port_base_address + address_uintptr_type(8U);

        static constexpr register_value_type  bpos_value        = bpos;

      public:
        static void set_direction_output() noexcept
        {
          // Set the port pin's direction to output.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pdir_set__address,
                                       bpos_value>::bit_set();
        }

        static void set_direction_input() noexcept
        {
          // Set the port pin's direction to input.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       pdir_clr__address,
                                       bpos_value>::bit_set();
        }

        static void set_pin_high() noexcept
        {
          // Set the port output value to high.
          *(std::uint8_t*) pout_set__address |= (std::uint8_t) (1U << bpos_value);
        }

        static void set_pin_low() noexcept
        {
          // Set the port output value to low.
          *(std::uint8_t*) pout_clr__address |= (std::uint8_t) (1U << bpos_value);
        }

        static bool read_input_value() noexcept
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<address_uintptr_type,
                                              register_value_type,
                                              pout_inp__address,
                                              bpos_value>::bit_get();
        }

        static void toggle_pin() noexcept
        {
          // Toggle the port output value.
          *(std::uint8_t*) pout_tgl__address |= (std::uint8_t) (1U << bpos_value);
        }
      };

      template<const std::uint8_t bpos>
      class port_pin_expander
      {
      public:
        static void set_direction_output() {        mcal_port_pin_expander_set_direction_output(bpos); }
        static void set_direction_input () {        mcal_port_pin_expander_set_direction_input (bpos); }
        static void set_pin_high        () {        mcal_port_pin_expander_set_pin_high        (bpos); }
        static void set_pin_low         () {        mcal_port_pin_expander_set_pin_low         (bpos); }
        static bool read_input_value    () { return mcal_port_pin_expander_read_input_value    (bpos); }
        static void toggle_pin          () {        mcal_port_pin_expander_toggle_pin          (bpos); }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H_
