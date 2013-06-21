
#ifndef _CP15_2013_06_21_H_
  #define _CP15_2013_06_21_H_

  #include <cstdint>

  extern "C" void CP15DCacheCleanBuff(std::uint32_t bufPtr, std::uint32_t size);
  extern "C" void CP15ICacheFlushBuff(std::uint32_t bufPtr, std::uint32_t size);
  extern "C" void CP15ICacheDisable();
  extern "C" void CP15DCacheDisable();
  extern "C" void CP15ICacheEnable();
  extern "C" void CP15DCacheEnable();
  extern "C" void CP15DCacheCleanFlush();
  extern "C" void CP15ICacheFlush();
  extern "C" void CP15Ttb0Set(std::uint32_t ttb);
  extern "C" void CP15TlbInvalidate();
  extern "C" void CP15MMUDisable();
  extern "C" void CP15MMUEnable();
  extern "C" void CP15VectorBaseAddrSet(std::uint32_t addr);
  extern "C" void CP15BranchPredictorInvalidate();
  extern "C" void CP15BranchPredictionEnable();
  extern "C" void CP15BranchPredictionDisable();
  extern "C" void CP15DomainAccessClientSet();

#endif // _CP15_2013_06_21_H_
