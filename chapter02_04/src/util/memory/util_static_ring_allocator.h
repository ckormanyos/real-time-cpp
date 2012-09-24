#ifndef _UTIL_STATIC_RING_ALLOCATOR_2010_02_23_H_
  #define _UTIL_STATIC_RING_ALLOCATOR_2010_02_23_H_

  #include <memory>
  #include "util_ring_allocator_base.h"

  namespace util
  {
    template<typename T>
    class static_ring_allocator;

    template<>
    class static_ring_allocator<void> : public ring_allocator_base
    {
    public:
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template <class U>
      struct rebind { typedef static_ring_allocator<U> other; };
    };

    template<typename T>
    class static_ring_allocator : public ring_allocator_base
    {
    public:
      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;
      typedef std::ptrdiff_t    difference_type;

      static_ring_allocator() throw() { }

      static_ring_allocator(const static_ring_allocator&) throw() { }

      template <class U>
      static_ring_allocator(const static_ring_allocator<U>&) throw() { }

      template<class U> 
      struct rebind { typedef static_ring_allocator<U> other; };

      size_type max_size(void) const throw()
      {
        return buffer_size / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type num,
                       static_ring_allocator<void>::const_pointer = 0U)
      {
        void* p = do_allocate(num * sizeof(value_type));
        return static_cast<pointer>(p);
      }

      void construct(pointer p, const value_type& x)
      {
        new(static_cast<void*>(p)) value_type(x); 
      }

      void destroy(pointer p) { p->~value_type(); }

      void deallocate(pointer, size_type) { }
    };
  }

#endif // _UTIL_STATIC_RING_ALLOCATOR_2010_02_23_H_
