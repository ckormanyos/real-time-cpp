///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AVR_ATOMIC_2012_01_09_H_
  #define AVR_ATOMIC_2012_01_09_H_

  namespace std
  {
    template<typename atomic_integral_type>
    atomic_integral_type atomic_load(const atomic_integral_type*);

    template<typename atomic_integral_type>
    atomic_integral_type atomic_load(const volatile atomic_integral_type*);

    template<typename atomic_integral_type>
    void atomic_store(atomic_integral_type*, atomic_integral_type);

    template<typename atomic_integral_type>
    void atomic_store(volatile atomic_integral_type*, atomic_integral_type);
  }

  struct atomic_helper
  {
    template<typename atomic_integral_type>
    friend atomic_integral_type std::atomic_load(const atomic_integral_type*);

    template<typename atomic_integral_type>
    friend atomic_integral_type std::atomic_load(const volatile atomic_integral_type*);

    template<typename atomic_integral_type>
    friend void std::atomic_store(atomic_integral_type*, atomic_integral_type);

    template<typename atomic_integral_type>
    friend void std::atomic_store(volatile atomic_integral_type*, atomic_integral_type);

    static void enable_all_interrupts () { asm volatile("sei"); }
    static void disable_all_interrupts() { asm volatile("cli"); }
  };

#endif // AVR_ATOMIC_2012_01_09_H_
