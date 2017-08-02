#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QDialog>
#include <QTcpSocket>   //通信套接字

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_buttonConnect_clicked();
    void on_buttonSend_clicked();
    void on_buttonClose_clicked();
private:
    Ui::ClientWidget *ui;
    QTcpSocket * tcpSocket; //通信套接字
};

#endif // CLIENTWIDGET_H
