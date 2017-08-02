/*
 * Time:2017年6月27日16:51:12
 * Author:KangRuojin
 * Mail:mailbox_krj@163.com
 * Version:v1.1.1
 *
*/
#include "widget.h"
#include "ui_widget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

#include <QMediaPlayer>
#include <string.h>

#define cout qDebug()

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    startPoint = QPoint(81,61); //起点坐标
    endPoint = QPoint(710,530); //终点坐标

    gridWidth = (endPoint.x() - startPoint.x())/8;
    gridHigh = (endPoint.y() - startPoint.y())/8;

    initChess();

    connect(&timer, &QTimer::timeout, this, &Widget::machinePlay);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    //绘图事件，画棋盘，画棋子
    QPainter p(this);   //创建画家，指定窗口为画布

    //背景图（棋盘）
    p.drawPixmap(this->rect(),QPixmap(":/image/BackGround.PNG"));

    int startX = 0;
    int startY = 0;
    //根据棋盘二维数组的状态画棋子
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            startX = startPoint.x() + i*(gridWidth+1);
            startY = startPoint.y() + j*(gridHigh+1);
            if(chessStatus[i][j] == Black){
                //画黑子
                p.drawPixmap(startX, startY,
                             gridWidth-2, gridHigh-2, QPixmap(":/image/Black.png"));
            }
            else if(chessStatus[i][j] == White){
                //画白子
                p.drawPixmap(startX, startY,
                             gridWidth-2, gridHigh-2, QPixmap(":/image/White.png"));
            }
        }
    }
}
//鼠标点击事件
void Widget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        p = ev->globalPos() - this->frameGeometry().topLeft();
    }

    int i = 0, j = 0;
    i = ev->x() - startPoint.x();
    j = ev->y() - startPoint.y();

    if(i >= 0 && i <= 8*gridWidth && j >= 0 && j <= 8*gridHigh){
        //点击点在正确的棋盘内
        i = i/gridWidth;
        j = j/gridHigh;

        if( judgeRole(i,j,role) > 0 ){//点击落子成功
            whiteFlag = true;//落子成功则将白子标志位置为true
            changeRole();//改变角色
            update();//更新绘图
        }
    }
}
//鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent *ev)
{
    //如果鼠标事件中包含“按住的是左键”，需要移动窗口（在移动事件处理函数中必然有移动事件）
    if( ev->buttons() & Qt::LeftButton){
        move(ev->globalPos() - p);
    }
}

void Widget::on_toolButtonQuit_clicked()
{
    this->close();
}

void Widget::initChess()
{
    whiteFlag = blackFlag = true;//一开始双方都能落子
    overFlag = false;   //一开始游戏不结束

    bNumber = wNumber = 0;

    memset(chessStatus,0,sizeof(chessStatus));
    //中间四子：两白两黑
    chessStatus[3][3] = Black;
    chessStatus[4][3] = White;
    chessStatus[3][4] = White;
    chessStatus[4][4] = Black;

    role = White;   //默认白子先下

    ui->labelWhite->show();
    ui->labelBlack->hide();

    ui->lcdNumberWhite->display(2);
    ui->lcdNumberBlack->display(2);

    startVedio();
}

void Widget::changeRole()
{
    if(role == Black){
        role = White;
        ui->labelWhite->show();
        ui->labelBlack->hide();
    }
    else{
        role = Black;
        ui->labelWhite->hide();
        ui->labelBlack->show();
    }

    if(role == Black){//为黑子时，则由机器下子
        timer.start(1000);//machinePlay();
    }
    //统计个数
    countScore();
}

void Widget::countScore()
{
    bNumber = 0;
    wNumber = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            (!(chessStatus[i][j] - Black))
                    ? bNumber++ : ((!(chessStatus[i][j] - White)) ? wNumber++ : true);
        }
    }
    //记分规则：根据落子数与落子占比数来计算得分
    ui->lcdNumberWhite->display((wNumber)*(MAX_GRID_NUMBER-bNumber));
    ui->lcdNumberBlack->display((bNumber)*(MAX_GRID_NUMBER-wNumber));

    //判断能落子的最大值
    int num = 0,max = 0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){//判断能吃的位置
            if( num = judgeRole(i, j, role, false) > max){//寻找最多吃子的位置
                max = num;
            }
        }
    }

    //最大吃0个子，即不能落子，则直接判断胜负
    if(max == 0){
        if(blackFlag | whiteFlag){
            WHITE_FLAG();
            BLACK_FLAG();
            changeRole();
            update();
        }
        else{
            if(overFlag == false){
                overFlag = true;
                //修改标志位并弹出结果提示信息，在函数返回时另一个gameOver()就不会执行了
                gameOver();
            }
        }
    }
}

