#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

protected:
    void run(); //基类是保护类型，当然这里是public也是可以的
signals:
    void isDone();

public slots:
};

#endif // MYTHREAD_H
