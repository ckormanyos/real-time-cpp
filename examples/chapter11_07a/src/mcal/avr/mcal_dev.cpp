///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_benchmark.h>
#include <mcal_dev.h>
#include <mcal_memory/mcal_memory_sram_array.h>

auto mcal::dev::post_init() -> void
{
  using benchmark_port_type = ::mcal::benchmark::benchmark_port_type;

  benchmark_port_type::set_direction_output();

  mcal::spi::sram::mcal_spi_sram_type::init();
  mcal::spi::lcd::mcal_spi_lcd_type::init();
}
