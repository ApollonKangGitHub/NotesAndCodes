#include "mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Lamda表达式");
    this->resize(250,250);
    lamda_b.setParent(this);
    lamda_b.setText("Yes");
    lamda_b.move(100,100);

    int a = 10;

    //注意：lamda为C++11特性，需要在.pro 文件中加上"CONFIG += C++11"
    //not captured没有捕获
    //[=]表示把函数外部所有变量、类中所有成员以值传递
    //[this] 表示把类中所有成员以值传递进去
    //[&]表示把外部所有局部变量以引用传递进来
#if 1
    connect(&lamda_b,&QPushButton::pressed,&lamda_b,
            [=]()mutable{
                lamda_b.move(150,150);
                qDebug()<<"11111111";
                a=70;
                //[=]以值传递自动修饰外部变量为只读的,
                //error: assignment of read-only variable 'a'
                //但是可以在()后面用mutable修饰，以示可变的
                qDebug() << a;
            }
    );
#endif
#if 1
    connect(&lamda_b,&QPushButton::released,this,
            //我们发现即使这里是发给this的,但是信号发送是类似广播的形式发送的,
            //lamda_b依旧可以接收并处理
            [&](){
                lamda_b.move(100,100);
                qDebug()<<"22222222";
                a=35;qDebug() << a;
            }
    );
#endif
    //测试按键时按慢一点观察效果：如果按下时按键移动坐标则松开按键会失效
    //并且可以在按下键以后不松开在窗口界面上移动，观察现象，思考按键的机制
    //观察可知QQ登录时也有这种现象：按键不松开，移动到按键以外的屏幕再松开则登录键无效
    //想一想：是不是主窗口接收的是released信号而不是pressed信号(虽然QQ不是用Qt做的但是机制差不多应该)
#if 1
    //传递参数：
    //void QAbstractButton::clicked(bool checked = false)
    /* clicked与released很相似，但是不一样：released是松开按键时发送信号，
     * 但是clicked要的是按下到松开的整个过程，缺一个信号都不会发送，说与released是因为：
     * 一般released产生意味着pressed也已经产生，clicked自然与released相似(效果相似)
     *mouse Clicked:点击鼠标响应事件(按键通码)
     *mouse Pressed:鼠标按下时响应事件(按键通码加断码)
     *mouse released:松开鼠标时响应时间(按键断码)
     */

    connect(&lamda_b,&QPushButton::clicked,
            [=](bool value){
                qDebug() << value;    //按下一次传递一个false
            }
    );
#endif
}

MyWidget::~MyWidget()
{

}
