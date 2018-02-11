#ifndef UTIL_DYNAMIC_BITSET_2018_02_03_H_
  #define UTIL_DYNAMIC_BITSET_2018_02_03_H_

  #include <algorithm>
  #include <cstddef>
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

      dynamic_bitset() : my_elem_count((my_bit_count / 8U) + (((my_bit_count % 8U) != 0U) ? 1U : 0U)),
                         my_memory    (allocator_type().allocate(my_elem_count))
      {
        std::fill(my_memory,
                  my_memory + my_elem_count,
                  std::uint8_t(0U));
      }

      ~dynamic_bitset()
      {
        allocator_type().deallocate(my_memory, my_elem_count);
      }

      void set(const std::size_t i)
      {
        my_memory[i / 8U] |= (UINT8_C(1) << (i % 8U));
      }

      void set()
      {
        for(std::uint_fast8_t i = 0U; (i < my_bit_count % 8U); ++i)
        {
          my_memory[my_elem_count - 1U] |= std::uint8_t(1U << i);
        }

        for(std::uint_fast8_t i = 0U; (i < (my_elem_count - 1U)); ++i)
        {
          my_memory[i] |= UINT8_C(0xFF);
        }
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

      bool any() const
      {
        return std::any_of(my_memory,
                           my_memory + my_elem_count,
                           [](const std::uint8_t& by) -> bool
                           {
                             return (by != 0U);
                           });
      }

      bool none() const
      {
        return std::all_of(my_memory,
                           my_memory + my_elem_count,
                           [](const std::uint8_t& by) -> bool
                           {
                             return (by == 0U);
                           });
      }

      static std::size_t size()
      {
        return my_bit_count;
      }

    private:
      const std::size_t   my_elem_count;
            std::uint8_t* my_memory;
    };
  } // namespace util

#endif // UTIL_DYNAMIC_BITSET_2018_02_03_H_
