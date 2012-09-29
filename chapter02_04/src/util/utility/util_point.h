#ifndef _UTIL_POINT_2008_11_22_H_
  #define _UTIL_POINT_2008_11_22_H_

  namespace util
  {
    template<typename x_type,
              typename y_type = x_type>
    class point
    {
    public:
      x_type x;
      y_type y;

      point(const x_type& x_ = x_type(),
            const y_type& y_ = y_type()) : x(x_),
                                            y(y_) { }

      bool operator<(const point& other) const
      {
        return (x < other.x);
      }
    };
  }

#endif // _UTIL_POINT_2008_11_22_H_
