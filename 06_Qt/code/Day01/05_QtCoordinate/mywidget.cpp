#include "mywidget.h"
#include "mybutton.h"   //用于析构释放内存
#include <unistd.h>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    //正数向右下偏移，负数向左上偏移，直至于偏出屏幕都可以
    this->resize(500,300);
    this->setWindowTitle("I Love You");
#if 1
    Love = new QPushButton(this);
    Love->move(100,100);
    Love->resize(300,100);
    Love->setText("I love you!");
    Hate = new QPushButton(Love);
    Hate->move(0,0);
    Hate->resize(100,30);
    Hate->setText("I Hate you!");

#endif
#if 0
    this->show();
    int x=0,y=0;
    for(x=0,y=0;x<800&&y<400;x+=30,y+=20){
        this->move(x,y);
        sleep(1);
    }
    for(;x<1200&&y<600;x+=30,y-=20){
        this->move(x,y);
        sleep(1);
    }
#endif
    //即使没有释放内存，但是由于既传承了QPushButton，所以系统会根据建立的对象树自动释放
    myButton * free_mem = new myButton(this);
    free_mem->setText("delete memory");
    myButton * free_mem2 = new myButton(this);
    free_mem2->setText("delete memory2");
    free_mem2->move(50,50);
    //两个QPushbutton的子类对象各自调用一次析构器
}

MyWidget::~MyWidget()
{
    qDebug()<< "MyWidget对象已经析构";
    //释放的是主窗口，不是按钮(按钮在QPushButton的析构器中释放)
    //执行一次
}
