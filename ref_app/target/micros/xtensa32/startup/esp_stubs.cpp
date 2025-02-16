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
    dummy
  }
  esp_log_level_t;

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

  ::std::uint32_t esp_log_timestamp() { return UINT32_C(0); }

  void esp_log_level_set(const char*, esp_log_level_t) { }

  void esp_log_write(esp_log_level_t, const char*, const char*, ...) { }

  void spi_flash_init() { }
  void spi_flash_guard_set(const void*) { }
  bool spi_flash_cache_enabled() { return false; }

  spi_flash_guard_funcs_t g_flash_guard_default_ops { nullptr, nullptr, nullptr, nullptr };

  void eri_write(int, ::std::uint32_t) { }

  int esp_ota_get_app_elf_sha256(char*, ::std::size_t) { return -1; }
}
