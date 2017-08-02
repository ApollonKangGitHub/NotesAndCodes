#include "mythread.h"
#include <QThread>
#include <QDebug>
MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = false;
}

void MyThread::myTimeout()
{
    while(false == isStop){
        QThread::sleep(1);
        emit mySignal();//每隔1s钟发送一个信号
        qDebug() << "子线程号：" << QThread::currentThread();
        if(true == isStop){
            break;
        }
    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;
}
