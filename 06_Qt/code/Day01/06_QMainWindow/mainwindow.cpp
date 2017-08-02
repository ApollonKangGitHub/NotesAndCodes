#include "mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>   //Desktop信息
#include <QApplication>
#include <QMenuBar>         //菜单栏
#include <QMenu>            //菜单
#include <QAction>          //动作
#include <QToolBar>         //工具栏
#include <QPushButton>
#include <QStatusBar>       //状态栏
#include <QLabel>           //标签
#include <QTextEdit>        //文本编辑
#include <QDockWidget>      //浮动窗口

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //带标题栏、菜单栏、工具栏、状态栏、浮动窗口等的主窗口

    //设置窗口大小为屏幕大小
    GetScreenSize();
    this->resize(screenWidth-15,screenHeight-80);
    //标题栏
    this->setWindowTitle("The First");  //可以用stata()这种函数读取一些文件信息作为标题
    SetMenuAndTool();   //设置菜单栏和工具栏
    SetDockAndTest();   //设置浮动窗口与核心控件
    SetStatus();        //设置状态栏
}
void MainWindow::SetMenuAndTool()
{
    //菜单栏
    QMenuBar * pMenuBar = menuBar();
    //添加菜单
    QMenu * pFile = pMenuBar->addMenu("文件(F)");
    QMenu * pEdit = pMenuBar->addMenu("编辑(E)");
    //添加菜单项（添加动作），点击会产生信号，因此相应的反应是对相应的信号的操作
    QAction * pFiNew = pFile->addAction("New");
    QAction * pFiOpen = pFile->addAction("Open");
    pFile->addSeparator();  // 添加分割线
    QAction * pFiClose = pFile->addAction("Close");

    //动作处理
    connect(pFiNew,&QAction::triggered,[=](){qDebug()<<"New press is pressed!";});
    connect(pFiOpen,&QAction::triggered,[=](){qDebug()<<"Open press is pressed!";});

    //创建工具栏
    QToolBar * pToolBar = addToolBar("ToolBar");
    //工具栏添加快捷键
    pToolBar->addAction(pFiNew);
    pToolBar->addAction(pFiOpen);
    pToolBar->addAction(pFiClose);
    //添加小控件
    QPushButton * b = new QPushButton(this);
    b->setText("Save");
    pToolBar->addWidget(b);
    connect(b,&QPushButton::clicked,[=](){b->setText("Success");});
}
void MainWindow::SetDockAndTest()
{
    //核心控件：文本编辑器
    QTextEdit * pTestEdit = new QTextEdit(this);
    setCentralWidget(pTestEdit);    //设置核心控件为文本编辑器

    //设置浮动窗口
    QDockWidget * pDockPro = new QDockWidget("Project",this);
    addDockWidget(Qt::LeftDockWidgetArea,pDockPro);   //第一个参数是放的位置
    QTextEdit * pTestEditDock = new QTextEdit(this);    //向浮动窗口中添加控件(文本编辑器)
    pDockPro->setWidget(pTestEditDock);
    QDockWidget * pDockDebug = new QDockWidget("Debug",this);   //再创建一个浮动窗口
    addDockWidget(Qt::BottomDockWidgetArea,pDockDebug);
}
void MainWindow::SetStatus()
{
       //创建状态栏
       QStatusBar * pStatusBar =  statusBar();
       QLabel * pLabel = new QLabel(this);
       pLabel->setText("Normal text file");
       pStatusBar->addWidget(pLabel);
       //从左往右添加
       pStatusBar->addWidget(new QLabel("\t\tEFFL 80.074586",this));
       //从右往左添加
       pStatusBar->addPermanentWidget(new QLabel("WFNO 6.5\t\t",this));
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

MainWindow::~MainWindow()
{

}
