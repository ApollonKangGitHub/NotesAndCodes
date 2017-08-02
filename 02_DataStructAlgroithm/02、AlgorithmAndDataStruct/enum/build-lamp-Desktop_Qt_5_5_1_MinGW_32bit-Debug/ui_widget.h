/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonPrompt;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonRestart;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 350);
        Widget->setMinimumSize(QSize(400, 350));
        Widget->setMaximumSize(QSize(400, 350));
        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 290, 321, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(23, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        buttonPrompt = new QPushButton(widget);
        buttonPrompt->setObjectName(QStringLiteral("buttonPrompt"));
        buttonPrompt->setMinimumSize(QSize(100, 50));
        buttonPrompt->setMaximumSize(QSize(100, 50));
        QFont font;
        font.setFamily(QStringLiteral("04b_21"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        buttonPrompt->setFont(font);

        horizontalLayout->addWidget(buttonPrompt);

        horizontalSpacer = new QSpacerItem(24, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonRestart = new QPushButton(widget);
        buttonRestart->setObjectName(QStringLiteral("buttonRestart"));
        buttonRestart->setMinimumSize(QSize(100, 50));
        buttonRestart->setMaximumSize(QSize(100, 50));
        buttonRestart->setFont(font);

        horizontalLayout->addWidget(buttonRestart);

        horizontalSpacer_3 = new QSpacerItem(23, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        buttonPrompt->setText(QApplication::translate("Widget", "\345\205\250\351\203\250\346\217\220\347\244\272", 0));
        buttonRestart->setText(QApplication::translate("Widget", "\351\207\215\346\226\260\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
