///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-002_nonconst_com_class.cpp

#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>

#define __attribute__(attr)

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_tbuf { };
    std::uint8_t dummy_register_rbuf { };
  }
}

extern "C"
auto com_recv_isr() -> void __attribute__((interrupt));

class communication
{
public:
  communication() = default;

  ~communication() = default;

  auto send_byte(const std::uint8_t by) const -> bool
  {
    // Transmit the byte.
    *tbuf = by;

    // Simulate the receive interrupt handler on the PC.
    com_recv_isr();

    return true;
  }

  auto recv_ready() const noexcept -> bool { return has_recv; }

  std::uint8_t recv_byte()
  {
    if(has_recv)
    {
      has_recv = false;

      recv_buf = *rbuf;

      return recv_buf;
    }

    return 0U;
  }

private:
  static std::uint8_t* tbuf;
  static std::uint8_t* rbuf;

  std::uint8_t recv_buf { };
  bool has_recv { };

  communication(const communication&) = delete;

  const communication& operator=(const communication&) = delete;

  friend auto com_recv_isr() -> void;
};

std::uint8_t* communication::tbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_tbuf);
std::uint8_t* communication::rbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_rbuf);

auto wakeup(const communication& com) -> bool // Emphasize: com is a comst reference.
{
  // Call the const send_byte function on a const reference.
  const bool result_send_is_ok { com.send_byte(UINT8_C(0x12)) };

  com_recv_isr();

  return result_send_is_ok;
}

auto login(communication& com) -> bool // Emohasize: com is a non-comst reference.
{
  const bool wakeup_is_ok = wakeup(com);

  if(wakeup_is_ok)
  {
    // Receive the byte.
    // If com were a const reference,
    // then there would be a compilation error
    // when calling com.recv_byte().

    const std::uint8_t the_byte { com.recv_byte() };

    // Do something with the_byte.
    std::cout << std::format("received byte: {:#02x}", static_cast<unsigned>(the_byte)) << std::endl;

    return (the_byte == 0x34U);
  }
  else
  {
    return false;
  }
}

namespace
{
  // Instantiate a non-constant communication instance.
  communication com { };
}

extern "C"
void com_recv_isr() __attribute__((interrupt))
{
  com.has_recv = true;

  // Simulate the receive interrupt handler on the PC.
  *com.rbuf = 0x34U;
}

int main()
{
  const bool login_is_ok = login(com);

  const std::string str_login = std::format("login_is_ok: {}", login_is_ok);

  std::cout << str_login << std::endl;
}
