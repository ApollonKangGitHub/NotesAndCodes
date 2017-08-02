#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //自定义类对象分配空间
    mythread = new MyThread;
    //创建子线程
    thread = new QThread(this);

    //将自定义线程模块添加到子线程
    mythread->moveToThread(thread);

    //启动子线程，但是并没有启动线程处理函数
    thread->start();

    //线程处理函数必须通过signal - slot来处理
    connect(ui->pushButton, &QPushButton::pressed, mythread, &MyThread::drawImage);
    connect(mythread,&MyThread::updateImage,this,&Widget::getImage);
    connect(this,&Widget::destroyed,this,&Widget::dealClose);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealClose()
{
    //退出子线程
    thread->quit();
    //回收资源
    thread->wait();
    delete mythread;
}
void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);//创建画家，指定绘图设备为窗口
    p.drawImage(50,50,image);
}
void Widget::getImage(QImage temp)
{
    image = temp;
    update();//更新窗口，间接调用paintEvent()
}
