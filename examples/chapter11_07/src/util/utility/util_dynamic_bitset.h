#ifndef UTIL_DYNAMIC_BITSET_2018_02_03_H_
  #define UTIL_DYNAMIC_BITSET_2018_02_03_H_

  #include <algorithm>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    template<const std::size_t my_bit_count,
             typename alloc = std::allocator<std::uint8_t>>
    class dynamic_bitset
    {
    public:
      using allocator_type = alloc;

      static const std::size_t my_elem_count = (my_bit_count / 8U) + (((my_bit_count % 8U) != 0U) ? 1U : 0U);

      dynamic_bitset() : my_memory(allocator_type().allocate(my_elem_count))
      {
        std::fill(my_memory,
                  my_memory + my_elem_count,
                  UINT8_C(0));
      }

      ~dynamic_bitset()
      {
        std::allocator_traits<allocator_type>::deallocate(allocator_type(), my_memory, my_elem_count);
      }

      void set(const std::size_t i)
      {
        my_memory[i / 8U] |= (UINT8_C(1) << (i % 8U));
      }

      void flip(const std::size_t i)
      {
        my_memory[i / 8U] ^= (UINT8_C(1) << (i % 8U));
      }

      bool test(const std::size_t i) const
      {
        const std::uint8_t test_value = (my_memory[i / 8U] & (UINT8_C(1) << (i % 8U)));

        return (test_value != 0U);
      }

      static std::size_t size()
      {
        return my_bit_count;
      }

    private:
      std::uint8_t* my_memory;
    };
  } // namespace util

#endif // UTIL_DYNAMIC_BITSET_2018_02_03_H_
