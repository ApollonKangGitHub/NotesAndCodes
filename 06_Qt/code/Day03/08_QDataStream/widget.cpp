#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>  //二进制数据流的方式操作
#include <QFile>
#include <QDebug>

//__FILE__、__LINE__：全局宏
#define cout (qDebug()<<"["<<__FILE__<<":"<<__LINE__ <<"]")
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();
    readData();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{
    //创建一个文件对象
    QFile file("../08_QDataStream/file.txt");
    //以只写方式打开文件
    if(file.open(QIODevice::WriteOnly)){
        //创建数据流，和file文件相关
        //向数据流中输入数据，相当于往文件中写数据
        QDataStream stream(&file);
        stream << QString("碗大的西瓜一扎厚的皮，你瓜实了！")<<250;
        file.close();
    }
}
void Widget::readData()
{
    QFile file("../08_QDataStream/file.txt");
    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        QString str;
        int a;
        stream >> str >> a;
        //qDebug()
        cout << str.toUtf8().data() <<a;
        file.close();
    }
}
