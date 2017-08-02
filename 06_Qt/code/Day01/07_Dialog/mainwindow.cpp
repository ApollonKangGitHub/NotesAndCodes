#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>  //文件对话框

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("TEST Modal and NonModal");
    GetScreenSize();
    this->resize(screenWidth-500,screenHeight-300);

    QMenuBar *mBar = menuBar(); //创建一个菜单栏
    setMenuBar(mBar);           //设置菜单栏
    QMenu * menu = mBar->addMenu("对话框");    //在菜单栏中设置菜单
    QAction *pModal = menu->addAction("模态对话框");
    QAction *pNonModal = menu->addAction("非模态对话框");

    connect(pModal, &QAction::triggered,
            [](){QDialog dlg;dlg.exec();qDebug()<<"Modal is Over";}
    );
    //dlg.exec()是阻塞式的，不结束则所有其他操作不能进行

    connect(pNonModal, &QAction::triggered,
            //①逻辑没错但是效果没有
            //[](){QDialog dlg;dlg.show();qDebug()<<"Modal is Over";}
            #if 0
            //②dlg.show()是非阻塞式的，其作用域只在Lamda函数中，所以需要将dlg作为类的成员，
            //不至于Lamda结束时窗口也跟着关闭，但是过多成员的话显得类有点臃肿
            [=](){dlg.show();qDebug()<<"Modal is Over";}
            #endif
            #if 0
            //③当然要想用局部变量，也可以new一个堆内存，并与this对象建立关系树的连接(设置为this的子窗口)
            //使得Lamda结束内存也不会被回收show（）可以继续显示.关闭主窗口之后，非模态对话框会随之关闭
            [=](){QDialog *log = new QDialog(this);log->show();qDebug()<<"Modal is Over";}
            #endif
            #if 1
            //④但是，如果指定其父对象为主窗口，但是窗口一直不结束，并且按了N多次非模态对话框，则内存会越用越少
            //那么就不设置其父对象，而仅仅设置其属性为Qt::WA_DeleteOnClose(关闭时释放)
            [=](){
                QDialog *log = new QDialog;
                log->setAttribute(Qt::WA_DeleteOnClose);
                log->show();
                qDebug()<<"Modal is Over";
            }
            #endif
    );

    //关于问题对话框：一般提示性的对话框，如版本信息、是否保存/关闭等等
    //这类对话框是比较现成的，只需要设定参数即可

    //关于对话框：显示版本信息(属于单提示类的信息显示对话框)
    QAction *pAbout = menu->addAction("版本信息(V)");

    connect(pAbout, &QAction::triggered,
            [=](){
                //静态成员函数通过类名来调用
                QMessageBox::about(this,"About Version","Time:2017年5月22日00:00:48\n"
                                                  "Mail:mailbox_krj@163.com\n"
                                                  "Version:V1.1.0\n");
            }
    );

    //问题对话框，选择信息提示，一般是文件保存、文件关闭时的提示信息等
    QAction *pQuestion = menu->addAction("关闭窗口(S)");
    connect(pQuestion, &QAction::triggered,
            [=](){
                //默认两个选项： QMessageBox::Yes与 QMessageBox::No
                //int ret = QMessageBox::question(this,"Question","关闭前是否保存文件");
                //设置选项：
                int ret = QMessageBox::question(this,"Question Close","关闭前是否保存文件",
                                                QMessageBox::Ok | QMessageBox::Cancel);
                switch(ret){
                    case QMessageBox::Yes:
                        qDebug() << "Choose Yes,Save success!";
                    break;
                    case QMessageBox::No:
                        qDebug() << "Choose No,Save Failure!";
                    break;
                    case QMessageBox::Ok:
                        qDebug() << "Choose Ok,Save success!";
                    break;
                    case QMessageBox::Cancel:
                        qDebug() << "Choose Cancel,Save Failure!";
                    break;
                    default:
                    break;
                }
                close();
            }
    );

    //文件对话框:可以获取路径等
    QAction *pFile = menu->addAction("文件(F)");

    connect(pFile, &QAction::triggered,
            [=](){
                QString path = QFileDialog::getOpenFileName(
                            this,
                            "open",  //对话框标题
                            "../",   //路径
                            "source(*.c *.cpp *.sh *.h);;"  //过滤文件类型，指定类型名，用括号括起来列举的类型名
                            "text(*.pdf *.txt *.doc);;"     //两个分号隔开一种类型，列举该类型中的格式用空格隔开
                            "all(*.*)"
                            );  //返回一个完整路径
                qDebug() << path;
            }
    );

}

MainWindow::~MainWindow()
{

}
void MainWindow::GetScreenSize()
{
    QDesktopWidget *deskWgt = QApplication::desktop();
    if (deskWgt) {
        QRect screenRect = deskWgt->screenGeometry();
        screenWidth = screenRect.width();
        screenHeight = screenRect.height();
        //qDebug() << "screen width:" <<screenWidth << ",height:" << screenHeight;
    }
}
