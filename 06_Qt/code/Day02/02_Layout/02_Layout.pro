#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T17:47:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 02_Layout
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smallwidget.cpp

HEADERS  += mainwindow.h \
    smallwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
CONFIG += C++11
