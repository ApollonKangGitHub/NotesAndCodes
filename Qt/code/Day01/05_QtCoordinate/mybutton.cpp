#include "mybutton.h"
#include <QDebug>
//指定父对象之后，并且必须是直接或间接继承与QObject类
//子对象如果是动态分配内存的，则不需要手动delete释放
//系统会自动释放
myButton::myButton(QWidget *parent) : QPushButton(parent)//构造函数给基类传递参数
{

}

myButton::~myButton()
{
    qDebug()<<"myButton对象已经析构";  //析构函数会被调用并会自动析构该类的对象
}
