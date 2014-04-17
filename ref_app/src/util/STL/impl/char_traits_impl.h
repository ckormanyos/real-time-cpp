///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CHAR_TRAITS_IMPL_2010_02_23_H_
  #define _CHAR_TRAITS_IMPL_2010_02_23_H_

  #include <string.h>

  // Implement some of std::char_traits for compilers that do not yet support it.

  namespace std
  {
    template<typename char_type>
    class char_traits
    {
    public:
      static std::size_t length(const char_type* first)
      {
        const char_type* p = first;

        while(*p != char_type('\0'))
        {
          ++p;
        }

        return (std::size_t) (p - first);
      }
    };

    template<>
    class char_traits<char>
    {
    public:
      static std::size_t length(const char* first)
      {
        return ::strlen(first);
      }
    };
  }

#endif // _CHAR_TRAITS_IMPL_2010_02_23_H_
