///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RING_ALLOCATOR_2010_02_23_H
  #define UTIL_RING_ALLOCATOR_2010_02_23_H

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>

  namespace util
  {
    template <const std::size_t ArenaSize>
    struct ring_arena {
        std::array<std::uint8_t, ArenaSize> buffer;

        std::size_t head{};
        std::size_t outstanding{};
        std::size_t peak_outstanding{};
        std::size_t allocations{};
    };

    template <class T, const std::size_t ArenaSize>
    class ring_allocator {
    public:
        using value_type = T;

        ring_allocator() {}

        template <class U>
        ring_allocator(const ring_allocator<U, ArenaSize>&) {}

        template<typename U> 
        struct rebind {
            using other = ring_allocator<U, ArenaSize>;
        };

        T* allocate(const std::size_t n) {

            ring_arena<ArenaSize>* arena_ptr{&arena_instance};

            const std::size_t bytes = n * sizeof(T);
            std::size_t       at    = (arena_ptr->head + alignof(T) - 1) & ~(alignof(T) - 1);
            if (at + bytes > arena_ptr->buffer.size()) {
                at = 0; // wrap
                if (bytes > arena_ptr->buffer.size()) {
                    return nullptr;
                }
            }
            arena_ptr->head = at + bytes;
            arena_ptr->outstanding += bytes;
            arena_ptr->peak_outstanding = std::max(arena_ptr->peak_outstanding, arena_ptr->outstanding);
            ++arena_ptr->allocations;
            return reinterpret_cast<T*>(static_cast<void*>(arena_ptr->buffer.data() + at));
        }

        auto deallocate(T*, const std::size_t n) noexcept -> void {
            ring_arena<ArenaSize>* arena_ptr{&arena_instance};

            arena_ptr->outstanding -= n * sizeof(T);
        }

    private:
        static ring_arena<ArenaSize> arena_instance;

        friend auto operator==(const ring_allocator&, const ring_allocator&) noexcept -> bool {
            return true; }

        friend auto operator!=(const ring_allocator&, const ring_allocator&) noexcept -> bool {
            return false; }
    };

    template <class T, const std::size_t ArenaSize>
    ring_arena<ArenaSize> ring_allocator<T, ArenaSize>::arena_instance;
  }

#endif // UTIL_RING_ALLOCATOR_2010_02_23_H
