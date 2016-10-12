/* ************************************************************************//*!
 * \file
 * \brief Unit Conversion - Length
 * \author zhengrr
 * \date 2016-1-8 ~ 7-19
 * \copyright The MIT License
 ******************************************************************************/

#ifndef UNCNV__LEN_HPP
#define UNCNV__LEN_HPP

namespace uncnv {

class Length {
   explicit Length(const Length &) = delete;
   //explicit Length(Length &&) = delete;
   Length &operator=(const Length &) = delete;
   Length &operator=(Length &&) = delete;

public:
   explicit Length(const double metre) { length = metre; }
   ~Length(void) = default;

private:
   double length {0.};

public:
#define DECLI static inline Length &
#define DECLO inline double

   /* SI */
   DECLI m(const double metre) { return Length(metre); }
   DECLO m(void) const { return length; }

   DECLI dam(const double decametre) { return m(decametre * 10.); }
   DECLO dam(void) const { return m() / 10.; }
   // 10
   // m
   // 10
   DECLI dm(const double decimetre) { return m(decimetre / 10.); }
   DECLO dm(void) const { return m() * 10.; }
   // 10
   DECLI cm(const double centimetre) { return m(centimetre / 100.); }
   DECLO cm(void) const { return m() * 100.; }
   // 10
   DECLI mm(const double millimetre) { return m(millimetre / 1000.); }
   DECLO mm(void) const { return m() * 1000.; }

   /* Imperial */
   DECLI yd(const double yard) { return m(yard * .9144); }
   DECLO yd(void) const { return m() / .9144; }
   // 3
   DECLI ft(const double foot) { return m(foot * .3048); }
   DECLO ft(void) const { return m() / .3048; }
   // 12
   DECLI in(const double inch) { return m(inch * .0254); }
   DECLO in(void) const { return m() / .0254; }

   /* Typographic */
   DECLI pica(const double pica) { return in(pica / 6.); }
   DECLO pica(void) const { return in() * 6.; }
   // 12
   DECLI pt(const double point) { return pica(point / 12.); }
   DECLO pt(void) const { return in() * 72.; }

   /* Other */
   DECLI px(const int pixel, const int dpi) {
      return in(static_cast<double>(pixel) / static_cast<double>(dpi));
   }
   inline int px(const int dpi) {
      return static_cast<int>(dpi * in());
   }

#undef DECLI
#undef DECLO
};  // class Length

}  // namespace uncnv

#endif  // UNCNV__LEN_HPP
