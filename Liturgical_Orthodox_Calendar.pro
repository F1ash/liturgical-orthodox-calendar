#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T23:23:54
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Liturgical_Orthodox_Calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingswidget.cpp \
    toolbar.cpp \
    addbookmarkdialog.cpp \
    data.cpp \
    statusbar.cpp \
    networkstuff.cpp \
    traywidget.cpp \
    calendarwidget.cpp

HEADERS  += mainwindow.h \
    settingswidget.h \
    toolbar.h \
    addbookmarkdialog.h \
    statusbar.h \
    networkstuff.h \
    traywidget.h \
    calendarwidget.h

