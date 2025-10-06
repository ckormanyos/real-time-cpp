///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-003_poll_communication.cpp

#include <chrono>
#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <thread>

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_tbuf { };
    std::uint8_t dummy_register_rbuf { };
  }
}

auto task_send_one_byte() -> void;
auto task_poll_communication() -> void;

class communication
{
public:
  communication() = default;

  ~communication() = default;

  auto send_byte(const std::uint8_t by) const -> bool
  {
    // Transmit the byte.
    *tbuf = by;

    return true;
  }

  auto recv_ready() const noexcept -> bool { return has_recv; }

  auto recv_byte() noexcept -> std::uint8_t
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

  auto operator=(const communication&) -> const communication& = delete;

  friend auto task_poll_communication() -> void;
};

std::uint8_t* communication::tbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_tbuf);
std::uint8_t* communication::rbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_rbuf);

extern communication com;

auto task_send_one_byte() -> void
{
  constexpr std::uint8_t the_byte { UINT8_C(0x12) };

  std::cout << std::format("send byte: {:#02x}", static_cast<unsigned>(the_byte)) << std::endl;

  com.send_byte(the_byte);
}

auto task_poll_communication() -> void
{
  for(;;)
  {
    if(com.recv_ready())
    {
      const std::uint8_t the_byte = com.recv_byte();

      // Do something with the_byte.
      std::cout << std::format("recv byte: {:#02x}", static_cast<unsigned>(the_byte)) << std::endl;

      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10U));

    // Simulate receiving a byte.
    *com.rbuf = UINT8_C(0x34);

    com.has_recv = true;
  }
}

// Instantiate a non-constant communication instance.
communication com { };

auto main() -> int
{
  std::thread com_send_thread = std::thread(task_send_one_byte);

  com_send_thread.join();

  std::thread com_recv_thread = std::thread(task_poll_communication);

  com_recv_thread.join();
}
