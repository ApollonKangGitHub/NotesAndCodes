#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Litttle Boss");
    this->resize(500,300); //设置窗口大小

    b.move(220,120);
    b.setParent(this);
    b.setText("切换到主窗口");

    connect(&b, &QPushButton::clicked, this, &SubWidget::sendSlot);
}
void SubWidget::sendSlot()
{
    emit mySignal();    //发送信号
    //emit mySignal(32767,"MaxValue of 32 bit signel int is");
    emit mySignal(32767,"最大的有符号整数(32bit_int)是");
}
