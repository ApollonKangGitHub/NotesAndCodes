#include "widget.h"
#include "ui_widget.h"
#include <QPixMap>
#include <QBitMap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    //比较QPixMap与QBitMap的不同对象画出来的图有何区别
    QPainter p(this);
    p.drawPixmap(0,0,400,400,QPixmap(":/new/prefix1/Image/26610354_59.gif"));
    p.drawPixmap(450,0,400,400,QBitmap(":/new/prefix1/Image/26610354_59.gif"));

    //也可以现指定路径再画
    QPixmap pixmap;
    pixmap.load(":/new/prefix1/Image/26610354_59.gif");
    p.drawPixmap(900,0,400,400,pixmap);

    //QBitmap只能显示黑白两种颜色
}
