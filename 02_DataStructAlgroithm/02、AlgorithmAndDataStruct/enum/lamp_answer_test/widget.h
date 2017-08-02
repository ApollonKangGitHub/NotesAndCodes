#ifndef WIDGET_H
#define WIDGET_H

#include "bitoper.h"
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
    void initLamp();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
private slots:
    void on_buttonRestart_clicked();

    void on_buttonPrompt_clicked();

private:
    Ui::Widget *ui;

    //用于创建初始矩阵与寻找矩阵求解方案的类
    bitOper lamp;
    //起点坐标、终点坐标
    QPoint startPoint;
    QPoint endPoint;
    //每一格的高度与宽度
    int gridHigh;
    int gridWidth;

    bool pressFlag;
};

#endif // WIDGET_H
