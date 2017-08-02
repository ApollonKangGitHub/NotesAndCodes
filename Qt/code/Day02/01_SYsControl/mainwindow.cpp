#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>
#include <QStringList>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <unistd.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //修改ui的button_close名字
    //ui->button_close->setText("YVER");
    /*Input Widgets*/
    ui->lineEdit->setText("input");
    //设置内容显示间隙(左、上、右、下)
    ui->lineEdit->setTextMargins(5,0,0,0);
    //设置内容和显示方式
    //ui->lineEdit->setEchoMode(QLineEdit::Password);

    //提示列表信息
    QStringList list;
    list << "HeiHei" <<"Hello World" << "Who are you";
    QCompleter * com = new QCompleter(list, this);
    //设置不区分大小写
    com->setCaseSensitivity(Qt::CaseInsensitive);
    //将com设定给lineEdit
    ui->lineEdit->setCompleter(com);


    //Label设置
    ui->labelImage->setPixmap(QPixmap("://image/3.jpg"));
    //让图片自适应Label大小
    ui->labelImage->setScaledContents(true);

    //创建动画
    QMovie * myMovie = new QMovie("://image/B8D3C705E7DB34331C86294EF107D878.gif");
    //设置动画
    ui->labelGif->setMovie(myMovie);
    //启动动画
    myMovie->start();

    //设置HTML内容
    ui->labelUrl->setText("百度一下");
    ui->labelUrl->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    //打开外部连接
    ui->labelUrl->setOpenExternalLinks(true);
    //数码管
    ui->lcdNumber->display(75);

    //进度条
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(75);

    //显示URL指定的网址的网页webView
    ui->webView->load(QUrl("http://www.baidu.com"));

    //设置按钮到标签页之上
    ui->lineEdit->setParent(ui->labelImage);
    ui->button_close->setParent(ui->labelImage);
    ui->button_ok->setParent(ui->labelImage);
    ui->dateTimeEdit->setParent(ui->labelImage);
    ui->fontComboBox->setParent(ui->labelImage);
    ui->comboBox->setParent(ui->labelImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
