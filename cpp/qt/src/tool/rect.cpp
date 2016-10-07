/* ************************************************************************//*!
 * \copyright The MIT License
 ******************************************************************************/

#include "rect.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

Rect &Rect::Screen(void) {
  QRect screen(QApplication::desktop()->screenGeometry());
  return Rect(screen.width(), screen.height());
}
