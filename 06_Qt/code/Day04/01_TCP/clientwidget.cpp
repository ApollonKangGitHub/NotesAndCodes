#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QByteArray>

ClientWidget::ClientWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    tcpSocket = NULL;

    //分配空间指定父对象
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, QTcpSocket::connected,
            [=](){ui->textRead->setText("和服务器建立连接成功");});
    connect(tcpSocket, QTcpSocket::readyRead,
            [=](){
                //获取对方发送的内容
                QByteArray array = tcpSocket->readAll();
                //追加到编辑区中
                ui->textRead->append(array);
            }
            );
    connect(tcpSocket, &QTcpSocket::disconnected,
            [=](){ui->textRead->setText("连接断开");});
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    QString ipSer = ui->lineEditIP->text();
    qint16 portSer = ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ipSer),portSer);
}

void ClientWidget::on_buttonSend_clicked()
{
    //获取编辑框内容
    QString str = ui->textWrite->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_buttonClose_clicked()
{
    //主动和对方断开连接
    ui->textRead->setText("连接断开");
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
