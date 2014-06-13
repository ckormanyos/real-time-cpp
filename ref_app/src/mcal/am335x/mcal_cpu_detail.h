///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_CPU_DETAIL_2014_06_12_H_
  #define _MCAL_CPU_DETAIL_2014_06_12_H_

  #include <cstdint>

  namespace mcal
  {
    namespace cpu
    {
      namespace detail
      {
        void initialize_the_neon_coprocessor_and_the_vfp();
        void invalidate_the_caches                      ();
        void clear_the_branch_prediction_array          ();
        void invalidate_the_tlb                         ();
        void setup_the_domain_access_control            ();
        void fill_the_tlb                               ();
        void set_the_tlb_base_address                   ();
        void enable_the_mmu                             ();
        void enable_branch_prediction                   ();
        void enable_the_caches                          ();
        void load_the_address_of_the_nmi_interrupt_table();
        void switch_to_user_mode                        ();
      }
    }
  } // namespace mcal::cpu::detail

#endif // _MCAL_CPU_DETAIL_2014_06_12_H_
