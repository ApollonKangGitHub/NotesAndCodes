#include "mywidget.h"
#include "ui_mywidget.h"
#include <QKeyEvent>
#include <QDebug>
#include <unistd.h>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    timerID_fast = this->startTimer(1000);//以毫秒为单位，每隔1秒触发一次定时器
    timerID_slow = this->startTimer(500);
    //this->killTimer(timerID);     //关闭定时器

    connect(ui->pushButton, &MyButton::pressed, [](){qDebug()<<"左键被按下";});
    connect(ui->pushButton, &MyButton::released, [](){qDebug()<<"左键被释放";});

    ui->label->installEventFilter(this);//安装过滤器
    //设定追踪鼠标，一开始运行就追踪而不是需要先按下键才会追踪
    ui->label->setMouseTracking(true);
}
#if 1
void MyWidget::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "事件传递给了父组件";
}
MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() >= Qt::Key_A && ev->key() <= Qt::Key_Z){
        qDebug() << (char)ev->key();
    }
}
#endif
void MyWidget::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == timerID_fast){
        static int sec = 0;
        ui->labelCoordinate->setText(
                    QString("<center><h1>Timer out:%1</h1></center>").arg(sec));
        //<center><h1>Timer out:%1</h1></center>为HTML的写法，中间(center)标题大小(h1)显示
        if(sec == 20){  //定时到20ms时停止计时
            killTimer(timerID_fast);
        }
        sec++;
    }else if(ev->timerId() == timerID_slow){
        static int sec = 0;
        ui->label->setText(
                    QString("<center><h1>Timer out:%1</h1></center>").arg(sec++));
    }
}
void MyWidget::closeEvent(QCloseEvent *ev)
{
    int ret = QMessageBox::question(this,"question","Close the Windows?");
    if(ret == QMessageBox::Yes){
        //关闭窗口
        //接收事件，事件不再向下传递
        ev->accept();
    }else{
        //不关闭窗口
        //忽略事件，事件继续给父组件传递,由于父组件没有做关于close的接收操作
        //所以不操作
        ev->ignore();
    }
}
//通过event()进行事件过滤
bool MyWidget::event(QEvent *ev)
{
//switch的写法
#if 1
    //对于定时器进行功能进行覆写，对键盘的Y键保留中断，其他键忽略。其它时间仍按默认处理
    //默认的是在event()的分发层(下一级)进行处理，而定时器的处理直接放在了event()函数中处理
    //到了下一层定时器的处理发现return的是true就不再处理，键盘按键也是同理
    switch(ev->type()){
        case QEvent::Timer: //如果是定时器事件，返回true停止时间传播，忽略定时器中断
            //timerEvent(static_cast<QTimerEvent*>(ev));       //不处理直接返回就是干掉了定时器
            //取消注释，则是将定时器事件提到event()函数中直接处理
            return true;
            break;
        case QEvent::KeyPress:
            if(static_cast<QKeyEvent *>(ev)->key() == Qt::Key_Y){
                return QWidget::event(ev);
            }
            return true;
            break;
        default:
            return QWidget::event(ev);
            break;
            //...
    }
#endif
    //if...else...的写法
#if 0
    if(ev->type() == QEvent::Timer){        //定时器特殊处理：忽略
        return true;
    }
    else if(ev->type() == QEvent::KeyPress){    //键盘处理：保留Y键，其它键忽略
        if(static_cast<QKeyEvent *>(ev)->key() == Qt::Key_Y){
            return QWidget::event(ev);
        }
        return true;

    }
    else{
        return QWidget::event(ev);  //其它事件按原有方式处理
        //注意这里一定要把不特殊处理的按原有方式处理
    }
#endif
}
bool MyWidget::eventFilter(QObject *obj, QEvent *ev)
{
    //对标签label进行事件过滤
    if(obj == ui->label){
        QMouseEvent * env = static_cast<QMouseEvent *>(ev);
        if(ev->type() == QEvent::MouseMove){
            ui->label->setText(QString("<center><h1>Mouse Move:(%1, %2)"
                                       "</h1></center>").arg(env->x()).arg(env->y()));
            return true;    //结束传播
        }
        else if(ev->type() == QEvent::MouseButtonPress){
            ui->label->setText(QString("<center><h1>Mouse pressed</h1></center>"));
            return true;    //结束传播
        }
        else if(ev->type() == QEvent::MouseButtonRelease){
            ui->label->setText(QString("<center><h1>Mouse released</h1></center>"));
            return true;    //结束传播
        }
    }
        return QWidget::eventFilter(obj,ev);

}
