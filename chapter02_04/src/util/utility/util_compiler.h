#ifndef _UTIL_COMPILER_2006_04_10_H_
  #define _UTIL_COMPILER_2006_04_10_H_

  // Create a GCC version number such as (40000 + 600 + 1 = 40601) for 4.6.1.

  #if defined(__GNUC__)
    #define GCC_VERSION  (  (__GNUC__       * 10000) \
                          + (__GNUC_MINOR__ *   100) \
                          +  __GNUC_PATCHLEVEL__)
  #endif

#endif // _UTIL_COMPILER_2006_04_10_H_
