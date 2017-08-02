#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    //比较复杂的数据处理，提到线程中
    QThread::sleep(3);
    emit isDone();
}
