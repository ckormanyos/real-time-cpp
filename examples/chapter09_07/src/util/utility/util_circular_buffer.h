///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
  #define _UTIL_CIRCULAR_BUFFER_2007_11_22_H_

  #include <algorithm>
  #include <cstddef>

  namespace util
  {
    // TBD: We need to define a custom iterator class in order
    // to provide proper iterator support for circular_buffer.

    template<typename T,
             const std::size_t N>
    class circular_buffer
    {
    public:
      typedef T                 value_type;
      typedef       value_type* pointer;
      typedef const value_type* const_pointer;
      typedef       std::size_t size_type;
      typedef       value_type& reference;
      typedef const value_type& const_reference;

      circular_buffer(
          const T& value        = value_type(),
          const size_type count = size_type(0U))
        : in_ptr (buffer),
          out_ptr(buffer)
      {
        const size_type the_count =
          (std::min)(N, count);

        std::fill(in_ptr,
                  in_ptr + the_count,
                  value);

        in_ptr += the_count;
      }

      circular_buffer(const circular_buffer& other)
        : in_ptr (other.in_ptr),
          out_ptr(other.out_ptr)
      {
        std::copy(other.buffer,
                  other.buffer + N,
                  buffer);
      }

      circular_buffer& operator=(
          const circular_buffer& other)
      {
        if(this != &other)
        {
          in_ptr   (other.in_ptr);
          out_ptr  (other.out_ptr);
          std::copy(other.buffer,
                    other.buffer + N,
                    buffer);
        }

        return *this;
      }

      size_type capacity() const { return N; }

      bool empty() const
      {
        return (in_ptr == out_ptr);
      }

      size_type size() const
      {
        const bool is_wrap = (in_ptr < out_ptr);

        return size_type((is_wrap == false)
          ? size_type(in_ptr - out_ptr)
          : N - size_type(out_ptr - in_ptr));
      }

      void clear()
      {
        in_ptr  = buffer;
        out_ptr = buffer;
      }

      void in(const value_type value)
      {
        if(in_ptr >= (buffer + N))
        {
          in_ptr = buffer;
        }

        *in_ptr = value;

        ++in_ptr;
      }

      value_type out()
      {
        if(out_ptr >= (buffer + N))
        {
          out_ptr = buffer;
        }

        const value_type value = *out_ptr;

        ++out_ptr;

        return value;
      }

      reference front()
      {
        return ((out_ptr >= (buffer + N))
                  ? buffer[N - 1U]
                  : *out_ptr);
      }

      const_reference front() const
      {
        return ((out_ptr >= (buffer + N))
                  ? buffer[N - 1U]
                  : *out_ptr);
      }

      reference back()
      {
        return ((in_ptr  >= (buffer + N))
                  ? buffer[N - 1U]
                  : *in_ptr);
      }

      const_reference back() const
      {
        return ((in_ptr  >= (buffer + N))
                  ? buffer[N - 1U]
                  : *in_ptr);
      }

    private:
      value_type buffer[N];
      pointer    in_ptr;
      pointer    out_ptr;
    };

    template<typename T>
    class circular_buffer<T, std::size_t(1U)>
    {
    public:
      typedef T                 value_type;
      typedef       value_type* pointer;
      typedef const value_type* const_pointer;
      typedef       std::size_t size_type;
      typedef       value_type& reference;
      typedef const value_type& const_reference;

      circular_buffer(
          const T& value        = value_type(),
          const size_type count = size_type(0U))
      {
        if(count > size_type(0U))
        {
          data     = value;
          has_data = true;
        }
        else
        {
          data = value_type();

          has_data = false;
        }
      }

      circular_buffer(const circular_buffer& other)
        : data    (other.data),
          has_data(other.has_data)
      {
      }

      circular_buffer& operator=(
          const circular_buffer& other)
      {
        if(this != &other)
        {
          data = other.data;

          has_data = other.has_data;
        }

        return *this;
      }

      size_type capacity() const { return size_type(1U); }

      bool empty() const
      {
        return (has_data == false);
      }

      size_type size() const
      {
        return size_type(has_data ? 1U : 0U);
      }

      void clear()
      {
        has_data = false;
      }

      void in(const value_type value)
      {
        has_data = true;

        data = value;
      }

      value_type out()
      {
        has_data = false;

        return data;
      }

      reference front()
      {
        return data;
      }

      const_reference front() const
      {
        return data;
      }

      reference back()
      {
        return data;
      }

      const_reference back() const
      {
        return data;
      }

    private:
      value_type data;
      bool       has_data;
    };
  }

  /*
  #include <util/utility/util_circular_buffer.h>

  void do_something();

  void do_something()
  {
    typedef util::circular_buffer<unsigned, 3U> circular_buffer_type;

    circular_buffer_type             data;
    circular_buffer_type::size_type  size;
    circular_buffer_type::value_type value;

    data.in(1U);
    size = data.size();
    data.in(2U);
    size = data.size();
    data.in(3U);
    size = data.size();

    value = data.out();
    size = data.size();
    value = data.out();
    size = data.size();
    value = data.out();
    size = data.size();

    data.in(101U);
    size = data.size();
    data.in(102U);
    size = data.size();

    value = data.out();
    size = data.size();
    value = data.out();
    size = data.size();

    volatile unsigned debug = 0U;
  }
  */

#endif // _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
