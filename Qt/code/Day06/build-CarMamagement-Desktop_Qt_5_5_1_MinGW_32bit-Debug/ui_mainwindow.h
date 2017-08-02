/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCar;
    QAction *actionCalc;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *pageCar;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *pageSellCar;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelFactory;
    QComboBox *comboBoxFactory;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelBrand;
    QComboBox *comboBoxBrand;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelPrice;
    QLineEdit *lineEditPrice;
    QLabel *labelPriceUnits;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelNumber;
    QSpinBox *spinBoxNumber;
    QLabel *labelLastNumber;
    QLabel *labelLast;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelTotal;
    QLineEdit *lineEditTotal;
    QLabel *labelTotalUnits;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonSure;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_6;
    QWidget *pageNewCar;
    QTextEdit *textEdit;
    QWidget *pageCalc;
    QWidget *widget;
    QWidget *widget_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(631, 400);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMaximumSize(QSize(800, 400));
        actionCar = new QAction(MainWindow);
        actionCar->setObjectName(QStringLiteral("actionCar"));
        actionCalc = new QAction(MainWindow);
        actionCalc->setObjectName(QStringLiteral("actionCalc"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(222, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        labelTitle = new QLabel(centralWidget);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(28);
        labelTitle->setFont(font);

        gridLayout->addWidget(labelTitle, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(221, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pageCar = new QWidget();
        pageCar->setObjectName(QStringLiteral("pageCar"));
        gridLayout_2 = new QGridLayout(pageCar);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(pageCar);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setMinimumSize(QSize(200, 0));
        toolBox->setMaximumSize(QSize(500, 16777215));
        pageSellCar = new QWidget();
        pageSellCar->setObjectName(QStringLiteral("pageSellCar"));
        pageSellCar->setGeometry(QRect(0, 0, 200, 212));
        gridLayout_3 = new QGridLayout(pageSellCar);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelFactory = new QLabel(pageSellCar);
        labelFactory->setObjectName(QStringLiteral("labelFactory"));

        horizontalLayout_2->addWidget(labelFactory);

        comboBoxFactory = new QComboBox(pageSellCar);
        comboBoxFactory->setObjectName(QStringLiteral("comboBoxFactory"));

        horizontalLayout_2->addWidget(comboBoxFactory);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelBrand = new QLabel(pageSellCar);
        labelBrand->setObjectName(QStringLiteral("labelBrand"));

        horizontalLayout_3->addWidget(labelBrand);

        comboBoxBrand = new QComboBox(pageSellCar);
        comboBoxBrand->setObjectName(QStringLiteral("comboBoxBrand"));

        horizontalLayout_3->addWidget(comboBoxBrand);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelPrice = new QLabel(pageSellCar);
        labelPrice->setObjectName(QStringLiteral("labelPrice"));

        horizontalLayout_4->addWidget(labelPrice);

        lineEditPrice = new QLineEdit(pageSellCar);
        lineEditPrice->setObjectName(QStringLiteral("lineEditPrice"));
        lineEditPrice->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEditPrice);

        labelPriceUnits = new QLabel(pageSellCar);
        labelPriceUnits->setObjectName(QStringLiteral("labelPriceUnits"));

        horizontalLayout_4->addWidget(labelPriceUnits);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelNumber = new QLabel(pageSellCar);
        labelNumber->setObjectName(QStringLiteral("labelNumber"));

        horizontalLayout_5->addWidget(labelNumber);

        spinBoxNumber = new QSpinBox(pageSellCar);
        spinBoxNumber->setObjectName(QStringLiteral("spinBoxNumber"));

        horizontalLayout_5->addWidget(spinBoxNumber);

        labelLastNumber = new QLabel(pageSellCar);
        labelLastNumber->setObjectName(QStringLiteral("labelLastNumber"));

        horizontalLayout_5->addWidget(labelLastNumber);

        labelLast = new QLabel(pageSellCar);
        labelLast->setObjectName(QStringLiteral("labelLast"));

        horizontalLayout_5->addWidget(labelLast);


        gridLayout_3->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelTotal = new QLabel(pageSellCar);
        labelTotal->setObjectName(QStringLiteral("labelTotal"));

        horizontalLayout_6->addWidget(labelTotal);

        lineEditTotal = new QLineEdit(pageSellCar);
        lineEditTotal->setObjectName(QStringLiteral("lineEditTotal"));
        lineEditTotal->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditTotal);

        labelTotalUnits = new QLabel(pageSellCar);
        labelTotalUnits->setObjectName(QStringLiteral("labelTotalUnits"));

        horizontalLayout_6->addWidget(labelTotalUnits);


        gridLayout_3->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        pushButtonSure = new QPushButton(pageSellCar);
        pushButtonSure->setObjectName(QStringLiteral("pushButtonSure"));

        horizontalLayout_7->addWidget(pushButtonSure);

        pushButtonCancel = new QPushButton(pageSellCar);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout_7->addWidget(pushButtonCancel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        gridLayout_3->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        toolBox->addItem(pageSellCar, QString::fromUtf8("\345\207\272\345\224\256\350\275\246\350\276\206"));
        pageNewCar = new QWidget();
        pageNewCar->setObjectName(QStringLiteral("pageNewCar"));
        pageNewCar->setGeometry(QRect(0, 0, 200, 212));
        toolBox->addItem(pageNewCar, QString::fromUtf8("\346\226\260\350\275\246\345\205\245\345\272\223"));
        splitter->addWidget(toolBox);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(200, 0));
        textEdit->setMaximumSize(QSize(500, 16777215));
        textEdit->setReadOnly(true);
        splitter->addWidget(textEdit);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        stackedWidget->addWidget(pageCar);
        pageCalc = new QWidget();
        pageCalc->setObjectName(QStringLiteral("pageCalc"));
        widget = new QWidget(pageCalc);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(19, 59, 291, 221));
        widget_2 = new QWidget(pageCalc);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(329, 59, 271, 221));
        comboBox = new QComboBox(pageCalc);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(150, 10, 69, 22));
        comboBox_2 = new QComboBox(pageCalc);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(470, 10, 69, 22));
        stackedWidget->addWidget(pageCalc);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionCar);
        menu->addAction(actionCalc);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCar->setText(QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\256\241\347\220\206", 0));
        actionCalc->setText(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\273\237\350\256\241", 0));
        labelTitle->setText(QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\256\241\347\220\206", 0));
        labelFactory->setText(QApplication::translate("MainWindow", "\345\216\202\345\256\266\357\274\232", 0));
        labelBrand->setText(QApplication::translate("MainWindow", "\345\223\201\347\211\214\357\274\232", 0));
        labelPrice->setText(QApplication::translate("MainWindow", "\346\212\245\344\273\267\357\274\232", 0));
        labelPriceUnits->setText(QApplication::translate("MainWindow", "\344\270\207", 0));
        labelNumber->setText(QApplication::translate("MainWindow", "\346\225\260\351\207\217\357\274\232", 0));
        labelLastNumber->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\346\225\260\351\207\217\357\274\232", 0));
        labelLast->setText(QApplication::translate("MainWindow", "20", 0));
        labelTotal->setText(QApplication::translate("MainWindow", "\351\207\221\351\242\235\357\274\232", 0));
        labelTotalUnits->setText(QApplication::translate("MainWindow", "\344\270\207", 0));
        pushButtonSure->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0));
        pushButtonCancel->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0));
        toolBox->setItemText(toolBox->indexOf(pageSellCar), QApplication::translate("MainWindow", "\345\207\272\345\224\256\350\275\246\350\276\206", 0));
        toolBox->setItemText(toolBox->indexOf(pageNewCar), QApplication::translate("MainWindow", "\346\226\260\350\275\246\345\205\245\345\272\223", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\256\241\347\220\206", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
