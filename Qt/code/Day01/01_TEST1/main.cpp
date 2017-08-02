#include "mywidget.h"
#include <QApplication>
//QApplication应用程序类
//Qt头文件不带.h
//头文件名与类名相同

int main(int argc, char *argv[])
{
    //有且只有一个应用程序类的对象
    QApplication a(argc, argv);

    //MyWidget继承于QWidget，QWidget是一个窗口基类
    //所以MyWidget也是窗口类
    //w是该类实例化后的对象，是一个窗口
    MyWidget w;
    //窗口默认是隐藏的，需要人为调用show()显示
    w.show();

    //a.exec()的作用是：
    //让程序一直执行(而不是窗口一闪而过)，等待用户操作(等待事件发生：如鼠标、键盘)
    return a.exec();
    //等价于：
    //a.exec()
    //return 0;
}
