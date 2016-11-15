/** \file
 *  \author zhengrr
 *  \date 2016-10-21 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_DIALOGWITHOUTBUTTONS_HPP
#define _RRDEMOCDOMQT_DIALOGWITHOUTBUTTONS_HPP

#include <QDialog>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class DialogWithoutButtons;
}

/// 不带按钮的对话框。
/**
*/
class DialogWithoutButtons : public QDialog {
    Q_OBJECT

public:
    explicit DialogWithoutButtons(QWidget *parent = nullptr);
    explicit DialogWithoutButtons(const DialogWithoutButtons &) = delete;
    explicit DialogWithoutButtons(DialogWithoutButtons &&) = delete;
    DialogWithoutButtons &operator=(const DialogWithoutButtons &) = delete;
    DialogWithoutButtons &operator=(DialogWithoutButtons &&) = delete;
    ~DialogWithoutButtons();

private:
    Ui::DialogWithoutButtons *ui {nullptr};
};// class DialogWithoutButtons

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_DIALOGWITHOUTBUTTONS_HPP
