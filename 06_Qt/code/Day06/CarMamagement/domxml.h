#ifndef DOMXML_H
#define DOMXML_H

#include <QString>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>

class DomXml
{
public:
    DomXml();
    //静态不需要通过类来调用
    static void createXml(QString filePath);//创建Xml信息
    //list.at(0) = 二汽神龙，list.at(1) = 毕加索
    static void appendXml(QString filePath,QStringList list);//追加XML信息
    static void writeXml(QDomDocument &doc, QDomElement &root, QStringList &list);
    static void NewDateNode(QDomDocument &doc, QDomElement &root, QStringList &list, QString dateStr);

    static void readXml(QString filePath,
                        QStringList &factoryList,
                        QStringList &brandList,
                        QStringList &priceList,
                        QStringList &numList,
                        QStringList &totalList
                        );
};

#endif // DOMXML_H
