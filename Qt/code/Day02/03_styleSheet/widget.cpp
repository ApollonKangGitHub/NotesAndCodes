#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
#if 0
    //统一背景图片设置
    this->setStyleSheet("QWidget{"
                        "background-image:url(://image/haizei.jpg);"
                        "}");
#endif
#if 1
    //统一颜色设置
    this->setStyleSheet("QLabel{color:red;background-color:green;}");
#endif
    //单独覆盖原有设置
    ui->label->setStyleSheet("QLabel{"
                             "color:rgb(255,255,255);"
                             "background-color:rgb(0,0,255);"
                             "}");

    //background-image:平铺方式
    //border-image:自适应大小
    ui->labelImage->setStyleSheet("QLabel{"
                                   "background-image:url(://image/haizei.jpg);"
                                   "}");
     //10像素点边框向外延伸
    ui->pushButton->setStyleSheet("QPushButton{"
                                  "border:10px outset red;"
                                  "}");
    //初始就有一张图片，当鼠标移动到按钮上时更换图片
    ui->pushButtonImage->setStyleSheet("QPushButton{"
                                       "border-image:url(://image/haizei.jpg);"
                                       "}"
                                       "QPushButton:hover{"
                                       "border-image:url(://image/49_121118100108_1.jpg);"
                                       "}"
                                       "QPushButton:pressed{"
                                       "border-image:url(://image/49_121120204924_1.jpg);"
                                       "}"
                                       );
}

Widget::~Widget()
{
    delete ui;
}
