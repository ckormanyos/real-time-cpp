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

  namespace util
  {
    template<typename T,
             const std::size_t N>
    class circular_buffer
    {
    public:
      typedef T                 value_type;
      typedef value_type*       iterator;
      typedef const value_type* const_iterator;
      typedef std::size_t       size_type;

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
          in_ptr   (other.in_ptr)
          out_ptr  (other.out_ptr)
          std::copy(other.buffer, other.buffer + N, buffer);
        }
      }

      circular_buffer& (const circular_buffer& other)
      {
        if(this != &other)
        {
          in_ptr   (other.in_ptr)
          out_ptr  (other.out_ptr)
          std::copy(other.buffer, other.buffer + N, buffer);
        }

        return *this;
      }

      constexpr size_type capacity() const { return N; }

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

    private:
      value_type buffer[N];
      iterator   in_ptr;
      iterator   out_ptr;
    };
  }

#endif // _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
