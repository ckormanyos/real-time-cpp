#include <mcal_cpu.h>

extern "C"
uint8_t mcal_cpu_read_program_memory_byte(const uint8_t* pointer_to_program_memory)
{
  return *pointer_to_program_memory;
}

extern "C"
uint16_t mcal_cpu_read_program_memory_word(const uint8_t* pointer_to_program_memory)
{
  const uint8_t memory_array[2U] =
  {
    *(pointer_to_program_memory + 0U),
    *(pointer_to_program_memory + 1U)
  };

  uint16_t memory_value;

  *(reinterpret_cast<uint8_t*>(&memory_value) + 0U) = memory_array[0U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 1U) = memory_array[1U];

  return memory_value;
}

extern "C"
uint32_t mcal_cpu_read_program_memory_dword(const uint8_t* pointer_to_program_memory)
{
  const uint8_t memory_array[4U] =
  {
    *(pointer_to_program_memory + 0U),
    *(pointer_to_program_memory + 1U),
    *(pointer_to_program_memory + 2U),
    *(pointer_to_program_memory + 3U)
  };

  uint32_t memory_value;

  *(reinterpret_cast<uint8_t*>(&memory_value) + 0U) = memory_array[0U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 1U) = memory_array[1U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 2U) = memory_array[2U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 3U) = memory_array[3U];

  return memory_value;
}

extern "C"
uint64_t mcal_cpu_read_program_memory_qword(const uint8_t* pointer_to_program_memory)
{
  const uint8_t memory_array[8U] =
  {
    *(pointer_to_program_memory + 0U),
    *(pointer_to_program_memory + 1U),
    *(pointer_to_program_memory + 2U),
    *(pointer_to_program_memory + 3U),
    *(pointer_to_program_memory + 4U),
    *(pointer_to_program_memory + 5U),
    *(pointer_to_program_memory + 6U),
    *(pointer_to_program_memory + 7U)
  };

  uint64_t memory_value;

  *(reinterpret_cast<uint8_t*>(&memory_value) + 0U) = memory_array[0U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 1U) = memory_array[1U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 2U) = memory_array[2U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 3U) = memory_array[3U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 4U) = memory_array[4U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 5U) = memory_array[5U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 6U) = memory_array[6U];
  *(reinterpret_cast<uint8_t*>(&memory_value) + 7U) = memory_array[7U];

  return memory_value;
}
