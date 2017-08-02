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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLCDNumber *lcdNumberWhite;
    QLCDNumber *lcdNumberBlack;
    QToolButton *toolButtonstart;
    QToolButton *toolButtonQuit;
    QLabel *labelWhite;
    QLabel *labelBlack;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        Widget->setMinimumSize(QSize(800, 600));
        Widget->setMaximumSize(QSize(800, 600));
        lcdNumberWhite = new QLCDNumber(Widget);
        lcdNumberWhite->setObjectName(QStringLiteral("lcdNumberWhite"));
        lcdNumberWhite->setGeometry(QRect(10, 140, 71, 51));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcdNumberWhite->setPalette(palette);
        lcdNumberWhite->setFrameShape(QFrame::NoFrame);
        lcdNumberWhite->setDigitCount(4);
        lcdNumberBlack = new QLCDNumber(Widget);
        lcdNumberBlack->setObjectName(QStringLiteral("lcdNumberBlack"));
        lcdNumberBlack->setGeometry(QRect(720, 140, 71, 51));
        lcdNumberBlack->setFrameShape(QFrame::NoFrame);
        lcdNumberBlack->setDigitCount(4);
        toolButtonstart = new QToolButton(Widget);
        toolButtonstart->setObjectName(QStringLiteral("toolButtonstart"));
        toolButtonstart->setGeometry(QRect(120, 540, 111, 51));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonstart->setIcon(icon);
        toolButtonstart->setIconSize(QSize(200, 200));
        toolButtonstart->setAutoRaise(true);
        toolButtonQuit = new QToolButton(Widget);
        toolButtonQuit->setObjectName(QStringLiteral("toolButtonQuit"));
        toolButtonQuit->setGeometry(QRect(570, 540, 111, 51));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/end.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonQuit->setIcon(icon1);
        toolButtonQuit->setIconSize(QSize(200, 200));
        toolButtonQuit->setAutoRaise(true);
        labelWhite = new QLabel(Widget);
        labelWhite->setObjectName(QStringLiteral("labelWhite"));
        labelWhite->setGeometry(QRect(3, 61, 71, 61));
        labelWhite->setPixmap(QPixmap(QString::fromUtf8(":/image/White.png")));
        labelWhite->setScaledContents(true);
        labelBlack = new QLabel(Widget);
        labelBlack->setObjectName(QStringLiteral("labelBlack"));
        labelBlack->setGeometry(QRect(723, 60, 71, 61));
        labelBlack->setPixmap(QPixmap(QString::fromUtf8(":/image/Black.png")));
        labelBlack->setScaledContents(true);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 781, 50));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        layoutWidget->raise();
        lcdNumberWhite->raise();
        lcdNumberBlack->raise();
        toolButtonQuit->raise();
        labelWhite->raise();
        labelBlack->raise();
        toolButtonstart->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        toolButtonstart->setText(QString());
        toolButtonQuit->setText(QString());
        labelWhite->setText(QString());
        labelBlack->setText(QString());
        label->setText(QApplication::translate("Widget", "\350\220\214\346\226\260\344\270\216\346\273\221\347\250\275\347\232\204\345\257\271\345\274\210", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
