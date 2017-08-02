#include "widget.h"
#include "ui_widget.h"
#include <QPainter>     //画家
#include <QPen>         //画笔
#include <QBrush>       //画刷

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x = 0;
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    //QPainter p(this);     //直接创建并指定设备，这样写就不需要指定begin()与ebd()

    QPainter p;     //创建画家对象
    p.begin(this);  //指定当前窗口为绘图设备
    //绘图操作
    //p.draw****();

    //定义画笔对象
    QPen pen;
    pen.setWidth(5);                    //设置线宽
    //pen.setColor(Qt::red);            //设置颜色
    pen.setColor(QColor(255,0,128));     //通过RGB设置颜色
    pen.setStyle(Qt::DashDotLine);      //设置线型
    //把画笔设置给画家
    p.setPen(pen);

    //定义画刷对象用以填充闭合图形
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::Dense1Pattern);
    p.setBrush(brush);

    //画背景图
    //起始位置为左上角(0,0)，宽度与高度(在窗口更新的时候自动获取)，图片路径
    //p.drawPixmap(0, 0, width(), height(), QPixmap(":/new/prefix1/image/picture.jpg"));
    //rect()可以自动获取矩形窗口大小范围
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/image/picture.jpg"));

    //画线:起点坐标与终点坐标
    p.drawLine(50,50,500,50);
    p.drawLine(50,50,50,500);

    //画矩形
    p.drawRect(200,100,100,50);

    //设置不同的画刷格式用以填充
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::CrossPattern);
    p.setBrush(brush);
    //画圆（椭圆）
    p.drawEllipse(QPoint(100,100),50,50); //圆心,半长轴长x,半短轴长y

    p.drawPixmap(x,300,75,75,QPixmap(":/new/prefix1/image/timg.jpg"));
    p.end();        //结束,与begin()对应
}

void Widget::on_pushButton_clicked()
{
    x += 75;
    if(x>width()){
        x = 0;
    }
    //手动刷新窗口(非内部自动调用)，让窗口重新绘制
    update(0,300,width(),75);       //刷新(指定范围)，不指定则全部重绘
    //间接调用paintEvent
}
