/** \copyright The MIT License */
#include "string_list_model.hpp"
#include "ui_string_list_model.h"

#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>

namespace {
Q_CONSTEXPR QStringList DEFAULT_DATA {
    "DEFAULT DATA A", "DEFAULT DATA B", "DEFAULT DATA C"};
}// namespace

namespace rrdemo {
namespace cdom {
namespace qt {

StringListModel::StringListModel(QWidget *parent) :
QDialog(parent), ui {new Ui::StringListModel}
{
    Q_CHECK_PTR(ui);
    ui->setupUi(this);
}

void StringListModel::initialize()
{
    Q_ASSERT(!initialized);

    Q_ASSERT(!model);
    model = new QStringListModel(this);  Q_CHECK_PTR(model);
    model->setStringList(DEFAULT_DATA);

    ui->listView->setModel(model);
    ui->comboBox->setModel(model);

    initialized = true;
}


StringListModel::~StringListModel()
{
    delete ui;  ui = Q_NULLPTR;
}

void StringListModel::on_insertButton_clicked()
{
    Q_ASSERT(initialized);

    bool ok;
    QString text {QInputDialog::getText(this, tr("Insert"),
                                        tr("New data:"),
                                        QLineEdit::Normal,
                                        tr("USER DARA "),
                                        &ok)};
    if (ok) {
        int row {ui->listView->currentIndex().isValid() ?
            ui->listView->currentIndex().row() : model->rowCount()};
        model->insertRow(row);
        model->setData(model->index(row), text);
    }
}

void StringListModel::on_deleteButton_clicked() const
{
    Q_ASSERT(initialized);

    if (ui->listView->currentIndex().isValid())
        model->removeRow(ui->listView->currentIndex().row());
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo

namespace {
int altmain(int argc, char *argv[])
{
    QApplication app(argc, argv);

    rrdemo::cdom::qt::StringListModel ui;
    ui.initialize();
    ui.show();

    return app.exec();
}
}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITCH
