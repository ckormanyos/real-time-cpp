///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H // NOLINT(llvm-header-guard)
  #define UTIL_N_SLOT_ARRAY_ALLOCATOR_2020_10_25_H

  #include <algorithm>
  #include <array>
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
    static constexpr std::uint_fast32_t slot_width = SlotWidth;
    static constexpr std::size_t        slot_count = SlotCount;

    using slot_array_type        = std::array<T, slot_width>;
    using slot_array_memory_type = std::array<slot_array_type, slot_count>;
    using slot_array_flags_type  = std::array<std::uint8_t, slot_count>;

  public:
    using size_type       = std::size_t;
    using value_type      = typename slot_array_type::value_type;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    constexpr n_slot_array_allocator() = default; // LCOV_EXCL_LINE

    constexpr n_slot_array_allocator(const n_slot_array_allocator&) = default; // LCOV_EXCL_LINE

    template<typename RebindType>
    struct rebind
    {
      using other = n_slot_array_allocator<RebindType, SlotWidth, SlotCount>;
    };

    constexpr auto max_size() const noexcept -> size_type { return slot_count; }

    constexpr auto address(      reference x) const ->       pointer { return &x; }
    constexpr auto address(const_reference x) const -> const_pointer { return &x; }

    auto allocate
    (
      size_type                                                                    count,
      typename n_slot_array_allocator<void, slot_width, slot_count>::const_pointer p_hint = nullptr
    ) -> pointer
    {
      static_cast<void>(count);
      static_cast<void>(p_hint);

      pointer p = nullptr;

      // TBD: There is most likely significant optimization potential
      // capable of being unlocked if a storage/lookup mechanism can be
      // devised that uses a binary search when finding the next free slot.

      for(std::size_t i = 0U; i < slot_count; ++i)
      {
        if(slot_flags[i] == 0U) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        {
          slot_flags[i] = 1U; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

          p = static_cast<pointer>(slot_array_memory[i].data()); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

          if(i > slot_max_index)
          {
            slot_max_index = i;

            static_cast<void>(slot_max_index);
          }

          break;
        }
      }

      return p;
    }

    auto construct(pointer p, const value_type& x) -> void
    {
      // The memory in the n-slot allocator already exists
      // in an uninitialized form. Construction can safely
      // simply set the value in the uninitialized memory.

      *p = x;
    }

    auto destroy(pointer p) const -> void { static_cast<void>(p); } // LCOV_EXCL_LINE

    auto deallocate(pointer p_slot, size_type sz) -> void
    {
      static_cast<void>(sz);

      auto index = static_cast<typename slot_array_memory_type::size_type>(UINT8_C(0));

      for(auto& slot_array_memory_entry : slot_array_memory)
      {
        if(p_slot == static_cast<pointer>(slot_array_memory_entry.data()))
        {
          slot_flags[index] = static_cast<typename slot_array_flags_type::value_type>(UINT8_C(0)); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

          break;
        }

        ++index;
      }
    }

  private:
    static slot_array_memory_type slot_array_memory; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    static slot_array_flags_type  slot_flags;        // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    static std::size_t            slot_max_index;    // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
  };

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  typename n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_array_memory_type n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_array_memory; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  typename n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_array_flags_type n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_flags; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  template<typename T,
           const std::uint_fast32_t SlotWidth,
           const std::size_t SlotCount>
  std::size_t n_slot_array_allocator<T, SlotWidth, SlotCount>::slot_max_index; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

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
