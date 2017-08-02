/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *buttonConnect;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *labelIp;
    QLineEdit *lineEditIp;
    QLabel *labelPort;
    QLineEdit *lineEditPort;
    QLabel *labelProg;
    QProgressBar *progressBar;

    void setupUi(QWidget *ClientWidget)
    {
        if (ClientWidget->objectName().isEmpty())
            ClientWidget->setObjectName(QStringLiteral("ClientWidget"));
        ClientWidget->resize(399, 300);
        ClientWidget->setMaximumSize(QSize(400, 300));
        gridLayout = new QGridLayout(ClientWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ClientWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        buttonConnect = new QPushButton(ClientWidget);
        buttonConnect->setObjectName(QStringLiteral("buttonConnect"));

        gridLayout->addWidget(buttonConnect, 1, 0, 1, 1);

        widget = new QWidget(ClientWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelIp = new QLabel(widget);
        labelIp->setObjectName(QStringLiteral("labelIp"));

        gridLayout_2->addWidget(labelIp, 0, 0, 1, 1);

        lineEditIp = new QLineEdit(widget);
        lineEditIp->setObjectName(QStringLiteral("lineEditIp"));

        gridLayout_2->addWidget(lineEditIp, 0, 1, 1, 1);

        labelPort = new QLabel(widget);
        labelPort->setObjectName(QStringLiteral("labelPort"));

        gridLayout_2->addWidget(labelPort, 1, 0, 1, 1);

        lineEditPort = new QLineEdit(widget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));

        gridLayout_2->addWidget(lineEditPort, 1, 1, 1, 1);

        labelProg = new QLabel(widget);
        labelProg->setObjectName(QStringLiteral("labelProg"));

        gridLayout_2->addWidget(labelProg, 2, 0, 1, 1);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout_2->addWidget(progressBar, 2, 1, 1, 1);


        gridLayout->addWidget(widget, 2, 0, 1, 1);


        retranslateUi(ClientWidget);

        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        ClientWidget->setWindowTitle(QApplication::translate("ClientWidget", "Form", 0));
        label->setText(QApplication::translate("ClientWidget", "\345\256\242\346\210\267\347\253\257", 0));
        buttonConnect->setText(QApplication::translate("ClientWidget", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", 0));
        labelIp->setText(QApplication::translate("ClientWidget", "\346\234\215\345\212\241\345\231\250IP\357\274\232", 0));
        lineEditIp->setText(QApplication::translate("ClientWidget", "127.0.0.1", 0));
        labelPort->setText(QApplication::translate("ClientWidget", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", 0));
        lineEditPort->setText(QApplication::translate("ClientWidget", "8888", 0));
        labelProg->setText(QApplication::translate("ClientWidget", "\350\277\233\345\272\246\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
