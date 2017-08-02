#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::ClientWidget *ui;
    QTcpSocket * tcpSocket; //通信
    QFile file;             //文件对象
    QString fileName;       //文件名字
    qint64 fileSize;        //文件大小
    qint64 recvSize;        //已接收发送大小

    bool isStart;           //数据包类型标志
};

#endif // CLIENTWIDGET_H
