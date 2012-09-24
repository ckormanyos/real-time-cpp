#ifndef _ARRAY_IMPL_2010_02_23_H_
  #define _ARRAY_IMPL_2010_02_23_H_

  #include "xalgorithm_impl.h"
  #include "iterator_impl.h"

  // Implement most of std::array for compilers that do not yet support it.

  namespace std
  {
    template<typename T,
	           const std::size_t N>
    class array
    {
    public:
      T elems[N];

      typedef std::size_t                           size_type;
      typedef std::ptrdiff_t                        difference_type;
      typedef T                                     value_type;
      typedef T*                                    pointer;
      typedef const T*                              const_pointer;
      typedef T&                                    reference;
      typedef const T&                              const_reference;
      typedef pointer                               iterator;
      typedef const_pointer                         const_iterator;
      typedef std::reverse_iterator<iterator>       reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

      static constexpr size_type static_size = N;

      iterator begin(void) { return elems; }
      iterator end  (void) { return elems + N; }

      const_iterator begin(void) const { return elems; }
      const_iterator end  (void) const { return elems + N; }

      const_iterator cbegin(void) const { return elems; }
      const_iterator cend  (void) const { return elems + N; }

      reverse_iterator rbegin(void) { return reverse_iterator(elems + N); }
      reverse_iterator rend  (void) { return reverse_iterator(elems); }

      const_reverse_iterator rbegin(void) const { return const_reverse_iterator(elems + N); }
      const_reverse_iterator rend  (void) const { return const_reverse_iterator(elems); }

      const_reverse_iterator crbegin(void) const { return const_reverse_iterator(elems + N); }
      const_reverse_iterator crend  (void) const { return const_reverse_iterator(elems); }

      reference operator[](const size_type i)             { return elems[i]; }
      const_reference operator[](const size_type i) const { return elems[i]; }

      reference at(const size_type i)             { rangecheck(i); return elems[i]; }
      const_reference at(const size_type i) const { rangecheck(i); return elems[i]; }

      reference front(void)             { return elems[0U]; }
      const_reference front(void) const { return elems[0U]; }

      reference back(void)             { return elems[N - 1U]; }
      const_reference back(void) const { return elems[N - 1U]; }

      static size_type size(void)     { return N; }
      static bool empty(void)         { return false; }
      static size_type max_size(void) { return N; }

      template<typename T2>
      void swap(array<T2, N>& y)
      {
        xalgorithm::xswap_ranges(begin(), end(), y.begin());
      }

      const_pointer data(void) const { return elems; }
      pointer data(void)             { return elems; }

      pointer c_array(void) { return elems; }

      template<typename T2>
      array& operator=(const array<T2, N>& y)
      {
        xalgorithm::xcopy(y.begin(), y.end(), begin());
        return *this;
      }

      void assign(const value_type& value)
      {
        xalgorithm::xfill(begin(), N, value);
      }

    private:
      static void rangecheck(const size_type) { }
    };
  }

#endif // _ARRAY_IMPL_2010_02_23_H_
