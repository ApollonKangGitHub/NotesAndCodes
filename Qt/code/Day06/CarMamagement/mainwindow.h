#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB();   //连接数据库
    void initData();    //初始化数据
private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFactory_currentIndexChanged(const QString &factory);

    void on_comboBoxBrand_currentIndexChanged(const QString &name);

    void on_spinBoxNumber_valueChanged(int number);

    void on_pushButtonCancel_clicked();

    void on_pushButtonSure_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel * model;
};

#endif // MAINWINDOW_H
