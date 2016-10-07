/* ************************************************************************//*!
 * \file
 * \brief Unit Conversion - Length
 * \author zhengrr
 * \date 2016-1-8 ~ 7-19
 * \copyright The MIT License
 ******************************************************************************/

#ifndef RECT_HH
#define RECT_HH

class Rect {
   explicit Rect(const Rect &) = delete;
   //explicit Rect(Rect &&) = delete;
   Rect &operator=(const Rect &) = delete;
   Rect &operator=(Rect &&) = delete;

public:
   explicit Rect(const double width, const double height) {
      this->width = width;
      this->height = height;
   }
   ~Rect(void) = default;

private:
   double width {0.};
   double height {0.};

public:
   inline double w(const double ratio = 1.) const { return ratio * width; }
   inline double h(const double ratio = 1.) const { return ratio * height; }

   static Rect &Screen(void);

   inline Rect &operator*=(const double ratio) {
      width *= ratio;
      height *= ratio;
      return *this;
   }

   inline Rect &operator/=(const double ratio) {
      width /= ratio;
      height /= ratio;
      return *this;
   }
};

inline Rect &operator*(const double lt, const Rect &rt) {
   return Rect(lt * rt.w(), lt * rt.h());
}

inline Rect &operator*(const Rect &lt, const double rt) {
   return rt * lt;
}

#endif  // RECT_HH
