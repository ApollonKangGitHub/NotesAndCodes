#-------------------------------------------------
#
# Project created by QtCreator 2017-06-11T15:12:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 01_QThread
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mythread.cpp

HEADERS  += widget.h \
    mythread.h

FORMS    += widget.ui
