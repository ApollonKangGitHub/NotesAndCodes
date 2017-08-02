#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T12:01:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 04_Event
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mybutton.cpp \
    mylabel.cpp

HEADERS  += mywidget.h \
    mybutton.h \
    mylabel.h

FORMS    += mywidget.ui
CONFIG += C++11
