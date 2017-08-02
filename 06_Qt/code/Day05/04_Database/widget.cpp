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
    qDebug() << QSqlDatabase::drivers();
    //"QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7"

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

    QSqlQuery query;
    //query.exec("");中放sql语句
    //创建表
    query.exec("create table student(id int primary key auto_increment, name varchar(255), age int, score int);");
    //primary key:主键；auto_increment:自动增加
                                    #if 0
                                        //添加第二个MySql数据库并创建一张表
                                        QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL","abcd");//指定名字

                                        //连接数据库，必须先安装数据库
                                        db1.setHostName("127.0.0.1");//数据库服务器IP
                                        db1.setUserName("root");//数据库用户名
                                        db1.setPassword("mysql");//密码
                                        db1.setDatabaseName("test");//使用哪个数据库

                                        //打开数据库
                                        if( false == db1.open() ){
                                            //数据库打开失败，打开失败则提示错误信息
                                            QMessageBox::warning(this,"打开错误",db.lastError().text());
                                            return;
                                        }

                                        QSqlQuery query1(db1);//创建QSqlDatabase对象时指定名字，这里则必须将QSqlDatabase对象传递进来，否则不可以
                                        query1.exec("create table student(id int primary key, name varchar(255), age int, score int);");
                                    #endif
    //插入
    query.exec("insert into student(id, name, age, score) values(1, 'mike', 18, 99);");

    //批量插入
#if 0
    //odbc风格
    //预处理语句:?相当于占位符
    query.prepare("insert into student(name, age, score) values(?, ?, ?);");
    //给字段设置内容：list
    QVariantList nameList;
    nameList << "xiaoA" << "xiaogB" << "xiaoC";
    QVariantList ageList;
    ageList << 21 << 22 <<20;
    QVariantList scoreList;
    scoreList << 77 << 78 << 85;
    //给字段绑定相应的值:按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    query.addBindValue(scoreList);
    //执行预处理命令
    query.execBatch();
#endif

#if 1
    //oracle风格
    //占位符":自定义名字"
    query.prepare("insert into student(name, age, score) values(:name, :age, :score);");
    QVariantList nameList;
    nameList << "xiaoD" << "xiaoE" << "xiaoF";
    QVariantList ageList;
    ageList << 20 << 17 <<19;
    QVariantList scoreList;
    scoreList << 87 << 84 << 91;
    //给字段绑定,不受顺序限制
    query.bindValue(":age",ageList);
    query.bindValue(":score",scoreList);
    query.bindValue(":name",nameList);
    //执行预处理命令
    query.execBatch();
#endif
    //query.exec("select * from student");//*全部匹配
    query.exec("select * from student where name = 'xiaoA'");//限制性匹配
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

void Widget::on_Widget_destroyed()
{

}

void Widget::on_pushSureDelete_clicked()
{
    //确定删除
    QSqlDatabase::database().commit();
}

void Widget::on_pushCanel_clicked()
{
    //回滚即撤销
    QSqlDatabase::database().rollback();
}

void Widget::on_pushDelete_clicked()
{
    //获取行编辑内容
    QString name = ui->lineEdit->text();

    QString  sql = QString("delete from student where name = '%1'").arg(name);
    //开启一个事务（还原点）
    QSqlDatabase::database().transaction();//获取的是当前正在操作的数据库
    QSqlQuery query;
    query.exec(sql);
}
