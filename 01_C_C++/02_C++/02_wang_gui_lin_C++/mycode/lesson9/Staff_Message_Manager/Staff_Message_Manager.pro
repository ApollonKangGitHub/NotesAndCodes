TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    employee.cpp \
    techincian.cpp \
    manager.cpp \
    saleman.cpp \
    salemanager.cpp

HEADERS += \
    employee.h \
    techincian.h \
    manager.h \
    saleman.h \
    salemanager.h

