///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_WORD_2020_05_06_H
  #define MCAL_PORT_WORD_2020_05_06_H

  #include <mcal_reg.h>

  void mcal_port_word_expander_set_port(const uint16_t value_to_write);
  void mcal_port_word_expander_set_direction_output();
  void mcal_port_word_expander_set_direction_input();

  namespace mcal { namespace port {

  template<typename addr_type,
           typename reg_type,
           const addr_type port>
  class port_word
  {
  private:
    using address_uintptr_type = addr_type;
    using register_value_type  = reg_type;

    static constexpr address_uintptr_type port_address = port;
    static constexpr address_uintptr_type pdir_address = port_address - address_uintptr_type(1U);
    static constexpr address_uintptr_type pinp_address = port_address - address_uintptr_type(2U);

  public:
    static auto set_port(const register_value_type value_to_write) -> void
    {
      mcal::reg::reg_access_dynamic<address_uintptr_type,
                                    register_value_type>::reg_set(port_address, value_to_write);
    }

    static auto set_direction_output() -> void
    {
      mcal::reg::reg_access_static<address_uintptr_type,
                                   register_value_type,
                                   pdir_address,
                                   register_value_type(0xFFFFFFFFUL)>::reg_set();
    }

    static auto set_direction_input() -> void
    {
      mcal::reg::reg_access_static<address_uintptr_type,
                                   register_value_type,
                                   pdir_address,
                                   register_value_type(0x0UL)>::reg_set();
    }

    static register_value_type read_port()
    {
      const register_value_type value_to_read = mcal::reg::reg_access_static<address_uintptr_type,
                                                                             register_value_type,
                                                                             pinp_address>::reg_get();

      return value_to_read;
    }
  };

  template<typename register_value_type>
  class port_word_expander
  {
  public:
    static auto set_port(const std::uint16_t value_to_write) -> void
    {
      mcal_port_word_expander_set_port(value_to_write);
    }

    static auto set_direction_output() -> void
    {
      mcal_port_word_expander_set_direction_output();
    }

    static auto set_direction_input() -> void
    {
      mcal_port_word_expander_set_direction_input();
    }
  };

  } } // namespace mcal::port

#endif // MCAL_PORT_WORD_2020_05_06_H
