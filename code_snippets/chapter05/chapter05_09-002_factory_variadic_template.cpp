///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_09-002_factory_variadic_template.cpp

#include <cstddef>
#include <cstdint>
#include <iostream>

template<typename type_to_make,
         typename ...parameters>
type_to_make* factory(void* mem,
                      parameters... params)
{
  // Construct a new pointer of kind type_to_make
  // with the placement-new operator
  // and a parameter pack argument.

  type_to_make* p = new(mem) type_to_make(params...);

  return p;
}

class something_else
{
public:
  explicit something_else(const int M = 0,
                          const int N = 0)
    : m(M),
      n(N)
  {
    static_cast<void>(m);
    static_cast<void>(n);
  }

  ~something_else() = default;

  void do_something_else() const
  {
    std::cout << "In member function do_something_else(...)" << std::endl;
  }

private:
  const int m;
  const int n;
};

extern void* pool;

something_else* p_else { factory<something_else>(pool, 12, 34) };

auto main() -> int;

auto main() -> int
{
  p_else->do_something_else();
}

// Consider the buffer and pool pointer to be in another file.
std::uint8_t buffer[std::size_t { UINT16_C(256) }];

void* pool { reinterpret_cast<void*>(&buffer[std::size_t { UINT8_C(0) }]) };
