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
      template<typename addr_type,
               typename reg_type,
               const addr_type addr,
               const reg_type val = static_cast<reg_type>(0)>
      class access
      {
      public:
        static void     reg_set() { *reinterpret_cast<volatile reg_type*>(addr)  = val; }
        static void     reg_and() { *reinterpret_cast<volatile reg_type*>(addr) &= val; }
        static void     reg_or () { *reinterpret_cast<volatile reg_type*>(addr) |= val; }
        static reg_type reg_get() { return *reinterpret_cast<volatile reg_type*>(addr); }
        static void     bit_set() { *reinterpret_cast<volatile reg_type*>(addr) |= static_cast<reg_type>(1UL << val); }
        static void     bit_clr() { *reinterpret_cast<volatile reg_type*>(addr) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << val)); }
        static void     bit_not() { *reinterpret_cast<volatile reg_type*>(addr) ^= static_cast<reg_type>(1UL << val); }
        static bool     bit_get() { return (static_cast<volatile reg_type>(reg_get() & static_cast<reg_type>(1UL << val)) != static_cast<reg_type>(0U)); }

        static void     reg_set(const reg_type new_val) { *reinterpret_cast<volatile reg_type*>(addr) = new_val; }
      };
    }
  }

#endif // _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_
