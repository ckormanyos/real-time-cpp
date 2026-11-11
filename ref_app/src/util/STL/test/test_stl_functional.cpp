///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <functional>
#include <type_traits>

template<typename...>
using test_void_t = void;

template<typename T, typename = void>
struct can_call_ref : std::false_type { };

template<typename T>
struct can_call_ref<T, test_void_t<decltype(std::ref(std::declval<T>()))>> : std::true_type { };

template<typename T, typename = void>
struct can_call_cref : std::false_type { };

template<typename T>
struct can_call_cref<T, test_void_t<decltype(std::cref(std::declval<T>()))>> : std::true_type { };

struct functional_member_target
{
  int value;

  int add(int amount)
  {
    value += amount;
    return value;
  }

  int read() const
  {
    return value;
  }
};

struct functional_member_derived : functional_member_target { };

auto test_stl_sanity_functional() -> bool;

auto test_stl_sanity_functional() -> bool
{
  int value = 5;
  std::reference_wrapper<int> reference(value);
  reference.get() = 7;

  const int const_value = 11;
  std::reference_wrapper<const int> const_reference(const_value);

  auto increment = [](int number) { return number + 1; };
  std::reference_wrapper<decltype(increment)> callable(increment);

  const std::reference_wrapper<int> copied_reference(reference);
  const auto reference_from_ref = std::ref(value);
  const auto repeated_reference = std::ref(reference_from_ref);
  const auto const_reference_from_cref = std::cref(value);
  const auto repeated_const_reference = std::cref(reference_from_ref);

  if(   (value != 7)
     || (&reference.get() != &value)
     || (&const_reference.get() != &const_value)
     || (callable(4) != 5)
     || (copied_reference.get() != 7)
     || (&reference_from_ref.get() != &value)
     || (&repeated_reference.get() != &value)
     || (&const_reference_from_cref.get() != &value)
     || (&repeated_const_reference.get() != &value)
     || (!std::is_same<decltype(std::ref(reference_from_ref)), std::reference_wrapper<int>>::value)
     || (!std::is_same<decltype(std::cref(reference_from_ref)), std::reference_wrapper<const int>>::value)
     || (!can_call_ref<int&>::value)
     || can_call_ref<int&&>::value
     || (!can_call_cref<int&>::value)
     || can_call_cref<int&&>::value
     || std::is_constructible<std::reference_wrapper<int>, int&&>::value)
  {
    return false;
  }

  if(   (std::negate<int> { }(4) != -4)
     || (!std::logical_and<int> { }(1, 2))
     || std::logical_and<int> { }(1, 0)
     || (!std::logical_or<int> { }(0, 2))
     || std::logical_or<int> { }(0, 0)
     || (!std::logical_not<int> { }(0))
     || std::logical_not<int> { }(1)
     || (std::bit_and<unsigned int> { }(0x0FU, 0x05U) != 0x05U)
     || (std::bit_or<unsigned int> { }(0x08U, 0x05U) != 0x0DU)
     || (std::bit_xor<unsigned int> { }(0x0FU, 0x05U) != 0x0AU)
     || (std::bit_not<unsigned int> { }(0x0FU) != static_cast<unsigned int>(~0x0FU)))
  {
    return false;
  }

  const std::plus<> transparent_plus;
  const std::less<> transparent_less;
  if((transparent_plus(short(2), 3L) != 5L) || (!transparent_less(short(2), 3L)))
  {
    return false;
  }

  functional_member_derived member_target { };
  member_target.value = 6;
  const auto member_value = std::mem_fn(&functional_member_target::value);
  const auto member_add = std::mem_fn(&functional_member_target::add);
  const auto member_read = std::mem_fn(&functional_member_target::read);

  if(   (member_value(member_target) != 6)
     || (member_value(&member_target) != 6)
     || (member_value(std::ref(member_target)) != 6))
  {
    return false;
  }

  member_value(member_target) = 8;

  const functional_member_derived& const_member_target = member_target;
  if(   (member_target.value != 8)
     || (member_add(member_target, 3) != 11)
     || (member_add(&member_target, 2) != 13)
     || (member_add(std::ref(member_target), 1) != 14)
     || (member_read(const_member_target) != 14))
  {
    return false;
  }

  const std::hash<std::uint64_t> hash_u64;
  if(hash_u64(17U) != hash_u64(17U))
  {
    return false;
  }

  const std::hash<double> hash_double;
  if(   (hash_double(-0.0) != hash_double(0.0))
     || (hash_double(1.25) != hash_double(1.25)))
  {
    return false;
  }

  int pointed_value = 0;
  const std::hash<int*> hash_pointer;
  const std::hash<std::nullptr_t> hash_nullptr;
  if((hash_pointer(&pointed_value) != hash_pointer(&pointed_value))
     || (hash_nullptr(nullptr) != hash_nullptr(nullptr)))
  {
    return false;
  }

#if !defined(_MSC_VER)
  if(hash_u64(1U) == hash_u64(0x0000000100000000ULL))
  {
    return false;
  }
#endif

#if !defined(_MSC_VER) && (__cplusplus < 201703L)
  const auto first_bound = std::bind1st(std::less<int>(), 3);
  const auto second_bound = std::bind2nd(std::less<int>(), 5);

  if((!first_bound(4)) || (!second_bound(4)) || first_bound(2) || second_bound(6))
  {
    return false;
  }
#endif

#if !defined(_MSC_VER) && (__cplusplus < 201703L)
  if(!std::is_same<std::identity<int>::type, int>::value)
  {
    return false;
  }
#endif

  return true;
}
