///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
  #define _UTIL_CIRCULAR_BUFFER_2007_11_22_H_

  #include <algorithm>
  #include <cstddef>
  #include <iterator>

  namespace util
  {
    template<typename T,
             const std::size_t N>
    class circular_buffer
    {
    public:
      typedef T                 value_type;
      typedef       value_type* iterator;
      typedef const value_type* const_iterator;
      typedef       std::size_t size_type;
      typedef       value_type& reference;
      typedef const value_type& const_reference;

      circular_buffer(const T& value        = T(),
                      const size_type count = size_type(0U)) : in_ptr (buffer),
                                                               out_ptr(buffer)
      {
        const size_type the_count = (std::min)(N, count);

        std::fill(in_ptr, in_ptr + the_count, value);

        out_ptr += the_count;
      }

      circular_buffer(const circular_buffer& other)
      {
        if(this != &other)
        {
          in_ptr   (other.in_ptr);
          out_ptr  (other.out_ptr);
          std::copy(other.buffer, other.buffer + N, buffer);
        }
      }

      circular_buffer& operator=(const circular_buffer& other)
      {
        if(this != &other)
        {
          in_ptr   (other.in_ptr);
          out_ptr  (other.out_ptr);
          std::copy(other.buffer, other.buffer + N, buffer);
        }

        return *this;
      }

      size_type capacity() const { return N; }

      bool empty() const { return (in_ptr == out_ptr); }

      size_type size() const
      {
        const bool is_wrap = (in_ptr >= out_ptr);

        return (is_wrap ? size_type(in_ptr - out_ptr)
                        : size() - size_type(out_ptr - in_ptr));
      }

      void clear()
      {
        in_ptr  = buffer;
        out_ptr = buffer;
      }

      void push(const value_type value)
      {
        *in_ptr = value;

        ++in_ptr;

        if(in_ptr >= (buffer + N))
        {
          in_ptr = buffer;
        }
      }

      value_type pop()
      {
        if(empty())
        {
          return value_type(0);
        }
        else
        {
          const value_type value = *out_ptr;

          ++out_ptr;

          if(out_ptr >= (buffer + N))
          {
            out_ptr = buffer;
          }

          return value;
        }
      }

      reference& front()
      {
        if(empty())
        {
          return buffer[0U];
        }
        else
        {
          return ((in_ptr == buffer) ? buffer[N - 1U] : *(in_ptr - 1U));
        }
      }

      reference& back()
      {
        if(empty())
        {
          return buffer[0U];
        }
        else
        {
          return ((out_ptr == buffer) ? buffer[N - 1U] : *(out_ptr - 1U));
        }
      }

      const_reference& front() const
      {
        if(empty())
        {
          return buffer[0U];
        }
        else
        {
          return ((in_ptr == buffer) ? buffer[N - 1U] : *(in_ptr - 1U));
        }
      }

      const_reference& back() const
      {
        if(empty())
        {
          return buffer[0U];
        }
        else
        {
          return ((out_ptr == buffer) ? buffer[N - 1U] : *(out_ptr - 1U));
        }
      }

    private:
      value_type buffer[N];
      iterator   in_ptr;
      iterator   out_ptr;
    };
  }

  /*
  #include <cstdint>
  #include <util/utility/util_circular_buffer.h>

  void do_something();

  void do_something()
  {
    typedef util::circular_buffer<std::uint8_t, 8U> buffer_type;

    buffer_type data;

    const buffer_type::value_type the_value(0x55U);

    data.push(the_value);
    data.push(the_value);
  }
  */

#endif // _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
