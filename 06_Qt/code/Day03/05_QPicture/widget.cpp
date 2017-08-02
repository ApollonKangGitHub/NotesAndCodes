#include "widget.h"
#include "ui_widget.h"
#include <QPicture>
#include <QPainter>
#include <QBitmap>
#include <QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPicture picture;

    QPainter p;
    p.begin(&picture);

    //定义画笔对象
    QPen pen;
    pen.setWidth(5);                    //设置线宽
    pen.setColor(QColor(0,255,0));     //通过RGB设置颜色
    pen.setStyle(Qt::DashDotLine);      //设置线型
    //把画笔设置给画家
    p.setPen(pen);

    p.drawPixmap(105,105,390,390,QBitmap("../05_QPicture/Image/QPicture.gif"));
    //画线(起点坐标,终点坐标)
    p.drawLine(100,500,500,500);
    p.drawLine(100,100,500,100);
    p.drawLine(500,100,500,500);
    p.drawLine(100,100,100,500);

    p.end();
    picture.save("../05_QPicture/Image/picture.png");   //QPicture是保存为二进制文件
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
#if 1
    QPicture pic;
    pic.load("../05_QPicture/Image/picture.png");    //加载二进制文件
    p.drawPicture(0,0,pic); //将二进制文件按照格式画在窗口上
#endif
#if 1
    //QPixmap-->QImage
    QPixmap pixmap;
    pixmap.load("../05_QPicture/Image/QPicture.gif");
    QImage tempImage = pixmap.toImage();
    p.drawImage(500,0,tempImage.scaled(100,100));

    //QImage-->QPixmap
    QImage image;
    image.load("../05_QPicture/Image/QPicture.gif");
    QPixmap tempPixmap = QPixmap::fromImage(image);
    p.drawPixmap(0,0,100,100,tempPixmap);
#endif
}
