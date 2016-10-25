/** \file
 *  \author zhengrr
 *  \date 2016-10-21
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCPPQT_DIALOGWITHOUTBUTTONS_HPP
#define _RRDEMOCPPQT_DIALOGWITHOUTBUTTONS_HPP

#include <QDialog>

namespace rrdemo {
namespace cpp {
namespace qt {

namespace Ui {
class DialogWithoutButtons;
}

/// 不带按钮的对话框
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
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_DIALOGWITHOUTBUTTONS_HPP
