#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.setWindowTitle("服务器");

    Widget w2;
    w2.show();
    w2.setWindowTitle("客户端");

    return a.exec();
}
