#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
protected:
    //键盘按下事件
    void keyPressEvent(QKeyEvent *);
    //定时器事件
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    bool event(QEvent *);
    bool eventFilter(QObject *, QEvent *);
private:
    Ui::MyWidget *ui;
    int timerID_fast;        //区分不同定时器，类似于文件描述符
    int timerID_slow;
};

#endif // MYWIDGET_H
