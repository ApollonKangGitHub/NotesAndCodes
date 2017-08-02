#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QString>
class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);
    void sendSlot();
signals:
    /*
     * 自定义信号必须由该关键字声明，信号不可以有返回值，但是可以有参数，
     * 信号就是函数的声明，没有定义，使用时：emit mySignal();即可
    */
    void mySignal();
    void mySignal(int,QString); //只需声明无需实现，QString与string用法差不多

public slots:

private:
    QPushButton b;
};

#endif // SUBWIDGET_H
