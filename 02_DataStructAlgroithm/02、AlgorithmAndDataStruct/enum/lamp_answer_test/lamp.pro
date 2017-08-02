#-------------------------------------------------
#
# Project created by QtCreator 2017-07-30T14:15:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lamp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    bitoper.cpp

HEADERS  += widget.h \
    bitoper.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc
