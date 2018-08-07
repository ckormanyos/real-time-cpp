///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_09-002_factory_variadic_template.cpp

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
  something_else(const int M,
                 const int N) : m(M),
                                n(N) { }

  virtual ~something_else() = default;

  void do_something_else() const
  {
    std::cout << "In member function do_something_else(...)" << std::endl;
  }

private:
  const int m;
  const int n;
};

extern void* pool;

something_else* p_else
  = factory<something_else>(pool, 12, 34);

int main()
{
  p_else->do_something_else();
}

// Consider the buffer and pool pointer to be in another file.
std::uint8_t buffer[256U];

void* pool = reinterpret_cast<void*>(&buffer[0U]);
