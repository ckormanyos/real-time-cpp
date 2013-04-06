#ifndef _CTIME_IMPL_2012_06_01_H_
  #define _CTIME_IMPL_2012_06_01_H_

  // Implement std::time_t of <ctime> for compilers that do not yet support it.

  // TBD: If the compiler has <time.h>, then include it for ::time_t.
  typedef unsigned int time_t;

  namespace std
  {
    typedef ::time_t time_t;
  }

#endif // _CTIME_IMPL_2012_06_01_H_
