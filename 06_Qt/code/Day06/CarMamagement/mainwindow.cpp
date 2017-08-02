#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "domXml.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //开始时为车辆管理页面
    on_actionCar_triggered();
    //打开数据库
    connectDB();

    //初始化
    initData();

    //创建空的Xml文件
    DomXml::createXml("../demo.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//车辆管理菜单
void MainWindow::on_actionCar_triggered()
{
    //切换到车辆管理页面
    ui->stackedWidget->setCurrentWidget(ui->pageCar);
    ui->labelTitle->setText("车辆管理");
}
//销售统计菜单
void MainWindow::on_actionCalc_triggered()
{
    //切换到销售统计页面
    ui->stackedWidget->setCurrentWidget(ui->pageCalc);
    ui->labelTitle->setText("销售统计");
}
//连接数据库
void MainWindow::connectDB()
{
    //添加选择数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("mysql");
    db.setDatabaseName("car");

    //打开数据库
    if(false == db.open()){
        QMessageBox::warning(this,"数据库打开失败",db.lastError().text());
        return;
    }
}

void MainWindow::initData()
{
    //下拉框由数据库中获取的值来设置
    QSqlQueryModel * queryModel = new QSqlQueryModel(this);//新建模型
    queryModel->setQuery("select name from factory");//sql语句
    ui->comboBoxFactory->setModel(queryModel);

    ui->labelLast->setText("0");//剩余数量初始化为0
    ui->lineEditTotal->setEnabled(false);//金额设置为只读
}

//对于厂家下拉框的修改的信号处理
void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &factory)
{
    //厂家下拉框槽函数
    if(factory == "请选择厂家"){    //factory是信号发送时携带的参数：下拉框选项内容(即选定的厂家)
        //选择的不是具体厂家，则清空
        ui->comboBoxBrand->clear();     //品牌下拉框清空
        ui->lineEditPrice->clear();     //价格清空
        ui->spinBoxNumber->setValue(0); //数量选择框清零
        ui->labelLast->setText("0");    //剩余数量清空
        ui->lineEditTotal->clear();     //总价清空

        ui->spinBoxNumber->setEnabled(false);   //数量最开始(没有选中品牌时)不能选择
        ui->pushButtonSure->setEnabled(false);
    }else{
        ui->comboBoxBrand->clear();
        QSqlQuery query;
        QString sql = QString("select name from brand where factory = '%1'").arg(factory);
        query.exec(sql);//执行Sql获取指定属性的所有记录

        //获取每一条记录
        while(query.next()){
            QString name = query.value(0).toString();
            ui->comboBoxBrand->addItem(name);   //添加到品牌下拉框
        }
        ui->spinBoxNumber->setEnabled(true);   //品牌选中后可以选择数量
    }
}
//品牌下拉框
void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &name)
{
    ui->spinBoxNumber->setValue(0);
    QSqlQuery query;
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'")
            .arg(ui->comboBoxFactory->currentText())    //厂家下拉框当前选中内容
            .arg(name);  //信号传递的品牌名
    query.exec(sql);//执行Sql获取指定属性的所有记录

    //获取每一条记录
    while(query.next()){
        //报价
        int price = query.value("price").toInt();
        //剩余数目
        int last = query.value("last").toInt();

        //更新到对应控件
        ui->lineEditPrice->setText(QString::number(price));//QString::number()整型转换为字符串
        ui->labelLast->setText(QString::number(last));
    }
}

//数量选择框槽函数
void MainWindow::on_spinBoxNumber_valueChanged(int number)
{
    if( 0 == number ){
        ui->pushButtonSure->setEnabled(false);
    }else{
        ui->pushButtonSure->setEnabled(true);
    }
    //更新剩余数量
    //获取数据库剩余的数量
    QSqlQuery query;
    QString sql = QString("select last from brand where factory = '%1' and name = '%2'")
                        .arg(ui->comboBoxFactory->currentText())
                        .arg(ui->comboBoxBrand->currentText());
    //执行Sql语句
    query.exec(sql);

    int last;
    while(query.next()){
        last = query.value("last").toInt(); //剩余数量要从未更新的数据库中获取
        //不能从实时更新的剩余的标签中获取，否则有Bug（成倍减少如）
    }

    if(number > last){
        ui->spinBoxNumber->setValue(last);
        return; //如果选择的数目大小多于剩余程序则结束
    }

    int tempNum = last - number;
    ui->labelLast->setText(QString::number(tempNum));//剩余
    //金额
    int price = ui->lineEditPrice->text().toInt();//报价
    int sum = price * number;
    ui->lineEditTotal->setText(QString::number(sum));
}

void MainWindow::on_pushButtonCancel_clicked()
{
    //取消即重新初始化
    ui->comboBoxFactory->setCurrentIndex(0);
    //ui->labelLast->setText("0");
}

void MainWindow::on_pushButtonSure_clicked()
{
    //获取信息
    //销售数量
    int num = ui->spinBoxNumber->value();
    //剩余数量
    int last = ui->labelLast->text().toInt();

    QSqlQuery query;
    QString sql = QString("select sell from brand where factory = '%1' and name = '%2'")
                    .arg(ui->comboBoxFactory->currentText())
                    .arg(ui->comboBoxBrand->currentText());
    //执行Sql语句
    query.exec(sql);

    int sell;
    while(query.next()){
        sell = query.value("sell").toInt();
    }
    //更新数据库剩余数量与销售总量
    sell += num;

    sql = QString("update brand set sell = %1, last = %2 where factory = '%3' and name = '%4'")
                        .arg(sell)
                        .arg(last)
                        .arg(ui->comboBoxFactory->currentText())
                        .arg(ui->comboBoxBrand->currentText());

    //把确认后的数据，更新到XML中
    QStringList list;
    list << ui->comboBoxFactory->currentText()
         << ui->comboBoxBrand->currentText()
         << ui->lineEditPrice->text()
         << QString::number(num)
         << ui->lineEditTotal->text();

    DomXml::appendXml("../demo.xml",list);

    QStringList factoryList;
    QStringList brandList;
    QStringList priceList;
    QStringList numList;
    QStringList totalList;
    DomXml::readXml("../demo.xml",factoryList,brandList,priceList,numList,totalList);
    ui->textEdit->clear();
    for(int i = 0; i < factoryList.size(); i++){//size()都是一样的，所以brand.size()也可以
        QString str = QString("<h3>%1:%2,卖出:%3台,单价:%4,总价:%5</h3>")
                .arg(factoryList.at(i))
                .arg(brandList.at(i))
                .arg(numList.at(i))
                .arg(priceList.at(i))
                .arg(totalList.at(i));
        ui->textEdit->append(str);
    }

    query.exec(sql);
    on_pushButtonCancel_clicked();
}
