#include "mylabel.h"
#include <QMouseEvent>
#include <qDebug>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    //设定追踪鼠标，一开始运行就追踪而不是需要先按下键才会追踪
    this->setMouseTracking(true);
}

//鼠标按下事件处理函数
void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        qDebug() << "Left";
    }else if(ev->button() == Qt::RightButton){
        qDebug() << "Right";
    }else if(ev->button() == Qt::MidButton){
        qDebug() << "Middle";
    }
    /*
     * QString str = QString("abc %1 ^_^ %2").arg(123456).arg("ABCDEF");
     * str = abc 123456 ^_^ ABCDEF
    */
    int i = ev->x();
    int j = ev->y();
    QString str = QString("<center><h1>Mouse Press:(%1, %2)</h1></center>").arg(i).arg(j);
    this->setText(str);
}
//鼠标抬起事件处理函数
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QString str = QString("<center><h1>Mouse Release:(%1, %2)</h1></center>").arg(ev->x()).arg(ev->y());
    this->setText(str);
}
//鼠标移动事件处理函数
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QString str = QString("<center><h1>Mouse Move:(%1, %2)</h1></center>").arg(ev->x()).arg(ev->y());
    //this->setText(str);
}
//鼠标位于标签内
void MyLabel::enterEvent(QEvent * ev)
{
    QString str = QString("<center><h1>Mouse Enter</h1></center>");
    this->setText(str);
}
//鼠标位于标签外
void MyLabel::leaveEvent(QEvent *ev)
{
    QString str = QString("<center><h1>Mouse Leave</h1></center>");
    this->setText(str);
}
