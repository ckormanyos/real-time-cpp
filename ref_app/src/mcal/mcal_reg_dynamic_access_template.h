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
      template<typename addr_type,
               typename reg_type>
      struct dynamic_access
      {
        static reg_type reg_get(const addr_type address) { return *reinterpret_cast<volatile reg_type*>(address); }

        static void reg_set(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address)  = value; }
        static void reg_and(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= value; }
        static void reg_or (const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) |= value; }
        static void reg_not(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= reg_type(~value); }
        static void reg_msk(const addr_type address, const reg_type value, const reg_type mask_value)
        {
          *reinterpret_cast<volatile reg_type*>(address) = reg_type(reg_type(reg_get(address) & reg_type(~mask_value)) | reg_type(value & mask_value));
        }

        static void bit_set(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) |= static_cast<reg_type>(1UL << value); }
        static void bit_clr(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << value)); }
        static void bit_not(const addr_type address, const reg_type value) { *reinterpret_cast<volatile reg_type*>(address) ^= static_cast<reg_type>(1UL << value); }
        static bool bit_get(const addr_type address, const reg_type value) { return (static_cast<volatile reg_type>(reg_get(address) & static_cast<reg_type>(1UL << value)) != static_cast<reg_type>(0U)); }
      };
    }
  }

#endif // _MCAL_REG_DYNAMIC_ACCESS_TEMPLATE_2013_12_13_H_
