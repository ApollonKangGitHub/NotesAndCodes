#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

//public slots:   //这是Qt4中的写法，需要声明
    void mySlot();
    void ChangeWindow();
    void dealSub();
    void dealSub(int,QString);
private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;
    SubWidget w;
};

#endif // MAINWIDGET_H
