#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H
#define CHESS_WHITE 1
#define CHESS_BLACK 2

#include <QWidget>

class ChessWidget : public QWidget
{
    Q_OBJECT
protected:
    //覆写绘图事件
    void paintEvent(QPaintEvent *);
    //覆写鼠标按下事件
    void mousePressEvent(QMouseEvent *ev);
public:
    ChessWidget(QWidget *parent = 0);
    ~ChessWidget();
private:
    //棋盘格子尺寸
    int gridW;
    int gridH;

    //棋盘起始点坐标
    int startX;
    int startY;

    //棋盘下标
    int chessX;
    int chessY;

    int chessColor;
    //格子行数（列数）
    const int lineNum = 10;
};

#endif // CHESSWIDGET_H
