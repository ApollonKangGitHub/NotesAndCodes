#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建一个绘图设备，QImage::Format_ARGB32是透明背景色
    QImage image(800,600,QImage::Format_ARGB32);
    QPainter p;
    p.begin(&image);

    //当前在build文件中，上一级目录包含04_QImage
    p.drawImage(0,0,QImage("../04_QImage/Image/QImage.png"));
#if 1
    for(int i = 0; i < 50; i++){
        for(int j = 0; j<50; j++){
            image.setPixel(QPoint(i,j),qRgb(0,255,255));//修改像素点，很少用到
            //image.pixel(QPoint(i,j));//获取像素点
        }
    }
#endif
    p.end();
    image.save("../04_QImage/Image/image.png");
}

Widget::~Widget()
{
    delete ui;
}
