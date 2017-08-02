#include "domxml.h"

#include <QFile>
#include <QDomDocument>                 //文件
#include <QDomProcessingInstruction>    //格式头部
#include <QDomElement>                  //元素（节点）
#include <QTextStream>                  //文本流
#include <QDebug>
#include <QDateTime>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

DomXml::DomXml()
{

}

void DomXml::createXml(QString filePath)
{
    QFile file(filePath);
    if(true == file.exists()){
        //如果存在不创建
        cout<<"文件已经存在";
        return;
    }
    else{
        //不存在则创建
        if(true == file.open(QIODevice::WriteOnly)){
            //打开成功，创建Xml文档
            QDomDocument doc;
            //创建Xml头部格式 <?xml version="1.0" encoding="UTF-8"?>
            QDomProcessingInstruction ins;
            //头结点固定格式信息，引号需要\转义
            ins = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            //追加元素（节点）
            doc.appendChild(ins);

            //根节点元素
            QDomElement root = doc.createElement("日销售清单");
            doc.appendChild(root);

            //保存
            QTextStream stream(&file);//文本流关联文件
            doc.save(stream,4);//4表示自动缩进的字符数

            file.close();   //关闭文件
        }
        else{
            //打开失败
            cout<<"Open of WriteOnly error";
            return;
        }
    }
}
#if 0
    如果没有子节点
    在根下创建<日期>子节点
    在<日期>设置属性
    在<日期>创建时间子节点
    在<时间>设置属性
    在时间下创建<厂家>子节点
    在<厂家>设置属性
    ......
#endif
void DomXml::appendXml(QString filePath, QStringList list)
{
    QFile file(filePath);

    if(true == file.open(QIODevice::ReadOnly)){
        //打开成功,文件file和XML文档对象关联
        QDomDocument doc;
        if(true == doc.setContent(&file)){
            file.close();//如果关联成功便可关闭文件
            QDomElement root = doc.documentElement();//获取根节点元素

            //获取当前时间（日期）
            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");//2017-6-23

            //判断根节点上有没有子节点
            if(root.hasChildNodes()){//有子节点
                //查找最后一个子节点
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr){
                    //存在当天的记录
                    writeXml(doc,lastEmt,list);//写有效销售数据，并是lastEmt日期的子节点
                }else{//没有当天的记录
                    NewDateNode(doc,root,list,dateStr);
                }
            }
            else{//没有子节点
                NewDateNode(doc,root,list,dateStr);
            }
            //保存文件
            if(true == file.open(QIODevice::WriteOnly)){
                QTextStream stream(&file);
                doc.save(stream,4);//缩进四字符
                file.close();
            }
        }
        else{
            cout << "setContent error";
        }
    }
    else{
        //打开失败
        cout<<"Open of WriteOnly error";
    }

}
void DomXml::NewDateNode(QDomDocument &doc, QDomElement &root, QStringList &list, QString dateStr)
{
    QDomElement dateEmt = doc.createElement("日期");//创建日期子节点
    QDomAttr dateAttr = doc.createAttribute("date");//创建Date属性
    dateAttr.setNodeValue(dateStr);//设置属性值
    dateEmt.setAttributeNode(dateAttr);//关联节点和属性
    root.appendChild(dateEmt);//把日期节点追加到根节点
    writeXml(doc,dateEmt,list);//写有效销售数据
}
void DomXml::writeXml(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    //获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("h:m:s ap");//10:29:41 AM/PM

    //创建时间节点元素（与append()的步骤类似）
    QDomElement timeEmt = doc.createElement("时间");
    //创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    //给属性设置值
    timeAttr.setNodeValue(timeStr);
    //属性与时间节点关联
    timeEmt.setAttributeNode(timeAttr);
    //把时间追加到日期节点下
    root.appendChild(timeEmt);//这里的root是传过来的日期节点（相对根节点）

    //创建子节点
    QDomElement factory = doc.createElement("厂家");
    QDomElement brand = doc.createElement("品牌");
    QDomElement price = doc.createElement("报价");
    QDomElement num = doc.createElement("数量");
    QDomElement total = doc.createElement("金额");

    //给各个节点设置内容
    QDomText text = doc.createTextNode(list.at(0));
    factory.appendChild(text);
    text = doc.createTextNode(list.at(1));
    brand.appendChild(text);
    text = doc.createTextNode(list.at(2));
    price.appendChild(text);
    text = doc.createTextNode(list.at(3));
    num.appendChild(text);
    text = doc.createTextNode(list.at(4));
    total.appendChild(text);

    //将各个子节点追加到时间节点下
    timeEmt.appendChild(factory);
    timeEmt.appendChild(brand);
    timeEmt.appendChild(price);
    timeEmt.appendChild(num);
    timeEmt.appendChild(total);
}
void DomXml::readXml(QString filePath, QStringList &factoryList, QStringList &brandList, QStringList &priceList, QStringList &numList, QStringList &totalList)
{
    QFile file(filePath);

    if(true == file.open(QIODevice::ReadOnly)){
        //打开成功,文件file和XML文档对象关联
        QDomDocument doc;
        if(true == doc.setContent(&file)){
            file.close();//关联成功文件可以关闭

            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");

            QDomElement root = doc.documentElement();//获取根节点

            if(true == root.hasChildNodes()){
                //找最后一个节点
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr){//判断有无当前日期
                    //取得当前日期下所有时间的子节点
                    QDomNodeList list = lastEmt.childNodes();
                    for(int i = 0; i < list.size(); i++){
                        //list.at()返回值为QDomNode，转换成元素，获取到某一个时间节点下的所有子节点
                        QDomNodeList subList = list.at(i).toElement().childNodes();

                        //将List中的每个元素取出来追加到指定的List中去
                        QString factory = subList.at(0).toElement().text();
                        factoryList.append(factory);

                        QString brand = subList.at(1).toElement().text();
                        brandList.append(brand);

                        QString price = subList.at(2).toElement().text();
                        priceList.append(price);

                        QString num = subList.at(3).toElement().text();
                        numList.append(num);

                        QString total = subList.at(4).toElement().text();
                        totalList.append(total);
                    }
                }
                else{
                    cout<<"没有当前日期";
                }
            }
            else{
                cout << "没有子节点";
                return;
            }
        }
        else{
            cout << "setContent error";
            return;
        }
    }
    else{
        cout<<"Open of ReadOnly error";
        return;
    }
}
