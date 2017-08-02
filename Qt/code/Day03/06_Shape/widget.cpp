#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //去除边框
    //windowFlags()是获取并在原有的基础上加上去除边框的属性
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把背景设置为透明
    //Qt::WA_TranslucentBackground，该枚举变量需要和Qt::FramelessWindowHint一起使用
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800,800);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,QPixmap("../06_Shape/Image/QShape.gif"));
}
void Widget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::RightButton){
        //右键关闭
        close();
    }else if(ev->button() == Qt::LeftButton){
        //求点击点与左上角的坐标差值
        //frameGeometry()获取的是一个矩形，topLeft()获取的是这个矩形的左上角坐标
        point = ev->globalPos() - this->frameGeometry().topLeft();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton){
        move(ev->globalPos() - point);
    }
}

