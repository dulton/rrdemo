/** \file
 *  \author zhengrr
 *  \date 2016-10-21
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCPPQT_WIDGET_HPP
#define _RRDEMOCPPQT_WIDGET_HPP

#include <QWidget>

namespace rrdemo {
namespace cpp {
namespace qt {

namespace Ui {
class Widget;
}

/// 部件
/**
*/
class Widget : public QWidget {
   Q_OBJECT

public:
   explicit Widget(QWidget *parent = nullptr);
   explicit Widget(const Widget &) = delete;
   explicit Widget(Widget &&) = delete;
   Widget &operator=(const Widget &) = delete;
   Widget &operator=(Widget &&) = delete;
   ~Widget();

private:
   Ui::Widget *ui {nullptr};
};// class Widget

}// namespace qt
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_WIDGET_HPP
