#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QByteArray>
#include <QMessageBox>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=](){
                QByteArray buf = tcpSocket->readAll();
                if(true == isStart){
                    isStart = false;
                    //接收包头
                    fileName = QString(buf).section("##",0,0);
                    fileSize = QString(buf).section("##",1,1).toInt();
                    recvSize = 0;

                    QString str = QString("接收的文件:[%1:%2kB]").arg(fileName).arg(fileSize/1024);
                    //QMessageBox::information(this,"文件信息",str);//会对服务器的连接断开可能会有影响
                    setWindowTitle(str);

                    ui->progressBar->setMaximum(fileSize);
                    ui->progressBar->setMinimum(0);
                    ui->progressBar->setValue(0);

                    file.setFileName(fileName);
                    if(false == file.open(QIODevice::WriteOnly)){
                        QMessageBox::information(this,"Error","文件创建并打开失败!");
                    }
                    tcpSocket->write("FileHead recv");
                }else{
                    //接收处理文件
                    qint64 len = file.write(buf);
                    recvSize += len;

                    ui->progressBar->setValue(recvSize);
                    if(recvSize == fileSize){
                        file.close();
                        QMessageBox::information(this,"完成","文件接收完成");

                        tcpSocket->write("file write done");
                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();
                    }
                }
            }
            );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    QString ip = ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();
    QMessageBox::information(this,"连接状态","服务器连接成功");
    tcpSocket->connectToHost(QHostAddress(ip),port);
    isStart = true;

}
