#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>
#include <QImage>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    void getImage(QImage);//槽函数
    void dealClose();//窗口关闭槽函数
private:
    Ui::Widget *ui;
    QImage image;
    MyThread * mythread;    //自定义线程
    QThread * thread;
};

#endif // WIDGET_H