void Widget::gameOver()
{
    if(wNumber > bNumber){
        QMessageBox::about(this,"白棋嬴","萌新大军获得胜利");
    }
    else if(wNumber < bNumber){
        QMessageBox::about(this,"黑棋嬴","滑稽大军获得胜利");
    }
    else if(wNumber == bNumber){
        QMessageBox::about(this,"平局","端庄大军与滑稽大军平分秋色，难辨雌雄");
    }
}
int Widget::judgeRole(int x, int y, ChessFlag currentRole, bool eatChess)
{
    //落子的八个方向
    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    int tmpX = x,tmpY = y;              //临时保存棋盘坐标位置
    int i = 0, eatNum = 0;      //初始化数据

    if(chessStatus[tmpX][tmpY] != Empty){//如果此方格中已经有棋子无效操作，直接返回
        return 0;
    }

    //棋盘的8个方向
    for(i=0; i<8; i++){
        //从鼠标点击点开始
        tmpX = x;
        tmpY = y;
        //确定一个方向：dir[i][0]
        tmpX += dir[i][0];
        tmpY += dir[i][1];

        if(tmpX < GRID_NUMBER && tmpX >= 0 && tmpY < GRID_NUMBER && tmpY >= 0
            && (chessStatus[tmpX][tmpY] != currentRole) && (chessStatus[tmpX][tmpY] != Empty)){

            //如果没有出界并且相邻棋子是对方棋子才有可能吃子
            tmpX += dir[i][0];
            tmpY += dir[i][1];//向前走一步，开始判断该方向还有无自己棋子

            while(tmpX < GRID_NUMBER && tmpX >= 0 && tmpY < GRID_NUMBER && tmpY >= 0){
                if(chessStatus[tmpX][tmpY] == Empty){
                    break;//遇到空位跳出循环，外部if最后一个条件也会不满足，则直接判断下一个方向
                }
                if(chessStatus[tmpX][tmpY] == currentRole){//找到自己的棋子代表可以吃子
                    //能吃子则点击点标记为自己的棋子，update后是自己的棋子，否则点击处不能落子
                    (true == eatChess) ? (chessStatus[x][y] = currentRole) : true;
                    tmpX -= dir[i][0];
                    tmpY -= dir[i][1];//回退一步开始吃子
                    //没有回到开始的位置就继续执行
                    while((tmpX != x) || (tmpY != y)){//没有回退到点击处则继续修改原有棋子状态
                        //若为true则为落子，修改为自己的棋子,如果为false则为测试，不用修改
                        (true == eatChess) ? (chessStatus[tmpX][tmpY] = currentRole) : true;
                        tmpX -= dir[i][0];
                        tmpY -= dir[i][1];//回退一格，继续
                        eatNum++;   //吃子累计
                    }
                    break;//跳出循环，结束该方向的判断
                }
                //没找到自己的棋子就向前（指定方向）走一步，走到0或GRID_NUMBER边界条件时就结束该层if语句
                tmpX += dir[i][0];
                tmpY += dir[i][1];
            }
        }
    }
    return eatNum;
}

void Widget::machinePlay()
{
    timer.stop();//定时器停止

    int max = 0, num = 0;
    int px = 0, py = 0;

    //判断能落子的最大值
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            //判断能吃的位置,机器为黑子
            if( num = judgeRole(i, j, role, false) > max){//寻找最多吃子的位置
                max = num;
                px = i;
                py = j;
            }
        }
    }
    if(max == 0){//没有可走的了
        if((blackFlag | whiteFlag)){
            WHITE_FLAG();
            BLACK_FLAG();
            changeRole();
            return;
        }
        else{
            if(overFlag == false){
                overFlag = true;
                //修改标志位并弹出结果提示信息，在函数返回时另一个gameOver()就不会执行了
                gameOver();
            }
        }
    }

    //吃子
    if(judgeRole(px, py, Black) > 0){
        blackFlag = true;   //机器落子则将黑子标志位置为true
        changeRole();
        update();
    }
}

void Widget::on_toolButtonstart_clicked()
{
    //开始时重新开始打开音频文件
    audio->stop();      //音频停止
    inputFile.close();  //音频文件关闭
    //重新初始化棋盘
    initChess();
    update();
}

void Widget::startVedio()
{
    inputFile.setFileName(":/runningnew.pcm");
    inputFile.open(QIODevice::ReadOnly);

    //设置采样率
    audioFormat.setSampleRate(44100);
    //设置通道数
    audioFormat.setChannelCount(2);
    //设置采样大小，一般为8位或16位
    audioFormat.setSampleSize(16);
    //设置编码方式
    audioFormat.setCodec("audio/pcm");
    //设置字节序
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    //设置样本数据类型
    audioFormat.setSampleType(QAudioFormat::UnSignedInt);

    audio = new QAudioOutput( audioFormat, 0);
    audio->start(&inputFile);
}
