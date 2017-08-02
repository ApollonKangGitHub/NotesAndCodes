#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>
MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}
//注意:
//如果两个Label都提升成为MyLabel，则在任意一个标签页的鼠标事件都是MyLabel处理，在MyLabel中没有忽略
//就传递不到MyWidget中去;如果有任一个标签Label没有提升为MyLabel，则在其标签页按下鼠标,产生一个事件
//事件就不是传递给MyLabel的事件处理函数，而是传递给MyWidget，这与MyButton忽略后传递给MyWidget
//结果显示是一样的，但是本质是不一样的：
//(一个是QLabel未处理传递给MyWidget，一个是MyButton处理后并忽略传递给MyWidget)。

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    //按下的是左键
    if(ev->button() == Qt::LeftButton){
        qDebug() << "Press is Left of Mouse";   // 处理完成之后就不会传递
        //ev->accept();   //事件接收，事件不会 再往下传递
    }
    else{
        ev->ignore();   //事件忽略则继续往下传递，给谁传递？
                        //不是给了父基类，而是给了父组件MyWidget主窗口
    }
    //只要这里有QPushButton::mousePressEvent(ev);信号就一定会向下传递
    //myWidget中的connect也就能够接收到，但是一般在if...else中指定ignore或accept来决定：
    //是否忽略或继续向下传递，所以将逻辑写到if...else中而不是if...else之外
    //但是ignore()最多的使用还是在close()事件中
    //QPushButton::mousePressEvent(ev);
}
