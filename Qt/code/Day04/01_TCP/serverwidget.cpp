#include "serverwidget.h"
#include "ui_serverwidget.h"

#define PORT_SERVER 8888

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    tcpSocket = NULL;
    tcpServer = NULL;

    //监听套接字
    setWindowTitle("Server:8888");
    tcpServer = new QTcpServer(this);   //指定父对象，自动回收空间
    //指定绑定的IP(Any指当前网卡的所有IP)和port
    tcpServer->listen(QHostAddress::Any, PORT_SERVER);

    //获取连接
    connect(tcpServer, &QTcpServer::newConnection,
            [=](){
                //取出建立好连接的套接字，用于通信
                //取监听队列中下一个(第一个)连接
                tcpSocket = tcpServer->nextPendingConnection();

                //获取对方的IP:port
                QString ipCli = tcpSocket->peerAddress().toString();
                qint16 portCli = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]:连接成功").arg(ipCli).arg(portCli);
                ui->textRead->setText(temp);        //显示连接信息

                //进行通信套接字的读取
                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=](){
                            //从通信套接字中取出内容
                            QByteArray array = tcpSocket->readAll();
                            ui->textRead->append(array);
                        }
                        );
                connect(tcpSocket, &QTcpSocket::disconnected,
                        [=](){ui->textRead->setText("连接断开");});
            }
            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonClose_clicked()
{
    //主动和客户端断开连接
    if(tcpSocket != NULL){
        ui->textRead->setText("连接断开");
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        tcpSocket = NULL;
    }
}

void ServerWidget::on_buttonSend_clicked()
{
    //获取编辑器内容
    if(tcpSocket != NULL){
        QString str = ui->textWrite->toPlainText();
        //给对方发送数据
        tcpSocket->write(str.toUtf8().data());
    }
}
