#ifndef MCAL_MEMORY_PROGMEM_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_2019_08_17_H_

  #include <stdint.h>

  #define MY_PROGMEM

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline uint8_t mcal_memory_progmem_read_byte(const uint8_t* src)
  {
    return *src;
  }

  static inline uint16_t mcal_memory_progmem_read_word(const uint16_t* src)
  {
    uint16_t dest;

    *(((uint8_t*) &dest) + 0U) = *(((const uint8_t*) src) + 0U);
    *(((uint8_t*) &dest) + 1U) = *(((const uint8_t*) src) + 1U);

    return dest;
  }

  static inline uint32_t mcal_memory_progmem_read_dword(const uint32_t* src)
  {
    uint32_t dest;

    *(((uint8_t*) &dest) + 0U) = *(((const uint8_t*) src) + 0U);
    *(((uint8_t*) &dest) + 1U) = *(((const uint8_t*) src) + 1U);
    *(((uint8_t*) &dest) + 2U) = *(((const uint8_t*) src) + 2U);
    *(((uint8_t*) &dest) + 3U) = *(((const uint8_t*) src) + 3U);

    return dest;
  }

  static inline uint64_t mcal_memory_progmem_read_qword(const uint64_t* src)
  {
    uint64_t dest;

    *(((uint8_t*) &dest) + 0U) = *(((const uint8_t*) src) + 0U);
    *(((uint8_t*) &dest) + 1U) = *(((const uint8_t*) src) + 1U);
    *(((uint8_t*) &dest) + 2U) = *(((const uint8_t*) src) + 2U);
    *(((uint8_t*) &dest) + 3U) = *(((const uint8_t*) src) + 3U);
    *(((uint8_t*) &dest) + 4U) = *(((const uint8_t*) src) + 4U);
    *(((uint8_t*) &dest) + 5U) = *(((const uint8_t*) src) + 5U);
    *(((uint8_t*) &dest) + 6U) = *(((const uint8_t*) src) + 6U);
    *(((uint8_t*) &dest) + 7U) = *(((const uint8_t*) src) + 7U);

    return dest;
  }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_MEMORY_PROGMEM_2019_08_17_H_
