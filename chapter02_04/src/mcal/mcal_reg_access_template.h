#ifndef _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_
  #define _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_

  namespace mcal
  {
    template<typename addr_type,
              typename reg_type,
              const addr_type addr,
              const reg_type val>
    class reg_access
    {
    public:
      static void     fixed_reg_set(void) { *reinterpret_cast<volatile reg_type*>(addr)  = val; }
      static void     fixed_reg_and(void) { *reinterpret_cast<volatile reg_type*>(addr) &= val; }
      static void     fixed_reg_or (void) { *reinterpret_cast<volatile reg_type*>(addr) |= val; }
      static reg_type fixed_reg_get(void) { return *reinterpret_cast<volatile reg_type*>(addr); }

      static void     fixed_bit_set(void) { *reinterpret_cast<volatile reg_type*>(addr) |= static_cast<reg_type>(1UL << val); }
      static void     fixed_bit_clr(void) { *reinterpret_cast<volatile reg_type*>(addr) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << val)); }
      static void     fixed_bit_not(void) { *reinterpret_cast<volatile reg_type*>(addr) ^= static_cast<reg_type>(1UL << val); }
      static bool     fixed_bit_get(void) { return (static_cast<volatile reg_type>(fixed_reg_get() & static_cast<reg_type>(1UL << val)) != static_cast<reg_type>(0U)); }

      static void variable_reg_set(const reg_type new_val) { *reinterpret_cast<volatile reg_type*>(addr) = new_val; }
    };
  }

#endif // _MCAL_REG_ACCESS_TEMPLATE_2010_12_01_H_
