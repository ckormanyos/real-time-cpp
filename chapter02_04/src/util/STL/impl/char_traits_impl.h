#ifndef _CHAR_TRAITS_IMPL_2010_02_23_H_
  #define _CHAR_TRAITS_IMPL_2010_02_23_H_

  #include <string.h>

  // Implement some of std::char_traits for compilers that do not yet support it.

  namespace std
  {
    template<typename T>
    class char_traits
    {
    public:
      static std::size_t length(const T* first)
      {
        const T* p = first;

        while(*p != T('\0'))
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
