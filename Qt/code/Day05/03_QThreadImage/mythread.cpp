#include "mythread.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <time.h>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}
//线程画图
void MyThread::drawImage()
{
    //定义绘图设备
    QImage image(500,500,QImage::Format_ARGB32);

    //定义画家，指定绘图设备
    QPainter painter(&image);

    //定义画笔对象
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);

    //定义画刷
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);//设置风格
    brush.setColor(Qt::green);
    painter.setBrush(brush);

    qsrand(time(NULL));
    //定义3个点
    QPoint a[] = {
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
    };

    painter.drawPolygon(a,3);//画三角形

    //通过信号发送图片
    emit updateImage(image);
}
