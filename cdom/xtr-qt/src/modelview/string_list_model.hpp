/** \file
 *  \author zhengrr
 *  \date 2016-12-5
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMQT_STRINGLISTMODEL_HPP
#define _RRDEMOCDOMQT_STRINGLISTMODEL_HPP

#include <QDialog>
#include <QStringListModel>

namespace rrdemo {
namespace cdom {
namespace qt {

namespace Ui {
class StringListModel;
}

class StringListModel : public QDialog {
    Q_OBJECT

public:
    explicit StringListModel(QWidget *parent = Q_NULLPTR);
    void initialize();
    ~StringListModel();

private:
    Q_DISABLE_COPY(StringListModel);
    explicit StringListModel(StringListModel&&) Q_DECL_EQ_DELETE;
    StringListModel &operator=(StringListModel&&)Q_DECL_EQ_DELETE;

    bool initialized {false};

private Q_SLOTS:
    void on_insertButton_clicked();
    void on_deleteButton_clicked() const;

private:
    Ui::StringListModel *ui {Q_NULLPTR};

    QStringListModel *model {Q_NULLPTR};

};// class StringListModel

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMQT_STRINGLISTMODEL_HPP
