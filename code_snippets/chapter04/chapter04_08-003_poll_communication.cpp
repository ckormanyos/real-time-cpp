///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-003_poll_communication.cpp

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <thread>

#define __attribute__(attr)

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_tbuf;
    std::uint8_t dummy_register_rbuf;
  }
}

void task_poll_communication();

class communication
{
public:
  communication() : recv_buf(0U),
                    has_recv(false) { }

  ~communication() = default;

  bool send_byte(const std::uint8_t by) const
  {
    // Transmit the byte.
    *tbuf = by;

    return true;
  }

  bool recv_ready() const { return has_recv; }

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

  std::uint8_t recv_buf;
  bool has_recv;

  communication(const communication&) = delete;

  const communication& operator=(const communication&) = delete;

  friend void task_poll_communication();
};

std::uint8_t* communication::tbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_tbuf);
std::uint8_t* communication::rbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_rbuf);

extern communication com;

void task_poll_communication()
{
  for(;;)
  {
    if(com.recv_ready())
    {
      const std::uint8_t the_byte = com.recv_byte();

      // Do something with the_byte.
      std::cout << std::hex << std::showbase << "received byte: " << unsigned(the_byte) << std::endl;

      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10U));

    // Simulate receiving a byte.
    *com.rbuf = 0x34U;

    com.has_recv = true;
  }
}

// Instantiate a non-constant communication instance.
communication com;

int main()
{
  com.send_byte(0x12U);

  std::thread com_recv_thread = std::thread(task_poll_communication);

  com_recv_thread.join();
}
