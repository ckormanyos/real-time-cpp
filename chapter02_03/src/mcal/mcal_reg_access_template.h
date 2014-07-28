///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_
  #define _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_

  namespace mcal
  {
    namespace reg
    {
      template<typename register_address_type,
               typename register_value_type,
               const register_address_type address,
               const register_value_type value = static_cast<register_value_type>(0)>
      struct access
      {
        static void     reg_set() { *reinterpret_cast<volatile register_value_type*>(address)  = value; }
        static void     reg_and() { *reinterpret_cast<volatile register_value_type*>(address) &= value; }
        static void     reg_or () { *reinterpret_cast<volatile register_value_type*>(address) |= value; }
        static void     reg_not() { *reinterpret_cast<volatile register_value_type*>(address) &= register_value_type(~value); }
        static register_value_type reg_get() { return *reinterpret_cast<volatile register_value_type*>(address); }

        template<const register_value_type mask_value>
        static void     reg_msk()
        {
          *reinterpret_cast<volatile register_value_type*>(address) = register_value_type(register_value_type(reg_get() & register_value_type(~mask_value)) | register_value_type(value & mask_value));
        }

        static void     bit_set() { *reinterpret_cast<volatile register_value_type*>(address) |= static_cast<register_value_type>(1UL << value); }
        static void     bit_clr() { *reinterpret_cast<volatile register_value_type*>(address) &= static_cast<register_value_type>(~static_cast<register_value_type>(1UL << value)); }
        static void     bit_not() { *reinterpret_cast<volatile register_value_type*>(address) ^= static_cast<register_value_type>(1UL << value); }
        static bool     bit_get() { return (static_cast<volatile register_value_type>(reg_get() & static_cast<register_value_type>(1UL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

#endif // _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_
