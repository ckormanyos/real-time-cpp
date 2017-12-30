///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_RING_ALLOCATOR_2010_02_23_H_
  #define _UTIL_RING_ALLOCATOR_2010_02_23_H_

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  #include <util/utility/util_alignas.h>

  namespace util
  {
    class ring_allocator_base
    {
    public:
      typedef std::size_t    size_type;
      typedef std::ptrdiff_t difference_type;

      virtual ~ring_allocator_base();

    protected:
      ring_allocator_base() throw() { }

      ring_allocator_base(const ring_allocator_base&) throw() { }

      // The ring allocator's default buffer size.
      static const size_type buffer_size = 64U;

      // The ring allocator's buffer type.
      struct buffer_type
      {
        std::uint8_t data[buffer_size];
      };

      // The ring allocator's memory allocation.
      template<const std::uint_fast8_t inner_buffer_alignment>
      static void* do_allocate(const size_type size)
      {
        ALIGNAS(16) static buffer_type buffer;
        static std::uint8_t* get_ptr = buffer.data;

        // Get the newly allocated pointer.
        std::uint8_t* p = get_ptr;

        // Increment the get-pointer for the next allocation.
        // Be sure to handle the inner-buffer alignment.
        const std::uint_fast8_t align_increment  = inner_buffer_alignment - std::uint_fast8_t(size % inner_buffer_alignment);
        const size_type         buffer_increment = size + align_increment;

        get_ptr += buffer_increment;

        // Does this attempted allocation overflow the capacity of the buffer?
        const bool is_overflow = (get_ptr >= (buffer.data + buffer_size));

        if(is_overflow)
        {
          // The buffer has overflowed.

          // Check if the requested size fits in the buffer.
          if(buffer_increment <= buffer_size)
          {
            // The requested size fits in the buffer.

            // Reset the allocated pointer to the bottom of the buffer
            // and increment the next get-pointer.
            p       = buffer.data;
            get_ptr = buffer.data + buffer_increment;
          }
          else
          {
            // The requested size exceeds the capacity of the buffer.

            // Set the return value of the failed allocation to nullptr
            // and reset the get-pointer to its value before the allocation
            // attempt.
            p       = nullptr;
            get_ptr = get_ptr - buffer_increment;
          }
        }

        return static_cast<void*>(p);
      }

    private:
      ring_allocator_base& operator=(const ring_allocator_base&);
    };

    ring_allocator_base::~ring_allocator_base() { }

    // Global comparison operators (required by the standard).
    inline bool operator==(const ring_allocator_base&,
                           const ring_allocator_base&) throw()
    {
      return true;
    }

    inline bool operator!=(const ring_allocator_base&,
                           const ring_allocator_base&) throw()
    {
      return false;
    }

    template<typename T,
             const std::uint_fast8_t inner_buffer_alignment = UINT8_C(4)>
    class ring_allocator;

    template<const std::uint_fast8_t inner_buffer_alignment>
    class ring_allocator<void, inner_buffer_alignment> : public ring_allocator_base
    {
    public:
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template<typename U>
      struct rebind { typedef ring_allocator<U, inner_buffer_alignment> other; };
    };

    template<typename T,
             const std::uint_fast8_t inner_buffer_alignment>
    class ring_allocator : public ring_allocator_base
    {
    public:
      static_assert(sizeof(T) <= buffer_size,
                    "The size of the allocation object can not exceed the buffer size.");

      static_assert(inner_buffer_alignment <= buffer_size,
                    "The granularity of the inner-buffer alignment can not exceed the buffer size.");

      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;

      ring_allocator() throw() { }

      ring_allocator(const ring_allocator&) throw() : ring_allocator_base(ring_allocator()) { }

      template <typename U>
      ring_allocator(const ring_allocator<U, inner_buffer_alignment>&) throw() { }

      template<typename U> 
      struct rebind { typedef ring_allocator<U, inner_buffer_alignment> other; };

      size_type max_size() const throw()
      {
        return buffer_size / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type count,
                       typename ring_allocator<void, inner_buffer_alignment>::const_pointer = nullptr)
      {
        const size_type chunk_size = count * sizeof(value_type);

        void* p = do_allocate<inner_buffer_alignment>(chunk_size);

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

#endif // _UTIL_RING_ALLOCATOR_2010_02_23_H_

/*
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(_MSC_VER)
#include <iostream>
#endif
#include <iterator>
#include <numeric>
#include <vector>
#include <mcal/mcal.h>
#include <util/utility/util_time.h>
#include <util/memory/util_ring_allocator.h>

namespace app
{
  namespace led
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  typedef util::timer<std::uint32_t> timer_type;

  timer_type app_led_timer(timer_type::seconds(1U));
}

void app::led::task_init()
{
  mcal::led::led0.toggle();
}

std::uint8_t counter;

typedef util::ring_allocator<std::uint8_t, UINT8_C(2)> allocator_type;
typedef std::vector<std::uint8_t, allocator_type>      vector_type;

vector_type v;

void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    v.clear();

    v.push_back(counter + UINT8_C(0));
    v.push_back(counter + UINT8_C(1));
    v.push_back(counter + UINT8_C(2));

    const bool vector_size_is_ok    = (v.size() == vector_type::size_type(3U));
    const bool vector_content_is_ok = (std::accumulate(v.cbegin(), v.cend(), std::uint8_t(0U)) == std::uint8_t(std::uint8_t(counter * UINT8_C(3)) + UINT8_C(3)));

    counter += std::uint8_t(v.size());

    if(vector_size_is_ok && vector_content_is_ok)
    {
      app_led_timer.start_interval(timer_type::seconds(1U));

      mcal::led::led0.toggle();

      #if defined(_MSC_VER)
      std::cout << unsigned(counter) << std::endl;
      #endif
    }
  }
}
*/
