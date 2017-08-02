#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    connect(myTimer, &QTimer::timeout,
            [=](){
                static int i = 0;
                i++;
                ui->lcdNumber->display(i);
            }
            );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonStart_clicked()
{
    //启动定时器，每隔1000ms，myTimer自动触发一次timeout()
    if(myTimer->isActive() == false){   //如果没有启动就启动
        myTimer->start(1000);
    }
}

void Widget::on_buttonStop_clicked()
{
    if(myTimer->isActive() == true){    //如果启动过了就停止
        myTimer->stop();
    }
}
