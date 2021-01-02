///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_BASELEXICAL_CAST_2020_06_28_H_
  #define UTIL_BASELEXICAL_CAST_2020_06_28_H_

  #include <cstddef>
  #include <cstdint>
  #include <iterator>

  namespace util {

  template<typename UnsignedIntegerType,
           typename OutputIterator,
           const std::uint_fast8_t BaseRepresentation = 10U,
           const bool UpperCase = true>
  OutputIterator baselexical_cast(const UnsignedIntegerType& u, OutputIterator OutFirst)
  {
    using unsigned_integer_type = UnsignedIntegerType;
    using output_value_type     = typename std::iterator_traits<OutputIterator>::value_type;

    unsigned_integer_type x(u);

    std::ptrdiff_t index = 0;

    do
    {
      for(std::ptrdiff_t j = index; j >= 0; --j)
      {
        *(OutFirst + (j + 1)) = *(OutFirst + j);
      }

      ++index;

      output_value_type c(x % BaseRepresentation);

      x /= BaseRepresentation;

      if(c <= (output_value_type) 9)
      {
        c = c + (output_value_type) '0';
      }
      else if((c >= (output_value_type) 0xA) && (c <= (output_value_type) 0xF))
      {
        c =   (UpperCase ? (output_value_type) 'A' : (output_value_type) 'a')
            + (output_value_type) (c - (output_value_type) 0xA);
      }

      *OutFirst = c;
    }
    while(x != 0U);

    return (OutputIterator) (OutFirst + index);
  }

  } // namespace util

#endif // UTIL_BASELEXICAL_CAST_2020_06_28_H_
