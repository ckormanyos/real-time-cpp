///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H // NOLINT(llvm-header-guard)
  #define UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H

  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <type_traits>

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
    using value_type    = void;
    using pointer       = value_type*;
    using const_pointer = const value_type*;

    template<typename RebindType>
    struct rebind
    {
      using other = n_slot_array_allocator<RebindType, SlotWidth, SlotCount>;
    };
  };

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  class n_slot_array_allocator // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    static_assert(SlotWidth > 0U, "SlotWidth must be greater than zero.");
    static_assert(SlotCount > 0U, "SlotCount must be greater than zero.");
    static_assert(std::is_trivial<T>::value && std::is_standard_layout<T>::value,
                  "T must be a POD-like type.");
    static_assert(std::is_default_constructible<T>::value,
                  "T must be default constructible for the fixed slot storage.");
    static_assert(std::is_copy_constructible<T>::value,
                  "T must be copy constructible for allocator construction.");

    static constexpr std::uint_fast32_t slot_width = SlotWidth;
    static constexpr std::size_t        slot_count = SlotCount;

    using slot_array_type        = std::array<T, static_cast<std::size_t>(slot_width)>;
    using slot_array_memory_type = std::array<slot_array_type, slot_count>;
    using slot_array_flags_type  = std::array<std::uint8_t, slot_count>;

  public:
    using size_type          = std::size_t;
    using value_type         = typename slot_array_type::value_type;
    using pointer            = value_type*;
    using const_pointer      = const value_type*;
    using void_pointer       = void*;
    using const_void_pointer = const void*;
    using reference          = value_type&;
    using const_reference    = const value_type&;
    using difference_type    = std::ptrdiff_t;

    constexpr n_slot_array_allocator() = default; // LCOV_EXCL_LINE

    constexpr n_slot_array_allocator(const n_slot_array_allocator&) = default; // LCOV_EXCL_LINE

    template <class U>
    constexpr n_slot_array_allocator(const n_slot_array_allocator<U, SlotWidth, SlotCount>&) noexcept { }

    template<typename RebindType>
    struct rebind
    {
      using other = n_slot_array_allocator<RebindType, SlotWidth, SlotCount>;
    };

    constexpr auto max_size() const noexcept -> size_type { return static_cast<size_type>(slot_width); }
    constexpr auto max_slot_count() const noexcept -> size_type { return slot_count; }

    constexpr auto address(      reference x) const ->       pointer { return &x; }
    constexpr auto address(const_reference x) const -> const_pointer { return &x; }

    auto allocate(size_type count, const_void_pointer p_hint = nullptr) -> pointer
    {
      static_cast<void>(p_hint);

      if(count == static_cast<size_type>(UINT8_C(0)))
      {
        return nullptr;
      }

      if(count > max_size())
      {
        return nullptr;
      }

      pointer p { nullptr };

      auto& my_slot_array_memory { slot_array_memory() };
      auto& my_slot_flags        { slot_flags() };
      auto& my_next_free_slot    { next_free_slot() };

      if(my_next_free_slot >= slot_count)
      {
        return nullptr;
      }

      {
        using local_flags_value_type = typename slot_array_flags_type::value_type;

        const auto allocated_slot_index { my_next_free_slot };

        my_slot_flags[allocated_slot_index] = static_cast<local_flags_value_type>(UINT8_C(1)); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        p = static_cast<pointer>(my_slot_array_memory[allocated_slot_index].data()); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

        my_next_free_slot = slot_count;

        for(auto i = allocated_slot_index + 1U; i < slot_count; ++i)
        {
          if(my_slot_flags[i] == static_cast<local_flags_value_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
          {
            my_next_free_slot = i;

            break;
          }
        }

        if(my_next_free_slot == slot_count)
        {
          for(auto i = static_cast<std::size_t>(UINT8_C(0)); i < allocated_slot_index; ++i)
          {
            if(my_slot_flags[i] == static_cast<local_flags_value_type>(UINT8_C(0))) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
            {
              my_next_free_slot = i;

              break;
            }
          }
        }
      }

      return p;
    }

    auto deallocate(pointer p_slot, size_type sz) -> void
    {
      static_cast<void>(sz);

      if(p_slot == nullptr)
      {
        return;
      }

      typename slot_array_memory_type::size_type index { };

      auto& my_slot_array_memory { slot_array_memory() };
      auto& my_slot_flags        { slot_flags() };
      auto& my_next_free_slot    { next_free_slot() };

      for(auto& mem_entry : my_slot_array_memory)
      {
        if(p_slot == static_cast<pointer>(mem_entry.data()))
        {
          using local_flags_value_type = typename slot_array_flags_type::value_type;

          my_slot_flags[index] = static_cast<local_flags_value_type>(UINT8_C(0)); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

          if(index < my_next_free_slot)
          {
            my_next_free_slot = index;
          }

          break;
        }

        ++index;
      }
    }

  private:
    static auto slot_array_memory() -> slot_array_memory_type& { static slot_array_memory_type my_mem_instance; return my_mem_instance; }
    static auto slot_flags       () -> slot_array_flags_type&  { static slot_array_flags_type  my_flg_instance; return my_flg_instance; }
    static auto next_free_slot   () -> std::size_t&            { static std::size_t            my_idx_instance; return my_idx_instance; }
  };

  // Global comparison operators (required by the standard).
  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  auto operator==(const n_slot_array_allocator<T, SlotWidth, SlotCount>& left,
                  const n_slot_array_allocator<T, SlotWidth, SlotCount>& right) -> bool
  {
    static_cast<void>(left.max_size());
    static_cast<void>(right.max_size());

    return true;
  }

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  auto operator!=(const n_slot_array_allocator<T, SlotWidth, SlotCount>& left,
                  const n_slot_array_allocator<T, SlotWidth, SlotCount>& right) -> bool
  {
    static_cast<void>(left.max_size());
    static_cast<void>(right.max_size());

    return false;
  }

  } // namespace util

#endif // UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H
