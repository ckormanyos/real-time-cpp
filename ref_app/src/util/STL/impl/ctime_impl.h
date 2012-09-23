#ifndef _CTIME_IMPL_2012_06_01_H_
  #define _CTIME_IMPL_2012_06_01_H_

  #include <time.h>

  // Implement std::time_t of <ctime> for compilers that do not yet support it.

  namespace std
  {
    typedef ::time_t time_t;
  }

#endif // _CTIME_IMPL_2012_06_01_H_
