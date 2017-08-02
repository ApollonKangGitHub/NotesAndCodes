#include "mainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    this->setFixedSize(500,300);
}
MainWindow::~MainWindow()
{ }
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"MouePressEnent "<<endl;
        qDebug()<<event->x()<<""<<event->y()<<endl;
        qDebug()<<event->globalX()<<""<<event->globalY()<<endl;
    }
}
