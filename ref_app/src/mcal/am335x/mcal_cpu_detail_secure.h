///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_DETAIL_SECURE_2014_06_12_H_
  #define MCAL_CPU_DETAIL_SECURE_2014_06_12_H_

  namespace mcal
  {
    namespace cpu
    {
      namespace detail
      {
        void init();

        class secure final
        {
          static constexpr std::uint32_t tlb_base_address = UINT32_C(0x4030C000);

          static void invalidate_caches            ();
          static void clear_branch_prediction_array();
          static void invalidate_tlb               ();
          static void setup_domain_access_control  ();
          static void fill_tlb_entries             ();
          static void enable_mmu                   ();
          static void enable_branch_prediction     ();
          static void enable_caches                ();

          friend void mcal::cpu::detail::init();
        };
      }
    }
  } // namespace mcal::cpu::detail

#endif // MCAL_CPU_DETAIL_SECURE_2014_06_12_H_
