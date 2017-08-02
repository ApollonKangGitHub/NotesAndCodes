TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    student.cpp \
    graduate.cpp \
    doctor.cpp \
    birthday.cpp

HEADERS += \
    student.h \
    graduate.h \
    doctor.h \
    birthday.h

