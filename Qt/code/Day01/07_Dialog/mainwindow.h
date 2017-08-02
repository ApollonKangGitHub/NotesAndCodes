#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void GetScreenSize();
    ~MainWindow();
private:
    int screenWidth;
    int screenHeight;
    QDialog dlg;
};

#endif // MAINWINDOW_H
