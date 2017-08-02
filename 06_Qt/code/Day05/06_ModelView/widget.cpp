#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //添加MySql数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //连接数据库，必须先安装数据库
    db.setHostName("127.0.0.1");//数据库服务器IP
    db.setUserName("root");//数据库用户名
    db.setPassword("mysql");//密码
    db.setDatabaseName("info");//使用哪个数据库

    //打开数据库
    if( false == db.open() ){
        //数据库打开失败，打开失败则提示错误信息
        QMessageBox::warning(this,"打开错误",db.lastError().text());
        return;
    }

    //设置模型
    model = new QSqlTableModel(this);
    model->setTable("student");//指定使用哪个表

    //把model放到view中
    ui->tableView->setModel(model);

    //显示model中的数据
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(0, Qt::Horizontal, "年龄");
    model->setHeaderData(0, Qt::Horizontal, "成绩");

    //设置model的编辑模式：手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置view中的数据库不允许修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();  //获取空记录
    //获取行号
    int row = model->rowCount();
    model->insertRecord(row,record);
}

void Widget::on_pushButtonSure_clicked()
{
    model->submitAll(); //提交所有动作
}

void Widget::on_pushButtonCancel_clicked()
{
    model->revertAll(); //撤销所有动作
    model->submitAll(); //提交所有动作
}

void Widget::on_pushButtonDel_clicked()
{
    //获取选中的模型
    QItemSelectionModel* sModel =  ui->tableView->selectionModel();
    //去除模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i<list.size(); i++){
        model->removeRow(list.at(i).row());
    }
}

void Widget::on_pushButtonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);
    model->setFilter(str);
    model->select();
}
