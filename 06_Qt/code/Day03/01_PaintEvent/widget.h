#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    //重写绘图事件，虚函数
    //如果在窗口绘图，必须放在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘时调用(窗口状态改变时：如放大、缩小...)
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int x;
};

#endif // WIDGET_H
