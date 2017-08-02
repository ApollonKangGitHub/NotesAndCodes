#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QKeyEvent>
#include <QEvent>

#define BUFFER_SIZE 1024

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString str = QString("<h2>请先绑定端口!</h2>");
    ui->textEditRead->setText(str);
    //socket初始化
    udpSocket = NULL;
}

Widget::~Widget()
{
    delete ui;
}
void Widget::dealMessage()
{
    char buf[BUFFER_SIZE]={0};
    QHostAddress cliAddr;
    quint16 cliPort;
    qint64 ret =  udpSocket->readDatagram(buf, BUFFER_SIZE, &cliAddr, &cliPort);
    if(ret > 0){
        QString str = QString("[%1:%2]:%3")
                .arg(cliAddr.toString())
                .arg(cliPort)
                .arg(buf);
        ui->textEditRead->append(str);
    }
}

void Widget::on_buttonSend_clicked()
{
    if(udpSocket == NULL){
        return;
    }//没绑定端口之前不能发送数据
    QString peer_ip = ui->lineEditIP->text();
    qint64 peer_port = ui->lineEditPeerPort->text().toInt();

    QString str = ui->textEditWrite->toPlainText();
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(peer_ip),peer_port);
    ui->textEditWrite->clear();
}

void Widget::on_buttonBindOwnPort_clicked()
{
    //分配空间，指定父对象
    quint64 port = ui->lineEditOwnPort->text().toInt();
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port);
    QString str = QString("<h3>端口绑定成功!</h3>");
    ui->textEditRead->setText(str);
    setWindowTitle(QString("Port:%1").arg(port));

    connect(udpSocket, &QUdpSocket::readyRead, this, &dealMessage);
}

void Widget::on_buttonClose_clicked()
{
    close();
}
