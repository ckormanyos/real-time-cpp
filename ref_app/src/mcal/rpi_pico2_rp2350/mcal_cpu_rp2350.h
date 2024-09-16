/******************************************************************************************
  Filename    : Cpu.h
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Cpu initialization header file for RP2350
  
******************************************************************************************/
#ifndef MCAL_CPU_RP2350_2024_09_16_H
  #define MCAL_CPU_RP2350_2024_09_16_H

  #include <cstdint>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  //=============================================================================
  // Defines
  //=============================================================================
  #define CPU_CORE0_ID   0UL
  #define CPU_CORE1_ID   1UL

  #define MULTICORE_SYNC_MASK  (std::uint32_t)((1UL << CPU_CORE0_ID) | (1UL << CPU_CORE1_ID))

  //=============================================================================
  // Functions prototype
  //=============================================================================
  auto RP2350_MulticoreSync(std::uint32_t CpuId) -> void;
  auto RP2350_StartCore1(void) -> bool;

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_CPU_RP2350_2024_09_16_H
