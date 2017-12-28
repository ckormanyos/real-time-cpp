///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_CIRCULAR_BUFFER_2007_11_22_H_
  #define UTIL_CIRCULAR_BUFFER_2007_11_22_H_

  #include <algorithm>
  #include <cstddef>
  #include <iterator>

  namespace util
  {
    // Forward declaration of the circular_buffer class.
    template<typename T,
             const std::size_t N>
    class circular_buffer;

    namespace circular_buffer_detail
    {
      template<typename T,
               const std::size_t N,
               typename traits_type>
      struct circular_iterator : public std::iterator<std::random_access_iterator_tag,
                                                      typename traits_type::value_type,
                                                      typename traits_type::difference_type,
                                                      typename traits_type::pointer,
                                                      typename traits_type::reference>
      {
      public:
        typedef std::iterator<std::random_access_iterator_tag,
                              typename traits_type::value_type,
                              typename traits_type::difference_type,
                              typename traits_type::pointer,
                              typename traits_type::reference> iterator_type;

        typedef typename       iterator_type::value_type      value_type;
        typedef typename       iterator_type::pointer         pointer;
        typedef typename       iterator_type::reference       reference;
        typedef          const reference                      const_reference;
        typedef typename       std::size_t                    size_type;
        typedef typename       iterator_type::difference_type difference_type;

        explicit circular_iterator(const pointer pb,
                                   const pointer pc = pb) : buffer_pointer  (pb),
                                                            circular_pointer(pc) { }

        ~circular_iterator() { }

        circular_iterator& operator=(const circular_iterator& other_iterator)
        {
          if(this != &other_iterator)
          {
            buffer_pointer   = other_iterator.buffer_pointer;
            circular_pointer = other_iterator.circular_pointer;
          }

          return *this;
        }

        const_reference operator*() const
        {
          return *circular_pointer;
        }

        reference operator*()
        {
          return *const_cast<pointer>(circular_pointer);
        }

        circular_iterator& operator++()
        {
          ++circular_pointer;

          if(circular_pointer > (buffer_pointer + difference_type(N)))
          {
            circular_pointer = buffer_pointer;
          }

          return *this;
        }

        circular_iterator& operator--()
        {
          --circular_pointer;

          if(circular_pointer < buffer_pointer)
          {
            circular_pointer = buffer_pointer + difference_type(N);
          }

          return *this;
        }

        circular_iterator operator++(int)
        {
          circular_iterator tmp = *this;

          ++(*this);

          return tmp;
        }

        circular_iterator operator--(int)
        {
          circular_iterator tmp = *this;

          --(*this);

          return tmp;
        }

        circular_iterator& operator+=(difference_type n)
        {
          if(n > difference_type(0))
          {
            circular_pointer += n;

            if(circular_pointer > (buffer_pointer + difference_type(N)))
            {
              circular_pointer -= difference_type(N);
            }
          }
          else if(n < 0)
          {
            *this -= -n;
          }

          return *this;
        }

        circular_iterator& operator-=(difference_type n)
        {
          if(n > difference_type(0))
          {
            circular_pointer -= n;

            if(circular_pointer < buffer_pointer)
            {
              circular_pointer += difference_type(N);
            }
          }
          else if(n < 0)
          {
            *this += -n;
          }

          return *this;
        }

      private:
        pointer buffer_pointer;
        pointer circular_pointer;

        circular_iterator();

        friend inline circular_iterator operator+(const circular_iterator& a, difference_type n) { return circular_iterator(a) += n; }
        friend inline circular_iterator operator-(const circular_iterator& a, difference_type n) { return circular_iterator(a) -= n; }

        friend inline bool operator==(const circular_iterator& a, const circular_iterator& b) { return (a.circular_pointer == b.circular_pointer); }
        friend inline bool operator!=(const circular_iterator& a, const circular_iterator& b) { return (a.circular_pointer != b.circular_pointer); }

        // TBD: Implement operator<().
        // TBD: Implement the remaining operators.
      };
    }

    template<typename T,
             const std::size_t N = std::size_t(16U)>
    class circular_buffer
    {
    public:
      static_assert(N > std::size_t(0U),
                    "Error: The circular_buffer class requires more than zero elements.");

      typedef       T              value_type;
      typedef       value_type*    pointer;
      typedef const value_type*    const_pointer;
      typedef       std::size_t    size_type;
      typedef       std::ptrdiff_t difference_type;
      typedef       value_type&    reference;
      typedef const value_type&    const_reference;

      typedef circular_buffer_detail::circular_iterator<T, N, std::iterator_traits<T*> > iterator;
      typedef circular_buffer_detail::circular_iterator<T, N, std::iterator_traits<const T*> > const_iterator;

      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

      circular_buffer() : buffer (),
                          my_size(difference_type(0)),
                          first  (buffer + difference_type(N)),
                          last   (buffer + difference_type(N))
      {
        std::fill(buffer, buffer + difference_type(N), value_type());
      }

      explicit circular_buffer(const size_type  count,
                               const value_type value = value_type()) : buffer (),
                                                                        my_size(difference_type(count)),
                                                                        first  (buffer + difference_type(N - count)),
                                                                        last   (buffer + difference_type(N))
      {
        std::fill(buffer, buffer + difference_type(N - count), value_type());

        std::fill(buffer + difference_type(N - count), buffer + difference_type(N), value);
      }

      circular_buffer(const circular_buffer& other) : buffer (),
                                                      my_size(difference_type(other.size())),
                                                      first  (buffer + difference_type(other.first - other.buffer)),
                                                      last   (buffer + difference_type(other.last  - other.buffer))
      {
        std::copy(other.buffer, other.buffer + difference_type(N), buffer);
      }

      ~circular_buffer() { }

      circular_buffer& operator=(const circular_buffer& other)
      {
        if(this != &other)
        {
          std::copy(other.buffer, other.buffer + difference_type(N), buffer);

          my_size = difference_type(other.size());

          first = buffer + difference_type(other.first - other.buffer);
          last  = buffer + difference_type(other.last  - other.buffer);
        }

        return *this;
      }

      static size_type capacity() { return N; }

      bool empty() const
      {
        return (my_size == difference_type(0U));
      }

      size_type size() const
      {
        return size_type(my_size);
      }

      void clear()
      {
        first   = buffer;
        last    = buffer + difference_type(N);
        my_size = difference_type(0);
      }

      void push_front(const value_type value)
      {
        --first;

        if(first < buffer)
        {
          first = buffer + difference_type(N - 1U);
        }

        *first = value;

        if(my_size < difference_type(N))
        {
          ++my_size;
        }
      }

      void pop_back()
      {
        if(my_size > difference_type(0))
        {
          --my_size;

          // TBD: Do we actually need to manually call the destructor here?
          last->~value_type();

          --last;

          if(last <= buffer)
          {
            last = buffer + difference_type(N);
          }
        }
      }

      iterator        begin ()       { return iterator      (buffer, first); }
      const_iterator  begin () const { return const_iterator(buffer, first); }
      const_iterator  cbegin() const { return const_iterator(buffer, first); }
      iterator        end   ()       { return iterator      (buffer, last); }
      const_iterator  end   () const { return const_iterator(buffer, last); }
      const_iterator  cend  () const { return const_iterator(buffer, last); }

      reverse_iterator       rbegin ()       { return std::reverse_iterator<iterator>      (iterator      (buffer, last)); }
      const_reverse_iterator rbegin () const { return std::reverse_iterator<const_iterator>(const_iterator(buffer, last)); }
      const_reverse_iterator crbegin() const { return std::reverse_iterator<const_iterator>(const_iterator(buffer, last)); }
      reverse_iterator       rend   ()       { return std::reverse_iterator<iterator>      (iterator      (buffer, first)); }
      const_reverse_iterator rend   () const { return std::reverse_iterator<const_iterator>(const_iterator(buffer, first)); }
      const_reverse_iterator crend  () const { return std::reverse_iterator<const_iterator>(const_iterator(buffer, first)); }

      reference       front ()       { return *begin(); }
      const_reference front () const { return *begin(); }
      reference       back  ()       { return *(end() - iterator::difference_type(1)); }
      const_reference back  () const { return *(cend() - const_iterator::difference_type(1)); }

    private:
      value_type      buffer[N];
      difference_type my_size;
      pointer         first;
      pointer         last;
    };
  }

  /*
  #include <algorithm>
  #include <iostream>
  #include <iterator>
  #include <util/utility/util_circular_buffer.h>

  template<typename circular_buffer_type>
  void do_something()
  {
    circular_buffer_type cb(1U, 1U);

    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;
    cb.push_front(2U);
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;
    cb.push_front(3U);
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    cb.pop_back();
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;
    cb.pop_back();
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;
    cb.pop_back();
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    cb.push_front(101U);
    cb.push_front(102U);
    cb.push_front(103U);
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    for(auto it = cb.cbegin();  it != cb.cbegin() + cb.size();  ++it) { std::cout << *it << std::endl; }
    for(auto it = cb.crbegin(); it != cb.crend(); ++it) { std::cout << *it << std::endl; }

    cb.pop_back();
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    cb.pop_back();
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    cb.push_front(42U);
    std::cout << cb.size() << ", " << cb.front() << ", " << cb.back() << std::endl;

    circular_buffer_type other_cb;

    other_cb = cb;

    volatile unsigned debug = 0U;

    static_cast<void>(debug);
  }

  int main()
  {
    do_something<util::circular_buffer<unsigned, 3U>>();
  }
*/

#endif // UTIL_CIRCULAR_BUFFER_2007_11_22_H_
