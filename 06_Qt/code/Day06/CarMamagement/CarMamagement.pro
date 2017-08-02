#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T17:20:18
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarMamagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domxml.cpp

HEADERS  += mainwindow.h \
    domxml.h

FORMS    += mainwindow.ui
