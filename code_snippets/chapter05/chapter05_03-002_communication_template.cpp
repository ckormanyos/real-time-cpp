///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_03-002_communication_template.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>

class communication
{
public:
  virtual ~communication() = default;

  virtual auto send_byte(const std::uint8_t b) const -> bool
  {
    // Simulate sending a byte on the PC.
    std::cout << "Sending: "
              << std::hex
              << std::showbase
              << unsigned(b)
              << std::endl;

    const auto cout_state = std::cout.rdstate();

    const auto failed_state =
      static_cast<std::ios::iostate>
      (
        cout_state & static_cast<std::ios::iostate>(std::ios::badbit | std::ios::failbit)
      );

    const auto send_byte_is_ok = (failed_state == static_cast<std::ios::iostate>(0));

    return send_byte_is_ok;
  }

  // Add a template send_uint function.
  template<typename unsigned_type>
  auto send_uint(const unsigned_type& u) const -> bool
  {
    constexpr auto type_is_signed = std::numeric_limits<unsigned_type>::is_signed;

    // Ensure that unsigned_type is unsigned.
    static_assert(type_is_signed == false,
                  "error: type must be unsigned");

    constexpr std::size_t count =
      static_cast<int>
      (
        std::numeric_limits<unsigned_type>::digits / static_cast<int>(INT8_C(8))
      );

    auto i = std::size_t { };

    for(i = static_cast<std::size_t>(UINT8_C(0)); i < count; ++i)
    {
      const auto by = static_cast<std::uint8_t>(u >> (i * static_cast<unsigned>(UINT8_C(8))));

      if(send_byte(by) == false)
      {
        break;
      }
    }

    return (i == count);
  }

  auto recv_byte() const -> std::uint8_t
  {
    return recv_buffer;
  }

private:
  std::uint8_t recv_buffer { };
};

auto main() -> int;

auto main() -> int
{
  communication com;

  const bool send_uint_is_ok = com.send_uint(static_cast<std::uint32_t>(UINT32_C(0x11223344)));

  std::cout << "Result of send_uint: "
            << std::boolalpha
            << send_uint_is_ok
            << std::endl;
}
