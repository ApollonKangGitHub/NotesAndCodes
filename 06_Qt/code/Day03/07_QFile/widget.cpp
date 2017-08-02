#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ButtonRead_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../",
                                "TXT(*.txt *.doc *.docx *.rtf);;"
                                "SOURCE(*.h *.c *.cpp *.java *.asm);;"
                                "ALL(*)");
    if( !path.isEmpty() ){
        //文件对象
        QFile file(path);
        //打开文件,读取文件：默认只识别UTF8编码
        if( file.open(QIODevice::ReadOnly) ){
            #if 0
            //readAll()一次性读取
            QByteArray array = file.readAll();
            //ui->textEdit->setText(QString(array));
            ui->textEdit->setText(array);
            #endif
            #if 1
            QByteArray array;
            while( !file.atEnd() ){
                //一次最多读取一行，可以指定参数：少于一行的字符数
                array += file.readLine();
            }
            ui->textEdit->setText(array);
            #endif
            file.close();
        }

        //获取文件信息，类似于stat结构体，包含文件的一些具体信息
        QFileInfo info(path);
        qDebug() <<"文件名字："<<info.fileName().toUtf8().data();
        qDebug() <<"文件路径："<<info.path().toUtf8().data();
        qDebug() <<"文件大小(B)："<<info.size();
        qDebug() <<"文件后缀："<<info.suffix();
        qDebug() <<"文件创建时间"<<info.created().toString("yyyy/MM/dd hh:mm:ss");

    }
}

void Widget::on_ButtonWrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"save","../",
                                "TXT(*.txt *.doc *.docx *.rtf);;"
                                "SOURCE(*.h *.c *.cpp *.java *.asm)");
    if(!path.isEmpty()){
        QFile file;
        file.setFileName(path);
        if(file.open(QIODevice::WriteOnly)){
            QString str = ui->textEdit->toPlainText();//获取编辑区内容
            //写文件QString --> QByteArray
            //file.write(str.toUtf8());   //按UTF-8方式写入

            //QString --> C++ string -->char*
            //转换成QString通过QByteArry转换成char *
            //file.write(str.toStdString().data()); //也是UTF-8

            //转换成本地编码(WIndows为ANSI)
            file.write(str.toLocal8Bit());
        }
    }
}
