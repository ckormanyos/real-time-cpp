///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_11-003_tuple_things_metaprog_alias.cpp

#include <iostream>
#include <tuple>

class apple
{
public:
  apple() = default;
  ~apple() = default;

  auto setup() const -> void
  {
    std::cout << "In apple::setup()" << std::endl;
  }
};

class car
{
public:
  car() = default;
  ~car() = default;

  auto setup() const -> void
  {
    std::cout << "In car::setup()" << std::endl;
  }
};

class tiger
{
public:
  tiger() = default;
  ~tiger() = default;

  auto setup() const -> void
  {
    std::cout << "In tiger::setup()" << std::endl;
  }
};

template<const unsigned N,
         const unsigned M = 0U>
struct tuple_setup_each
{
  template<typename tuple_type>
  static auto setup(tuple_type& t) -> void
  {
    // Setup the M'th object and the next higher one.
    std::get<M>(t).setup();
    tuple_setup_each<N, M + 1U>::setup(t);
  }
};

template<const unsigned N>
struct tuple_setup_each<N, N>
{
  template<typename tuple_type>
  static auto setup(tuple_type&) -> void { }
};

void do_something();

void do_something()
{
  // Use a convenient type definition
  // for the tuple_type.
  using tuple_type =
    std::tuple<apple, car, tiger>;

  tuple_type things;

  // Use tuple_size to get the size of the things.
  constexpr unsigned the_size
    = std::tuple_size<tuple_type>::value;

  // Setup the things.
  tuple_setup_each<the_size>::setup(things);
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
