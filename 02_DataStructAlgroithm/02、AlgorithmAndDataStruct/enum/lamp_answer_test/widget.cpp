/*
 * Time:2017年7月31日11:09:14
 * Author:KangRuoJin
 * Mail:mailbox_krj@163.com
 * Version:v2.1
*/
#include "widget.h"
#include "ui_widget.h"

#include <cstring>
#include <time.h>
#include <stdlib.h>

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    startPoint = QPoint(0,0); //起点坐标
    endPoint = QPoint(400,300); //终点坐标

    //宽度与高度
    gridWidth = (endPoint.x() - startPoint.x())/6;
    gridHigh = (endPoint.y() - startPoint.y())/5;

    pressFlag = false;
    memset(lamp.init, 0, 5);
    memset(lamp.lights, 0, 5);
    memset(lamp.result, 0, 5);
    initLamp();
}

void Widget::initLamp()
{
    srand(time(NULL));
    //只用到后六位，则对64取余即可
    lamp.init[0] = rand()%64;
    lamp.init[1] = rand()%64;
    lamp.init[2] = rand()%64;
    lamp.init[3] = rand()%64;
    lamp.init[4] = rand()%64;
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
   // p.drawPixmap(this->rect(),QPixmap("://back.PNG"));

    int startX, startY;
    for(int i = 0; i<6; i++){
        for(int j = 0; j<5; j++){
            startX = gridWidth * i +2;
            startY = gridHigh * j +2;
            if(lamp.GetBit(lamp.init[j],i)){//为1画亮（黄）
                if(lamp.GetBit(lamp.result[j],i)  && pressFlag)//需要提示
                    p.drawPixmap(startX, startY, gridWidth-2, gridHigh-2, QPixmap(":/image/press_light.png"));
                else//不需要提示
                    p.drawPixmap(startX, startY, gridWidth-2, gridHigh-2, QPixmap(":/image/light.PNG"));
            }
            else{//为0画灭（黑）
                if(lamp.GetBit(lamp.result[j],i) && pressFlag)
                    p.drawPixmap(startX, startY, gridWidth-2, gridHigh-2, QPixmap(":/image/press_black.png"));
                else
                    p.drawPixmap(startX, startY, gridWidth-2, gridHigh-2, QPixmap(":/image/black.PNG"));
            }
        }
    }
}
void Widget::mousePressEvent(QMouseEvent *ev)
{
    //根据点击点击点位置更新数组
    int i = ev->x()/gridWidth;
    int j = ev->y()/gridHigh;

    lamp.BackBit(lamp.init[j],i);//点击坐标反转
    if(j > 0)
        lamp.BackBit(lamp.init[j-1],i);//点击坐标上一行对应横坐标位置反转
    if(j < 4)
        lamp.BackBit(lamp.init[j+1],i);//点击坐标下一行对应横坐标位置反转
    if(i > 0)
        lamp.BackBit(lamp.init[j],i-1);//点击坐标前一个位置反转
    if(i < 5)
        lamp.BackBit(lamp.init[j],i+1);//点击坐标后一个位置反转

    lamp.SetBit(lamp.result[j], i, 0);//点击一次就将该点击点的result置为0

    update();//更新绘图
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonRestart_clicked()
{
    pressFlag = false;
    memset(lamp.init, 0, 5);
    memset(lamp.lights, 0, 5);
    memset(lamp.result, 0, 5);

    initLamp();
    update();
}

void Widget::on_buttonPrompt_clicked()
{
    pressFlag = true;
    lamp.ProcessAlgroithm();
    update();
}
