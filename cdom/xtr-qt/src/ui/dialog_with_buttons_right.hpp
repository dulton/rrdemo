/** \file
 *  \author zhengrr
 *  \date 2016-10-21 – 11-15
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_DIALOGWITHBUTTONSRIGHT_HPP
#define _RRDEMOCDOMQT_DIALOGWITHBUTTONSRIGHT_HPP

#include <QDialog>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class DialogWithButtonsRight;
}

/// 带右侧按钮的对话框。
/**
*/
class DialogWithButtonsRight : public QDialog {
    Q_OBJECT

public:
    explicit DialogWithButtonsRight(QWidget *parent = nullptr);
    explicit DialogWithButtonsRight(const DialogWithButtonsRight &) = delete;
    explicit DialogWithButtonsRight(DialogWithButtonsRight &&) = delete;
    DialogWithButtonsRight &operator=(const DialogWithButtonsRight &) = delete;
    DialogWithButtonsRight &operator=(DialogWithButtonsRight &&) = delete;
    ~DialogWithButtonsRight();

private:
    Ui::DialogWithButtonsRight *ui {nullptr};
};// class DialogWithButtonsRight

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_DIALOGWITHBUTTONSRIGHT_HPP
