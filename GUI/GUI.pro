#-------------------------------------------------
#
# Project created by QtCreator 2014-12-05T14:44:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagewidget.cpp \
    exportdialog.cpp \
    rundialog.cpp

HEADERS  += mainwindow.h \
    imagewidget.h \
    exportdialog.h \
    rundialog.h

FORMS    += mainwindow.ui \
    exportdialog.ui \
    rundialog.ui
