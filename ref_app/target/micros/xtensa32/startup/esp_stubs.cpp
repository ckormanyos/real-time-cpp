///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>

extern "C"
{
  typedef enum esp_log_level_t
  {
    dummy_esp_log_level
  }
  esp_log_level_t;

  typedef enum uart_port_t
  {
    dummy_uart_port
  }
  uart_port_t;

  typedef unsigned long TickType_t;
  typedef long BaseType_t;

  ::std::uint32_t esp_log_timestamp();
  void esp_log_level_set(const char*, esp_log_level_t);
  void esp_log_write(esp_log_level_t, const char*, const char*, ...);

  typedef void (*spi_flash_guard_start_func_t)();
  typedef void (*spi_flash_guard_end_func_t)();
  typedef void (*spi_flash_op_lock_func_t)();
  typedef void (*spi_flash_op_unlock_func_t)();

  typedef struct
  {
    spi_flash_guard_start_func_t start;
    spi_flash_guard_end_func_t   end;
    spi_flash_op_lock_func_t     op_lock;
    spi_flash_op_unlock_func_t   op_unlock;
  }
  spi_flash_guard_funcs_t;

  void spi_flash_init();
  void spi_flash_guard_set(const void*);
  bool spi_flash_cache_enabled();

  void eri_write(int, ::std::uint32_t);

  int esp_ota_get_app_elf_sha256(char*, ::std::size_t);

  using esp_err_t = int;

  esp_err_t esp_coex_adapter_register(void*);

  esp_err_t coex_pre_init();

  esp_err_t uart_flush_input(uart_port_t) __attribute__((weak));

  void __assert_func(const char*, int, const char*, const char*) __attribute__((noreturn));

  int fprintf(void*, const char* format, ... );

  int snprintf(char*, std::size_t, const char*, ... );

  void vRingbufferReturnItem(void*, void*);

  void* xRingbufferReceive(void*, size_t*, TickType_t);

  BaseType_t xRingbufferSend(void*, const void*, size_t, TickType_t);

  ::std::uint32_t esp_log_timestamp() { return UINT32_C(0); }

  void esp_log_level_set(const char*, esp_log_level_t) { }

  void esp_log_write(esp_log_level_t, const char*, const char*, ...) { }

  void spi_flash_init() { }
  void spi_flash_guard_set(const void*) { }
  bool spi_flash_cache_enabled() { return false; }

  spi_flash_guard_funcs_t g_flash_guard_default_ops { nullptr, nullptr, nullptr, nullptr };

  void eri_write(int, ::std::uint32_t) { }

  int esp_ota_get_app_elf_sha256(char*, ::std::size_t) { return -1; }

  esp_err_t esp_coex_adapter_register(void*) { return -1; }

  esp_err_t coex_pre_init() { return -1; }

  esp_err_t uart_flush_input(uart_port_t) { return -1; }

  void __assert_func(const char*, int, const char*, const char*) { for(;;) { ; } }

  int snprintf(char*, std::size_t, const char*, ... ) { return -1; }

  void vRingbufferReturnItem(void*, void*) { }

  void* xRingbufferReceive(void*, size_t*, TickType_t) { return nullptr; }

  BaseType_t xRingbufferSend(void*, const void*, size_t, TickType_t) { return -1L; }
}
