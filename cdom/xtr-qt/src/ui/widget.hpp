/** \file
 *  \author zhengrr
 *  \date 2016-10-21 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_WIDGET_HPP
#define _RRDEMOCDOMQT_WIDGET_HPP

#include <QWidget>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class Widget;
}

/// 部件。
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
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_WIDGET_HPP
