#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QString>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //显示第一个页面
    //ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentWidget(ui->pageSet);

    //初始化数据
    //失败动画
    overMovie.setFileName("://Image/lose.gif");
    ui->labelOver->setMovie(&overMovie);    //给标签设置动画
    ui->labelOver->setScaledContents(true); //动画自适应大小

    //胜利动画
    winMovie.setFileName("://Image/19-1F52410394O36.gif");
    ui->labelWin->setMovie(&winMovie);
    ui->labelWin->setScaledContents(true);

    QString str = QString("<center><h1>欢迎来到猜数字游戏</h1></center>");
    ui->labelSet->setText(str);
    str = QString("<center><h>选择难度(游戏时间)</h3></center>");
    ui->labelHard->setText(str);

    //猜数字游戏界面相应设置
    //数字按钮连接同一个槽
    connect(ui->pushButton0, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton1, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton2, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton3, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton4, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton5, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton6, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton7, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton8, &QPushButton::clicked, this, &MyWidget::dealNumber);
    connect(ui->pushButton9, &QPushButton::clicked, this, &MyWidget::dealNumber);
}

MyWidget::~MyWidget()
{
    delete ui;
}

//开始游戏
void MyWidget::on_pushButtonStart_clicked()
{
    //获取下拉框的时间.toInt()，字符串转化为int
    gameTime = ui->comboBox->currentText().toInt();
    //qDebug() << gameTime << "s";

    //切换到游戏界面
    //ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->setCurrentWidget(ui->pageGame);

    int num = 0;
    //从0时0分0秒到现在的秒数为种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //生成随机数
    while((num=qrand()%10000) <= 999){
        NULL;
    }
    randStr = QString::number(num);
    //qDebug()<< "randNum = " <<randStr;

    //设置进度条
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(gameTime);  //最大值
    ui->progressBar->setValue(gameTime);    //当前值

    gameTimerId = 0;
    //启动定时器
    gameTimerId = startTimer(1000); //1s作为时间间隔
    resultStr.clear();
    ui->textEdit->clear();
}

//退出游戏
void MyWidget::on_pushButtonEnd_clicked()
{
    this->close();
}
void MyWidget::timerEvent(QTimerEvent * ev)
{
    if(ev->timerId() == gameTimerId){
        gameTime--;
        //设置进度条
        ui->progressBar->setValue(gameTime);    //当前值
        //时间到
        if(0 == gameTime){
            //关闭定时器
            killTimer(gameTimerId);
            QMessageBox::information(this,"失败","时间到了，接收惩罚吧");
            overMovie.start();
            //切换失败动画页面
            ui->stackedWidget->setCurrentWidget(ui->pageOver);
            overTimerId = startTimer(SHOW_FAILURE_TIME); //显示SHOW_FAILURE_TIME时间
        }
    }
    else if(ev->timerId() == overTimerId){//失败动画时间
        //停止动画，停止定时器，回到游戏设置页面
        overMovie.stop();
        killTimer(overTimerId);

        //切换到游戏设置页面
        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }
    else if(ev->timerId() == winTimerId){
        winMovie.stop();    //停止动画
        killTimer(winTimerId);
        //切换到游戏设置页面
        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }
}
//数字键处理函数
void MyWidget::dealNumber()
{
    QString str;
    //获取信号接收者
    QObject * mySender = sender();
    //转换为按钮类型
    QPushButton * p = (QPushButton *)mySender;
    if(NULL != p){
        //获取按钮内容
        QString numStr = p->text();
        resultStr += numStr;

        //数字不能以0开始
        if(resultStr.size() == 1 && resultStr == "0"){
            resultStr.clear();
        }
        //保证显示结果为4位
        if(resultStr.size() <= 4){
            str = QString("<center><h1>%1</h1></center>").arg(resultStr);
            ui->textEdit->setText(str);

            if(resultStr.size() == 4){
                if(resultStr > randStr){
                    str = QString("<center><h1>数字大了点</h1></center>").arg(resultStr);
                    ui->textEdit->append(str);
                }else if(resultStr < randStr){
                    str = QString("<center><h1>数字小了点</h1></center>").arg(resultStr);
                    ui->textEdit->append(str);
                }else{
                    str = QString("<center><h1>恭喜你答对了</h1></center>").arg(resultStr);
                    ui->textEdit->append(str);
                    //停止计时器
                    //关闭计时器
                    killTimer(gameTimerId);
                    QMessageBox::information(this,"胜利","恭喜你猜对了,接收奖励吧");

                    //切换到成功动画
                    winMovie.start();
                    ui->stackedWidget->setCurrentWidget(ui->pageWin);
                    //启动定时器
                    winTimerId = startTimer(SHOW_SUCCESS_TIME);  //显示SHOW_SUCCESS_TIME时间
                }
                //初始化字符串结果，清空
                resultStr.clear();
            }
        }
    }
}
//退格按钮
void MyWidget::on_pushButtonDel_clicked()
{
    QString str = NULL;
    if(resultStr.size() == 1){
        resultStr.clear();
        ui->textEdit->clear();
    }
    else{
        resultStr.chop(1);  //截断最后一位字符
        resultStr[resultStr.size()-1] = '\0';
        str = QString("<center><h1>%1</h1></center>").arg(resultStr);
        ui->textEdit->setText(str);
    }
}
//提示按钮
void MyWidget::on_pushButtonEnter_clicked()
{
    resultStr.clear();
    QString str = "随机数为：" + randStr + 10;
    QString str_new = QString("<center><h1>%1</h1></center>").arg(str);
    ui->textEdit->setText(str_new);
}
