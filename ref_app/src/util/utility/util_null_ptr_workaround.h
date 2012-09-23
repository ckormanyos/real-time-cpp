#ifndef _UTIL_NULL_PTR_WORKAROUND_2010_12_06_H_
  #define _UTIL_NULL_PTR_WORKAROUND_2010_12_06_H_

  // Provide a nullptr workaround for C++ compilers not yet supporting it.

  class nullptr_t
  {
  public:
    template<typename T>
    operator T*() const { return static_cast<T*>(0U); }

    template<typename C, typename T>
    operator T C::*() const { return static_cast<T C::*>(0U); }

  private:
    void operator&() const;
  };

  template<typename T> inline bool operator==(const T* p, const nullptr_t&) { return (static_cast<const T*>(0U) == p); }
  template<typename T> inline bool operator!=(const T* p, const nullptr_t&) { return (static_cast<const T*>(0U) != p); }

  template<typename T> inline bool operator==(T* p, const nullptr_t&) { return (static_cast<T*>(0U) == p); }
  template<typename T> inline bool operator!=(T* p, const nullptr_t&) { return (static_cast<T*>(0U) != p); }

  template<typename T> inline bool operator==(const nullptr_t&, const T* p) { return (static_cast<const T*>(0U) == p); }
  template<typename T> inline bool operator!=(const nullptr_t&, const T* p) { return (static_cast<const T*>(0U) != p); }

  template<typename T> inline bool operator==(const nullptr_t&, T* p) { return (static_cast<T*>(0U) == p); }
  template<typename T> inline bool operator!=(const nullptr_t&, T* p) { return (static_cast<T*>(0U) != p); }

  constexpr nullptr_t nullptr = { };

#endif // _UTIL_NULL_PTR_WORKAROUND_2010_12_06_H_
