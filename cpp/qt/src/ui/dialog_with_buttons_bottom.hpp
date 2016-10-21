/** \file
 *  \author zhengrr
 *  \date 2016-10-21
 *  \copyright The MIT License
 */

#ifndef _RRDEMOCPPQT_DIALOGWITHBUTTONSBOTTOM_HPP
#define _RRDEMOCPPQT_DIALOGWITHBUTTONSBOTTOM_HPP

#include <QDialog>

namespace rrdemo {
namespace cpp {
namespace qt {

namespace Ui {
class DialogWithButtonsBottom;
}

/// 带底部按钮的对话框
/**
 */
class DialogWithButtonsBottom : public QDialog {
   Q_OBJECT

public:
   explicit DialogWithButtonsBottom(QWidget *parent = nullptr);
   explicit DialogWithButtonsBottom(const DialogWithButtonsBottom &) = delete;
   explicit DialogWithButtonsBottom(DialogWithButtonsBottom &&) = delete;
   DialogWithButtonsBottom &operator=(const DialogWithButtonsBottom &) = delete;
   DialogWithButtonsBottom &operator=(DialogWithButtonsBottom &&) = delete;
   ~DialogWithButtonsBottom();

private:
   Ui::DialogWithButtonsBottom *ui {nullptr};
};// class DialogWithButtonsBottom

}// namespace qt
}// namespace cpp
}// namespace rrdemo

#endif// _RRDEMOCPPQT_DIALOGWITHBUTTONSBOTTOM_HPP
