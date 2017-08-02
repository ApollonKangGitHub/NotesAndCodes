//2017年5月20日19:34:13
#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
