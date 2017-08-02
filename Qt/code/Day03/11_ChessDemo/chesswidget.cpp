#include "chesswidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QDebug>

ChessWidget::ChessWidget(QWidget *parent)
    : QWidget(parent)
{
    chessX = -1;
    chessY = -1;
    chessColor = CHESS_BLACK;   //黑棋先行
}

ChessWidget::~ChessWidget()
{

}
void ChessWidget::paintEvent(QPaintEvent *)
{
    //分成“lineNum * lineNum”的棋盘
    gridW = width()/lineNum;
    gridH = height()/lineNum;

    //棋盘起点坐标：
    startX = gridW;
    startY = gridH;

    QPainter p(this);   //创建画家，指定窗口为绘图设备

    //背景图
    //p.drawPixmap(rect(), QPixmap(":/new/prefix1/back.png"));

    //设置画笔
    QPen pen;
    pen.setWidth(2);    //线宽
    //pen.setColor(Qt::red);
    p.setPen(pen);      //将画笔与画家建立联系

    //取中间“(lineNum-2)*(lineNum-2)”份画棋盘
    for(int i = 0; i <= lineNum-2 ;i++){
        //横线：
        p.drawLine(startX,startY+i*gridH, startX+(lineNum-2)*gridW, startY+i*gridH);
        //竖线：
        p.drawLine(startX+i*gridW,startY, startX+i*gridW, startY+(lineNum-2)*gridH);
    }

    //画棋子
    QPixmap pixBlack(":/new/prefix1/Chess_Black.jpg");
    QPixmap pixWhite(":/new/prefix1/Chess_White.jpg");

    if(chessX != -1 && chessY != -1){
        if(CHESS_WHITE == chessColor){//画白棋
            p.drawPixmap(startX+chessX*gridW, startY+chessY*gridH,gridW,gridH,
                         QPixmap(":/new/prefix1/Chess_White.jpg"));  //图片来源白棋子
            chessColor = CHESS_BLACK;                                //画完白棋画黑棋
        }else if(CHESS_BLACK == chessColor){//画黑棋
            p.drawPixmap(startX+chessX*gridW, startY+chessY*gridH,gridW,gridH,
                     QPixmap(":/new/prefix1/Chess_Black.jpg"));      //图片来源黑棋子
            chessColor = CHESS_WHITE;                                //画完黑棋画白棋
        }
    }

}
void ChessWidget::mousePressEvent(QMouseEvent *ev)
{
    //获取点击点坐标
    int x = ev->x();
    int y = ev->y();

    //保证点击点在棋盘范围内
    if(x >= startX && x<= startX+(lineNum-2)*gridW
            && y >= startY && y<= startY+(lineNum-2)*gridH){
        //棋盘的位置转换为下标值
        //更新窗口，间接调用paintEvent()
        chessX = (x-startX-1)/gridW;    //再减1是为了防止点击点在最外边的线的外半部分，导致画图出界
        chessY = (y-startY-1)/gridH;
        qDebug() << "(" << chessX << "," << chessY << ")";
        //更新窗口，间接调用paintEvent()
        update();
    }
}
