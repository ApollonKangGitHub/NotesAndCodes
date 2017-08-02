#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <unistd.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout, this, &Widget::dealTimeout);
    //分配线程对象空间,构建线程对象，启动后进行操作
    thread = new MyThread(this);

    //当按窗口右上角关闭“x”的时候触发信号destroyed
    connect(this,&Widget::destroyed,this,&Widget::stopThread);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::dealTimeout()
{
    static int i = 0;
    ++i;
    //设定LCD的值
    ui->lcdNumber->display(i);
}

void Widget::on_pushButton_clicked()
{
    if(myTimer->isActive() == false){   //定时器没有启动（活动状态）
        myTimer->start(100);            //启动，设定时间间隔100ms
        ui->lineEdit->setText("线程开始操作，定时器启动");
    }
#if 0
    //复杂的数据处理，耗时较长
    for(int i = 10000; i>0; i--){
        //usleep(100);          //这个函数对于界面操作似乎无影响
        QThread::usleep(100);
    }

    ui->lineEdit->setText("数据处理完毕，定时器运行中");
    //单任务，必须等for循环中的内容处理完成后定时器才能工作
    //因为for肯定是先抢占CPU资源，CPU腾不出时间给定时器
    //所以启动新线程进行操作
#endif

    //启动线程处理数据
    thread->start();
    connect(thread, &MyThread::isDone, this, &Widget::dealDone);
}
void Widget::dealDone()
{
    ui->lineEdit->setText("线程结束操作，定时器关闭");
    myTimer->stop();
}

void Widget::stopThread()
{
    //当线程处理完毕后，停止线程
    thread->quit();
    //等待线程处理完成，回收资源类似于POSIX pthread_join()
    thread->wait();
}
