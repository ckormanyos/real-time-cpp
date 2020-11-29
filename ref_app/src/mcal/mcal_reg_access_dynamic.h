///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_
  #define MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_

  namespace mcal
  {
    namespace reg
    {
      template<typename register_address_type,
               typename register_value_type>
      struct reg_access_dynamic final
      {
        static register_value_type
                    reg_get(const register_address_type address) { return *reinterpret_cast<volatile register_value_type*>(address); }

        static void reg_set(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa =       value; }
        static void reg_and(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & value; }
        static void reg_or (const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa | value; }
        static void reg_not(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & register_value_type(~value); }

        static void reg_msk(const register_address_type address, const register_value_type value,
                            const register_value_type mask_value)
        {
          volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address);

          *pa = register_value_type(register_value_type(reg_get(address) & register_value_type(~mask_value)) | register_value_type(value & mask_value));
        }

        static void bit_set(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa | static_cast<register_value_type>(1UL << value); }
        static void bit_clr(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value)); }
        static void bit_not(const register_address_type address, const register_value_type value) { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa ^ static_cast<register_value_type>(1UL << value); }
        static bool bit_get(const register_address_type address, const register_value_type value) { return (static_cast<register_value_type>(reg_get(address) & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

#endif // MCAL_REG_ACCESS_DYNAMIC_2013_12_13_H_
