#ifndef _CPU_2013_06_21_H_
  #define _CPU_2013_06_21_H_

  #include <cstdint>

  extern "C" void CPUSwitchToUserMode();
  extern "C" void CPUSwitchToPrivilegedMode();

  /****************************************************************************/
  /*
  ** Functions used internally
  */
  extern "C" void CPUAbortHandler();
  extern "C" void CPUirqd();
  extern "C" void CPUirqe();
  extern "C" void CPUfiqd();
  extern "C" void CPUfiqe();
  extern "C" std::uint32_t CPUIntStatus();

#endif // _CPU_2013_06_21_H_
