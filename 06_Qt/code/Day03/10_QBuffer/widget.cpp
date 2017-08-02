#include "widget.h"
#include "ui_widget.h"
#include <QBuffer>      //内存文件
#include <QDebug>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QByteArray array;
    QBuffer memFile(&array);        //创建内存文件对象
    memFile.open(QIODevice::WriteOnly);
    qDebug() << "memory:" <<memFile.buffer();
    qDebug() << "array :" <<array;

    memFile.write("1111111111111111");
    qDebug() << "memory:" << memFile.buffer();
    qDebug() << "array :" <<array;

    memFile.write("2222222222222222");
    qDebug() << "memory:" << memFile.buffer();
    qDebug() << "array :" <<array;
    memFile.close();

    QBuffer memFileNew;
    memFileNew.open(QIODevice::WriteOnly);
    QDataStream stream(&memFileNew);
    stream << QString("测试") << 250;
    memFileNew.close();

    qDebug() << memFileNew.buffer();
    //qDebug() << QString(memFileNew.buffer()).toUtf8().data();
    //似乎不行

    memFileNew.open(QIODevice::ReadOnly);
    QString str;
    int num;
    stream >> str >> num;
    qDebug() << str.toUtf8().data() << num;
}

Widget::~Widget()
{
    delete ui;
}
