#-------------------------------------------------
#
# Project created by QtCreator 2017-06-21T16:24:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 03_QThreadImage
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mythread.cpp

HEADERS  += widget.h \
    mythread.h

FORMS    += widget.ui
