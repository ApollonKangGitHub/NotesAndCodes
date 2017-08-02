#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T13:43:47
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 01_TCP
TEMPLATE = app


SOURCES += main.cpp\
        serverwidget.cpp \
    clientwidget.cpp

HEADERS  += serverwidget.h \
    clientwidget.h

FORMS    += serverwidget.ui \
    clientwidget.ui
CONFIG += C++11
