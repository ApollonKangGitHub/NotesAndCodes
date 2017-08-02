#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QByteArray>
#include <QMessageBox>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    //创建对象指定父对象
    tcpServer = new QTcpServer(this);
    //绑定监听
    tcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器端口：8888");

    //两个按钮最开始都不能按
    ui->buttonChooseFile->setEnabled(false);
    ui->butttonSendFile->setEnabled(false);

    //如果客户端和服务器成功连接
    //tcpServer会自动触发newConnection()信号
    connect(tcpServer,&QTcpServer::newConnection,
            [=](){
                //获取通信套接字
                tcpSocket = tcpServer->nextPendingConnection();
                //获取对方IP、port
                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();

                QString str = QString("[%1:%2]:成功连接").arg(ip).arg(port);
                ui->textEdit->append(str);

                //成功连接后可以选择
                ui->buttonChooseFile->setEnabled(true);

                connect(tcpSocket, QTcpSocket::readyRead,
                        [=](){
                            QByteArray buf = tcpSocket->readAll();
                            #if 1
                            //采用回射信息进行粘包处理
                            if("FileHead recv" == QString(buf)){
                                ui->textEdit->append("文件头部接收成功，开始发送文件...");
                                sendData();
                            }
                            #endif
                            if("file write done" == QString(buf)){
                                QMessageBox::information(this,"完成","对端接收完成");
                                file.close();
                                tcpSocket->disconnectFromHost();
                                tcpSocket->close();
                            }
                        }
                        );
            }
            );
    #if 0
    //采用定时器进行粘包处理
    connect(&timer,&QTimer::timeout,
            [=](){
                //关闭定时器
                timer.stop();
                //发送文件
                sendData();
            }
            );
    #endif
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//选择文件
void ServerWidget::on_buttonChooseFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(false == filePath.isEmpty()){    //路径有效
        fileName.clear();
        fileSize = 0;
        //获取文件信息：名字、大小
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        sendSize = 0;   //已经发送文件大小

        //以只读方式打开文件
        file.setFileName(filePath);
        if(false == file.open(QIODevice::ReadOnly)){
            ui->textEdit->append("只读方式打开文件失败");
        }
        //提示已经打开的文件路径
        ui->textEdit->append(filePath);

        //可以发送
        ui->buttonChooseFile->setEnabled(false);  //只能选择一次
        ui->butttonSendFile->setEnabled(true);
    }
    else{
        ui->textEdit->append("选择文件路径无效：SERVER80");
    }
}

void ServerWidget::on_butttonSendFile_clicked()
{
    //发送按钮已经点击，发送过程中不能再点击，恢复按钮初始化
    ui->buttonChooseFile->setEnabled(false);
    ui->butttonSendFile->setEnabled(false);
    //先发送文件头信息:文件名##大小
    //构造头部信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    qint64 len = tcpSocket->write(head.toUtf8());
#if 0
    if(len > 0){//头部信息发送成功
        //防止TCP粘包，定时器延时20ms发送文件内容
        timer.start(20);
    }
#endif
#if 1
    if(len < 0){
        ui->textEdit->append("文件头部信息发送失败！");
        //关闭文件
        file.close();
    }
#endif

}
void ServerWidget::sendData()
{
    qint64 len = 0;
    do{
        //一次发送的大小
        char buf[BUF_SIZE] = {0};
        len = 0;
        len = file.read(buf,BUF_SIZE);  //len为读取的字节数
        len = tcpSocket->write(buf,len);    //len为发送的字节数
        //已发数据累加
        sendSize += len;
    }while(len > 0);
#if 0
    if(fileSize == sendSize){
        QMessageBox::information(this,"完成","文件发送完成");
        ui->textEdit->append("文件发送完毕！"); //可以发现文件发送完毕以后进度条还没走完
        //虽然用判断回射信息的方式完成对对方是否完成接收判断，但是如果是小文件
        //由于QMessageBox的特点导致readyRead()信号可能未被接收到,导致之前的文件未被关闭、连接未断开
        //所以Cilent端的:
        //QMessageBox::information(this,"文件信息",str);应该暂时被注释掉
    }
#endif
}
