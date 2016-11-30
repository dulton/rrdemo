/** \copyright The MIT License */
#include "thread-lcd.hpp"

#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QLCDNumber>

namespace rrdemo {
namespace cdom {
namespace qt {

ThreadLcdMainWindow::ThreadLcdMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget *widget {new QWidget(this)};

    QVBoxLayout *layout {new QVBoxLayout};
    widget->setLayout(layout);

    QLCDNumber *lcdNumber {new QLCDNumber(this)};
    layout->addWidget(lcdNumber);

    QPushButton *button {new QPushButton(tr("Start"), this)};
    layout->addWidget(button);

    setCentralWidget(widget);

    QTimer *timer {new QTimer(this)};
    connect(timer, &QTimer::timeout, [lcdNumber]() {
        static int sec {0};
        lcdNumber->display(QString::number(sec++));
    });

    ThreadLcdTask *task {new ThreadLcdTask};
    QThread *thread {new QThread(this)};
    task->moveToThread(thread);

    connect(thread, &QThread::started, task, &ThreadLcdTask::task);
    connect(task, &ThreadLcdTask::completed, thread, &QThread::quit);
    connect(task, &ThreadLcdTask::completed, timer, &QTimer::stop);
    connect(thread, &QThread::finished, task, &ThreadLcdTask::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(button, &QPushButton::clicked, [=]() {
        timer->start(1);
        thread->start();
    });
}

void ThreadLcdTask::task()
{
    static Q_CONSTEXPR int ALL {1000000000};

    for (int i {0}; i < ALL; i++)
        Q_EMIT step(i, ALL);

    Q_EMIT completed();
}

}// namespace qt
}// namespace cdom
}// namespace rrdemo

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[])
{
    using namespace rrdemo::cdom::qt;

    QApplication app(argc, argv);

    ThreadLcdMainWindow main_window;
    main_window.show();

    return app.exec();
}
#endif// ENTRY SWITCH
