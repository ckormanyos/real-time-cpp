///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_
  #define MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Warray-bounds"
  #endif

  namespace mcal
  {
    namespace reg
    {
      template<typename RegisterAddressType,
               typename RegisterValueType>
      struct reg_access_dynamic final
      {
        using register_address_type = RegisterAddressType;
        using register_value_type   = RegisterValueType;

        static auto reg_get(const register_address_type address) -> register_value_type                   { return *reinterpret_cast<volatile register_value_type*>(address); }
        static auto reg_set(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = value; }
        static auto reg_and(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & value); }
        static auto reg_or (const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | value); }
        static auto reg_not(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~value)); }

        static auto reg_msk(const register_address_type address,
                            const register_value_type   value,
                            const register_value_type   mask_value) -> void
        {
          volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address);

          *pa =
            static_cast<register_value_type>
            (
                static_cast<register_value_type>(reg_get(address) & static_cast<register_value_type>(~mask_value))
              | value
            );
        }

        static auto bit_set(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | static_cast<register_value_type>(1UL << value)); }
        static auto bit_clr(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value))); }
        static auto bit_not(const register_address_type address, const register_value_type value) -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa ^ static_cast<register_value_type>(1UL << value)); }
        static auto bit_get(const register_address_type address, const register_value_type value) -> bool { return (static_cast<register_value_type>(reg_get(address) & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  // -Warray-bounds
  #pragma GCC diagnostic pop
  #endif

#endif // MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_
