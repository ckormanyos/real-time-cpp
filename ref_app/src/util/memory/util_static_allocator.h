///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_STATIC_ALLOCATOR_2010_02_23_H_
  #define _UTIL_STATIC_ALLOCATOR_2010_02_23_H_

  #include <memory>

  namespace util
  {
    class static_allocator_base
    {
    public:
      typedef std::size_t size_type;

    protected:
      static_allocator_base() { }

      // The static_allocator's default buffer size.
      static const size_type buffer_size = 8U;

      // The static_allocator's memory allocation.
      static void* do_allocate(const size_type size);
    };

    // Global comparison operators (required by the standard).
    inline bool operator==(const static_allocator_base&,
                           const static_allocator_base&) throw()
    {
      return true;
    }

    inline bool operator!=(const static_allocator_base&,
                           const static_allocator_base&) throw()
    {
      return false;
    }

    template<typename T>
    class static_allocator;

    template<>
    class static_allocator<void> : public static_allocator_base
    {
    public:
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template<typename U>
      struct rebind { typedef static_allocator<U> other; };
    };

    template<typename T>
    class static_allocator : public static_allocator_base
    {
    public:
      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;
      typedef std::ptrdiff_t    difference_type;

      static_allocator() throw() { }

      static_allocator(const static_allocator&) throw() { }

      template <typename U>
      static_allocator(const static_allocator<U>&) throw() { }

      template<typename U> 
      struct rebind { typedef static_allocator<U> other; };

      size_type max_size() const throw()
      {
        return buffer_size / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type count,
                       static_allocator<void>::const_pointer = nullptr)
      {
        const size_type chunk_size = count * sizeof(value_type);

        void* p = do_allocate(chunk_size);

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

#endif // _UTIL_STATIC_ALLOCATOR_2010_02_23_H_
