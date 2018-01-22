// chapter05_12-001_prime_number.cpp

#include <cstdint>
#include <iostream>

template<typename T>
constexpr T prime_number = T(541);

constexpr std::uint16_t p =
  prime_number<std::uint16_t>;

int main()
{
  std::cout << p << std::endl;
}
