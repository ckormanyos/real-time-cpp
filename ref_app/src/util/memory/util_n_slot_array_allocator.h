#ifndef UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H_
  #define UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H_

  #include <array>
  #include <algorithm>
  #include <cstddef>
  #include <cstdint>

  namespace util {

  // Forward declaration of n_slot_array_allocator template.
  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  class n_slot_array_allocator;

  // Template partial specialization of n_slot_array_allocator template for void.
  template<const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  class n_slot_array_allocator<void, SlotWidth, SlotCount>
  {
  public:
    typedef void              value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;

    template<typename U>
    struct rebind
    {
      using other = n_slot_array_allocator<U, SlotWidth, SlotCount>;
    };
  };

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  class n_slot_array_allocator
  {
  private:
    static constexpr std::uint_fast32_t slot_width = SlotWidth;
    static constexpr std::size_t        slot_count = SlotCount;

    using slot_array_type = std::array<T, slot_width>;

  public:
    using size_type       = std::size_t;
    using value_type      = typename slot_array_type::value_type;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    n_slot_array_allocator() = default;

    n_slot_array_allocator(const n_slot_array_allocator&) = default;

    template<typename U>
    struct rebind
    {
      using other = n_slot_array_allocator<U, SlotWidth, SlotCount>;
    };

    size_type max_size() const
    {
      return sizeof(slot_array_type) * slot_count;
    }

          pointer address(      reference x) const { return &x; }
    const_pointer address(const_reference x) const { return &x; }

    pointer allocate(size_type, // count
                     typename n_slot_array_allocator<void, slot_width, slot_count>::const_pointer = nullptr)
    {
      pointer p = nullptr;

      for(std::size_t i = 0U; i < slot_count; ++i)
      {
        if(slot_flags[i] == 0U)
        {
          slot_flags[i] = 1U;

          p = (pointer) slot_array_memory[i].data();

          if(i > slot_max_index)
          {
            slot_max_index = i;

            (void) slot_max_index;
          }

          break;
        }
      }

      return p;
    }

    void construct(pointer p, const value_type& x)
    {
      // The memory in the n-slot allocator already exists
      // in an uninitialized form. Construction can safely
      // simply set the value in the uninitialized memory.

      *p = x;
    }

    void destroy(pointer p)
    {
      (void) p;
    }

    void deallocate(pointer p_slot, size_type)
    {
      for(std::size_t i = 0U; i < slot_count; ++i)
      {
        if(p_slot == (pointer) slot_array_memory[i].data())
        {
          slot_flags[i] = 0U;

          break;
        }
      }
    }

  private:
    static slot_array_type                      slot_array_memory[slot_count];
    static std::array<std::uint8_t, slot_count> slot_flags;
    static std::size_t                          slot_max_index;
  };

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  typename n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_array_type
  n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_array_memory[n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_count];

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  std::array<std::uint8_t, n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_count>
  n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_flags;

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  std::size_t n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_max_index;

  // Global comparison operators (required by the standard).
  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  bool operator==(const n_slot_array_allocator<T, SlotWidth, SlotCount>&,
                  const n_slot_array_allocator<T, SlotWidth, SlotCount>&)
  {
    return true;
  }

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  bool operator!=(const n_slot_array_allocator<T, SlotWidth, SlotCount>&,
                  const n_slot_array_allocator<T, SlotWidth, SlotCount>&)
  {
    return false;
  }

  } // namespace util

#endif // UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H_
