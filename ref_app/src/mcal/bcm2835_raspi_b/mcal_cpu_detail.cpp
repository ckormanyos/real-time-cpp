#include <cstdint>

#include <mcal_cpu_detail_secure.h>

void mcal::cpu::detail::init()
{
  mcal::cpu::detail::secure::initialize_vfp_unit();
  mcal::cpu::detail::secure::clear_branch_prediction_array();
  mcal::cpu::detail::secure::fill_tlb_entries();
  mcal::cpu::detail::secure::enable_mmu();
  mcal::cpu::detail::secure::enable_branch_prediction();
  mcal::cpu::detail::secure::enable_caches();
}
