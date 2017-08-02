#include "mainwidget.h"
#include<unistd.h>
#include<QDebug>    //Debug输出
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);
    b1.setText("close");
    b1.move(100,100);

    b2 = new QPushButton(this);
    b2->setText("donothing");
    b2->move(200,100);

    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);
    /*
     * &b1：信号发出者，为一个指针
     * &QPushButton::pressed：要处理的信号，格式-->&发送者对象的类名::信号名字
     * this：信号接收者，为一个指针
     * &MainWidget::close：槽函数(信号处理函数),格式-->&接收者对象的类名::槽函数名字
     *
    */

    //自定义槽：就是普通的函数，但是需要与信号一致(参数、返回值)
    //由于信号没有返回值，所以槽一定有返回值

    //b2发送信号、b2接收信号：按键按下时修改b2
    connect(b2, &QPushButton::pressed, this, &MainWidget::mySlot);
    //b2发送信号、b1接收信号：按键按下时隐藏b1
    connect(b2, &QPushButton::pressed, &b1, &QPushButton::hide);   //hide(隐藏槽函数)
    //b2发送信号、b1接收信号：按键抬起时显示b1
    connect(b2, &QPushButton::released, &b1, &QPushButton::show);

    setWindowTitle("Big Boss"); //this->setWindowTitle("Big Boss");
    this->resize(500,300); //设置窗口大小

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(300,100);

    //显示子窗口
    //w.show();

    //给子窗口发送信号
    connect(&b3, &QPushButton::released, this, &MainWidget::ChangeWindow);

    //处理子窗口的自信号
    //采用函数指针对重载的信号/槽分别进行区分，不进行区分的话会有二义性
#if 1
    void (SubWidget::*pNoParaSignal)() = SubWidget::mySignal;
    void (MainWidget::*pdealNoParaSub)() = MainWidget::dealSub;
    connect(&w, pNoParaSignal, this, pdealNoParaSub);

    void (SubWidget::*pParaSignal)(int,QString) = SubWidget::mySignal;
    void (MainWidget::*pdealParaSub)(int,QString) = MainWidget::dealSub;
    connect(&w, pParaSignal, this, pdealParaSub);
#endif

    //下面这种方式是需要在头文件中声明槽函数类型的："public slots:"
    //但是由于SIGNAL与SLOT是宏函数，它们将括号中的函数名字转换成字符串，不进行错误检查所以很容易出错
#if 0
    connect(&w, SIGNAL(mySignal()), this, SLOT(dealSub()));
    connect(&w, SIGNAL(mySignal(int,QString)), this, SLOT(dealSub(int,QString)));
#endif
}

void MainWidget::mySlot()
{
    b2->setText("DONOTHING");
}
void MainWidget::ChangeWindow()

{
    //隐藏主窗口
    this->hide();
    sleep(0.5); //延时可以看一下这个过程
    //显示子窗口
    w.show();
}
void MainWidget::dealSub()
{
    //显示主窗口
    this->show();
    sleep(0.5);
    //隐藏子窗口
    w.hide();
}
void MainWidget::dealSub(int value,QString str)
{
    //qDebug() << str << ":" << value;
    qDebug() << str.toUtf8().data() << ":" << value;
    //中文可能需要转Utf8编码
    //由于toUtf8()转换成了QByteArray类型，不是字符串，所以需要转换成char*的字符串
    //原型：QByteArray QString::toUtf8() const
    //原型：char * QByteArray::data()
}
MainWidget::~MainWidget()
{
    delete b2;
}
