#ifndef _UTIL_RELOCATABLE_RING_ALLOCATOR_BASE_2010_02_23_H_
  #define _UTIL_RELOCATABLE_RING_ALLOCATOR_BASE_2010_02_23_H_

  #include "util_ring_allocator_base.h"

  namespace util
  {
    class relocatable_ring_allocator_base : public ring_allocator_base
    {
    public:
      static void relocate(std::uint8_t* pbuf, const size_type size);
    };
  }

#endif // _UTIL_RELOCATABLE_RING_ALLOCATOR_BASE_2010_02_23_H_
