#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void GetScreenSize();   //获取屏幕分辨率
    void SetMenuAndTool();
    void SetDockAndTest();
    void SetStatus();
    ~MainWindow();
private:
    int screenWidth;        //屏幕宽度
    int screenHeight;       //屏幕高度
};

#endif // MAINWINDOW_H
