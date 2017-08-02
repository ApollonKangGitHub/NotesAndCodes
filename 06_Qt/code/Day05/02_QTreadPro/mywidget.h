#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void dealSignal();
    void dealClose();

signals:
    void startThread(); //启动子线程处理函数的信号
private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::MyWidget *ui;
    MyThread * mythread;
    QThread * thread;
};

#endif // MYWIDGET_H
