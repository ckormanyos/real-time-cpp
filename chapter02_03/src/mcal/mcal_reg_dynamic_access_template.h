///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_REG_DYNAMIC_ACCESS_TEMPLATE_2013_12_13_H_
  #define _MCAL_REG_DYNAMIC_ACCESS_TEMPLATE_2013_12_13_H_

  namespace mcal
  {
    namespace reg
    {
      template<typename register_address_type,
               typename register_value_type>
      struct dynamic_access
      {
        static register_value_type reg_get(const register_address_type address) { return *reinterpret_cast<volatile register_value_type*>(address); }

        static void reg_set(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address)  = value; }
        static void reg_and(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= value; }
        static void reg_or (const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) |= value; }
        static void reg_not(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= register_value_type(~value); }
        static void reg_msk(const register_address_type address, const register_value_type value, const register_value_type mask_value)
        {
          *reinterpret_cast<volatile register_value_type*>(address) = register_value_type(register_value_type(reg_get(address) & register_value_type(~mask_value)) | register_value_type(value & mask_value));
        }

        static void bit_set(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) |= static_cast<register_value_type>(1UL << value); }
        static void bit_clr(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) &= static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value)); }
        static void bit_not(const register_address_type address, const register_value_type value) { *reinterpret_cast<volatile register_value_type*>(address) ^= static_cast<register_value_type>(1UL << value); }
        static bool bit_get(const register_address_type address, const register_value_type value) { return (static_cast<volatile register_value_type>(reg_get(address) & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

#endif // _MCAL_REG_DYNAMIC_ACCESS_TEMPLATE_2013_12_13_H_
