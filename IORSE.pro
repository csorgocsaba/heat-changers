#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T20:42:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IORSE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    input.cpp \
    stream.cpp \
    shiftedtemperature.cpp \
    problemtable.cpp \
    heatcascade.cpp \
    results.cpp \
    design.cpp \
    deltat.cpp

HEADERS  += mainwindow.h \
    input.h \
    stream.h \
    shiftedtemperature.h \
    problemtable.h \
    heatcascade.h \
    results.h \
    design.h \
    deltat.h

FORMS    += mainwindow.ui \
    input.ui \
    shiftedtemperature.ui \
    problemtable.ui \
    heatcascade.ui \
    results.ui \
    design.ui \
    deltat.ui
