///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
  #define _UTIL_CIRCULAR_BUFFER_2007_11_22_H_

  #include <cstddef>

  namespace util
  {
    template<typename T, const std::size_t N>
    class circular_buffer
    {
    public:
      typedef T value_type;
      typedef value_type* iterator;
      typedef std::size_t size_type;

      circular_buffer() : in_ptr(buffer),
                          out_ptr(buffer) { }

      constexpr size_type size() const { return N; }

      bool empty() const { return (in_ptr == out_ptr); }

      size_type inque() const
      {
        const bool is_wrap = (in_ptr >= out_ptr);

        return (is_wrap ? size_type(in_ptr - out_ptr)
                        : size() - size_type(out_ptr - in_ptr));
      }

      void flush()
      {
        in_ptr = out_ptr = buffer;
      }

      void in(const value_type by)
      {
        *in_ptr = by;

        ++in_ptr;

        if(in_ptr >= (buffer + N))
        {
          in_ptr = buffer;
        }
      }

      value_type out()
      {
        if(empty())
        {
          return value_type(0);
        }
        else
        {
          const value_type by = *out_ptr;

          ++out_ptr;

          if(out_ptr >= (buffer + N))
          {
            out_ptr = buffer;
          }

          return by;
        }
      }

    private:
      value_type buffer[N];
      iterator in_ptr;
      iterator out_ptr;
    };
  }

#endif // _UTIL_CIRCULAR_BUFFER_2007_11_22_H_
