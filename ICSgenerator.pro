#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T15:50:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICSgenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formevent.cpp \
    formrecurrence.cpp

HEADERS  += mainwindow.h \
    formevent.h \
    formrecurrence.h

FORMS    += mainwindow.ui \
    formevent.ui \
    formrecurrence.ui

TRANSLATIONS = ICS_DE.ts
