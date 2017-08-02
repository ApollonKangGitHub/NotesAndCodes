#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //绘图设备400*300
    QPixmap pixmap(400,300);
    QPainter p(&pixmap);


    p.fillRect(0,0,400,300,QBrush(Qt::white));          //通过画刷填充背景色
    //pixmap.fill(Qt::white);                           //通过绘图设备填充背景色

    p.drawPixmap(0,0,400,300,QPixmap(":/new/prefix1/Image/QPixmap.png"));

    //保存
    pixmap.save("../03_QPixmap/Image/pixmap.png");
    //pixmap.save("../03_QPixmap/Image/pixmap.jpg");
}

Widget::~Widget()
{
    delete ui;
}
