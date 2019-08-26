#ifndef MCAL_MEMORY_PROGMEM_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_2019_08_17_H_

  #include <stdint.h>

  #include <avr/pgmspace.h>

  #define MY_PROGMEM PROGMEM

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline uint8_t mcal_memory_progmem_read_byte(const uint8_t* src)
  {
    return pgm_read_byte(src);
  }

  static inline uint16_t mcal_memory_progmem_read_word(const uint16_t* src)
  {
    return pgm_read_word(src);
  }

  static inline uint32_t mcal_memory_progmem_read_dword(const uint32_t* src)
  {
    return pgm_read_dword(src);
  }

  static inline uint64_t mcal_memory_progmem_read_qword(const uint64_t* src)
  {
    uint64_t dest;

    *(((uint8_t*) &dest) + 0U) = pgm_read_byte(((const uint8_t*) src) + 0U);
    *(((uint8_t*) &dest) + 1U) = pgm_read_byte(((const uint8_t*) src) + 1U);
    *(((uint8_t*) &dest) + 2U) = pgm_read_byte(((const uint8_t*) src) + 2U);
    *(((uint8_t*) &dest) + 3U) = pgm_read_byte(((const uint8_t*) src) + 3U);
    *(((uint8_t*) &dest) + 4U) = pgm_read_byte(((const uint8_t*) src) + 4U);
    *(((uint8_t*) &dest) + 5U) = pgm_read_byte(((const uint8_t*) src) + 5U);
    *(((uint8_t*) &dest) + 6U) = pgm_read_byte(((const uint8_t*) src) + 6U);
    *(((uint8_t*) &dest) + 7U) = pgm_read_byte(((const uint8_t*) src) + 7U);

    return dest;
  }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_MEMORY_PROGMEM_2019_08_17_H_
