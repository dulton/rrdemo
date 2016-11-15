/** \file
 *  \author zhengrr
 *  \date 2016-10-21 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_TABWIDGET_HPP
#define _RRDEMOCDOMQT_TABWIDGET_HPP

#include <QTabWidget>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    explicit TabWidget(const TabWidget &) = delete;
    explicit TabWidget(TabWidget &&) = delete;
    TabWidget &operator=(const TabWidget &) = delete;
    TabWidget &operator=(TabWidget &&) = delete;
    ~TabWidget();

private:
    Ui::TabWidget *ui;
};// TabWidget

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_TABWIDGET_HPP
