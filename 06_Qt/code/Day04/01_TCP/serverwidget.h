#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>   //监听套接字
#include <QTcpSocket>   //通信套接字

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_buttonClose_clicked();
    void on_buttonSend_clicked();
private:
    Ui::ServerWidget *ui;
    QTcpServer * tcpServer; //监听套接字对象
    QTcpSocket * tcpSocket; //通信套接字对象
};

#endif // SERVERWIDGET_H
