///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_21-001_mersenne_twister_19937.cpp

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

namespace local
{
  // Create a custom random device for seeding the pseudo-random number generator.
  // Use a custom random device because the default is allowed to repeat values.
  class my_custom_random_device
  {
  public:
     typedef std::uint32_t result_type;

     explicit my_custom_random_device(const std::string& token = "")
     {
       static_cast<void>(token.empty());

       this->operator()();
     }

     static result_type (min)() { return (std::numeric_limits<result_type>::min)(); }
     static result_type (max)() { return (std::numeric_limits<result_type>::max)(); }

     double entropy() const { return 4.0; }

     result_type operator()()
     {
       // Use the high resolution clock to create the seed.
       const auto start = std::chrono::time_point<std::chrono::high_resolution_clock>();
       const auto end   = std::chrono::high_resolution_clock::now();

       const std::chrono::duration<double> seed = (end - start);

       // Obtain the seed as an integral value.
       // This involves extracting the mantissa of the seed as a double
       // and subsequently multiplying this value with (10.0^precision).
       int n_exp;

       const result_type seed_as_integral_value =
         result_type(std::frexp(seed.count(), &n_exp) * std::pow(10.0, std::numeric_limits<double>::digits10));

       // We now have a unique seed expressed as an integral value.
       return seed_as_integral_value;
     }

     my_custom_random_device(const my_custom_random_device&) = delete;
     void operator=(const my_custom_random_device&) = delete;
  };
}

void do_something()
{
  static local::my_custom_random_device               my_random_device;
  static std::mt19937                                 my_generator(my_random_device());
  static std::uniform_int_distribution<std::uint16_t> my_distribution(1, 1023);

  // Generate 3 pseudo-random numbers.
  const std::uint16_t random_numbers[3U] =
  {
    my_distribution(my_generator),
    my_distribution(my_generator),
    my_distribution(my_generator)
  };

  std::cout << std::setw(5) << random_numbers[0U] << ", ";
  std::cout << std::setw(5) << random_numbers[1U] << ", ";
  std::cout << std::setw(5) << random_numbers[2U] << std::endl;
}

int main()
{
  // Generate 10 sequences of 3 pseudo-random numbers.
  for(std::uint_fast8_t i = 0U; i < 10U; ++i)
  {
    do_something();
  }
}
