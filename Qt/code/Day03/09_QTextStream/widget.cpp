#include "widget.h"
#include "ui_widget.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QFileDialog>

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
    QFile file;
    file.setFileName("../09_QTextStream/file.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream.setCodec("UTF-8");    //指定编码格式，不指定则按默认格式
        stream << QString("碗大的西瓜一扎厚的皮，你瓜实了！") << 250;
        file.close();
    }
}
void Widget::readData()
{
    QFile file;
    file.setFileName("../09_QTextStream/file.txt");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QString str;
        int a;
        //这种读取方式不对，因为写进去的时候两个数据(QString与int)变成了一个(QString)
        stream >> str >> a;
        cout << str.toUtf8().data() <<a;
        file.close();
    }
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../09_QTextStream/");
    if( !path.isEmpty() ){
        QFile file(path);
        if( file.open(QIODevice::ReadOnly) ){
            QTextStream stream(&file);
            stream.setCodec("UTF-8");       //必须与写文件的格式(保存后的格式)相同
            QByteArray array;
            while( !file.atEnd() ){
                //一次最多读取一行，可以指定参数：少于一行的字符数
                array += file.readLine();
            }
            ui->textEdit->setText(array);
            file.close();
        }
    }
}
