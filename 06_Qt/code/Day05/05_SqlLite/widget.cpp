#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QVariantList> //泛型
#include <QSqlQuery>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //打印Qt支持的数据库驱动
    //qDebug() << QSqlDatabase::drivers();

    //添加SqlLite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("../info.db");   //只需要提前创建好静态“.db”文件不需要借助数据库，也不需要密码、IP等

    //打开数据库
    if( false == db.open() ){
        //数据库打开失败，打开失败则提示错误信息
        QMessageBox::warning(this,"打开错误",db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("create table student(id int primary key, name varchar(255), age int, score int);");

    //插入
    query.prepare("insert into student(id, name, age, score) values(:id, :name, :age, :score);");
    QVariantList nameList;
    nameList << "xiaoD" << "xiaogE" << "xiaoF";
    QVariantList ageList;
    ageList << 20 << 17 <<19;
    QVariantList scoreList;
    scoreList << 87 << 84 << 91;
    QVariantList idList;
    idList << 148 << 149 << 150;
    //给字段绑定,不受顺序限制
    query.bindValue(":age",ageList);
    query.bindValue(":score",scoreList);
    query.bindValue(":name",nameList);
    query.bindValue(":id",idList);
    //执行预处理命令
    query.execBatch();

    query.exec("select * from student");//*全部匹配
    while(query.next()){//一行一行遍历，下一条记录不存在则返回0
        //取出当前行的内容(以列为单位)
        qDebug()<< query.value(0).toInt()//第一种方式:去除第0列，即ID
                << query.value(1).toString()//第1列，即name
                << query.value("age").toInt()//第二种方式：age字段的列
                << query.value("score").toInt();//score字段的列
    }
}

Widget::~Widget()
{
    delete ui;
}
