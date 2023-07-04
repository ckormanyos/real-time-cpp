///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_ACCESS_STATIC_2010_12_01_H_
  #define MCAL_REG_ACCESS_STATIC_2010_12_01_H_

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Warray-bounds"
  #endif

  namespace mcal
  {
    namespace reg
    {
      template<typename RegisterAddressType,
               typename RegisterValueType,
               const RegisterAddressType address,
               const RegisterValueType value = static_cast<RegisterValueType>(0U)>
      struct reg_access_static final
      {
        using register_value_type   = RegisterValueType;
        using register_address_type = RegisterAddressType;

        static auto reg_get() -> register_value_type { volatile register_value_type* pa = reinterpret_cast<register_value_type*>(address); return *pa; }
        static auto reg_set() -> void                { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = value; }
        static auto reg_and() -> void                { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & value); }
        static auto reg_or () -> void                { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | value); }
        static auto reg_not() -> void                { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~value)); }

        template<const register_value_type mask_value>
        static auto reg_msk() -> void
        {
          volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address);

          *pa =
            static_cast<register_value_type>
            (
                static_cast<register_value_type>(reg_get() & static_cast<register_value_type>(~mask_value))
              | value
            );
        }

        static auto bit_set() -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa | static_cast<register_value_type>(1ULL << value)); }
        static auto bit_clr() -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa & static_cast<register_value_type>(~static_cast<register_value_type>(1ULL << value))); }
        static auto bit_not() -> void { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = static_cast<register_value_type>(*pa ^ static_cast<register_value_type>(1ULL << value)); }
        static auto bit_get() -> bool { return (static_cast<register_value_type>(reg_get() & static_cast<register_value_type>(1ULL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  // -Warray-bounds
  #pragma GCC diagnostic pop
  #endif

#endif // MCAL_REG_ACCESS_STATIC_2010_12_01_H_
