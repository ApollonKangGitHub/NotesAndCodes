#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //①自定义线程类对象动态分配空间，不能指定父对象,否则第三步不能成功
    mythread = new MyThread;

    //②子线程分配空间
    thread = new QThread(this);

    //③把自定义线程加入到子线程中
    mythread->moveToThread(thread);

    //处理子线程发送的信号
    connect(mythread,&MyThread::mySignal,this,&MyWidget::dealSignal);
    qDebug() << "主线程号：" << QThread::currentThread();
    connect(this,&MyWidget::startThread,mythread,&MyThread::myTimeout);
    connect(this,&MyWidget::destroyed,this,&MyWidget::dealClose);

    //线程处理函数内部，绝对不允许操作图形界面
    //因为线程主要用于后台运行的数据处理

    //connect()的第五个参数链接方式：在多线程使用时才有意义
    #if 0
    Qt::AutoConnection//默认参数，如果是单线程默认使用直接方式，如果是多线程默认使用队列
    Qt::DirectConnection//直接,槽函数(myTimeout())和信号接收者在同一个线程，即打印的是两个线程的ID
    Qt::QueuedConnection//队列,槽函数(myTimeout())和信号发送者在同一个线程，即打印的是一个线程的ID
    #endif
}

void MyWidget::dealSignal()
{
    static int i=0;
    i++;
    ui->lcdNumber->display(i);
}
vodi MyWidget::dealClose()
{
    on_pushButtonStop_clicked();
    delete mythread;    //没有指定父对象，需要手动释放
}
MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButtonStart_clicked()
{
    if(thread->isRunning() == true){
        return;
    }
    //启动线程但是没有启动线程处理函数
    thread->start();
    mythread->setFlag(false);
    //调用线程处理函数不能直接调用
    //直接调用会导致线程处理函数和主线程在同一个线程
    //mythread->myTimeout();

    //只能通过“signal - slot”的方式来调用
    emit startThread();
}

void MyWidget::on_pushButtonStop_clicked()
{
    if(thread->isRunning() == false){
        return;
    }
    mythread->setFlag(true);
    thread->quit();
    thread->wait();
}
