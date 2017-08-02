#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
#include <QPixmap>
#include <QLineEdit>
#include <qDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QQ");
    this->resize(240,326);
#if 0
    ui->label->setPixmap(QPixmap(":/image/haizei.jpg"));
#endif

#if 1
    //创建动画
    QMovie * myMovie = new QMovie(":/image/touxiang.gif");
    //设置动画
    ui->label->setMovie(myMovie);
    //启动动画
    myMovie->start();
#endif
    //显示模式为密码模式
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);

    //connect(ui->pushButton_LogOn, &QPushButton::released,[](){qDebug() << "密码错误";});
    connect(ui->pushButton_LogOn, &QPushButton::clicked,
            [=](){ui->pushButton_LogOn->setText("密码错误");}
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}
