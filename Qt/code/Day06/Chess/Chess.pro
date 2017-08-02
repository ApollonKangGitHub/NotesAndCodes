#-------------------------------------------------
#
# Project created by QtCreator 2017-06-25T10:00:28
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia  #用于音频的播放
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc
CONFIG += c++11
