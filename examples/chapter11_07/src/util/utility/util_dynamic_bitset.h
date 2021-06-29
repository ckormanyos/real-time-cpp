#ifndef UTIL_DYNAMIC_BITSET_2018_02_03_H_
  #define UTIL_DYNAMIC_BITSET_2018_02_03_H_

  #include <algorithm>
  #include <cstddef>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    template<const std::size_t bit_count,
             typename T,
             typename alloc>
    class dynamic_bitset
    {
    private:
      static_assert(bit_count > 0U,
                    "error: the bit_count in dynamic_bitset must exceed zero.");

    public:
      using size_type      = std::size_t;
      using value_type     = T;
      using allocator_type = alloc;

      static constexpr std::size_t elem_digits =
        static_cast<size_type>(std::numeric_limits<value_type>::digits);

      static constexpr size_type elem_count =
            size_type(bit_count / elem_digits)
        + ((size_type(bit_count % elem_digits) != 0U) ? 1U : 0U);

      dynamic_bitset() : my_memory(allocator_type().allocate(elem_count))
      {
        std::fill(my_memory,
                  my_memory + elem_count,
                  value_type(0U));
      }

      ~dynamic_bitset()
      {
        allocator_type().deallocate(my_memory, elem_count);
      }

      void set(const std::size_t i)
      {
        my_memory[i / elem_digits] |= value_type(value_type(1ULL) << (i % elem_digits));
      }

      void set()
      {
        for(std::uint_fast8_t i = 0U; (i < std::uint_fast8_t(bit_count % elem_digits)); ++i)
        {
          my_memory[elem_count - 1U] |= value_type(value_type(1ULL) << i);
        }

        for(std::uint_fast8_t i = 0U; (i < (elem_count - 1U)); ++i)
        {
          my_memory[i] |= (std::numeric_limits<value_type>::max)();
        }
      }

      void flip(const std::size_t i)
      {
        my_memory[i / elem_digits] ^= (UINT8_C(1) << (i % elem_digits));
      }

      bool test(const std::size_t i) const
      {
        const value_type test_value =
          (my_memory[i / elem_digits] & value_type(value_type(1ULL) << (i % elem_digits)));

        return (test_value != 0U);
      }

      bool any() const
      {
        return std::any_of(my_memory,
                           my_memory + elem_count,
                           [](const value_type& value) -> bool
                           {
                             return (value != 0U);
                           });
      }

      bool none() const
      {
        return std::all_of(my_memory,
                           my_memory + elem_count,
                           [](const value_type& value) -> bool
                           {
                             return (value == 0U);
                           });
      }

      static constexpr size_type size()
      {
        return bit_count;
      }

    private:
      typename allocator_type::pointer my_memory;
    };
  } // namespace util

#endif // UTIL_DYNAMIC_BITSET_2018_02_03_H_
