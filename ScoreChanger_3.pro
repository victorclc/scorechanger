#-------------------------------------------------
#
# Project created by QtCreator 2014-06-01T20:53:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScoreChanger_3
TEMPLATE = app


SOURCES += main.cpp\
        scorechanger.cpp \
    popout.cpp \
    dialog.cpp

HEADERS  += scorechanger.h \
    popout.h \
    dialog.h

FORMS    += scorechanger.ui \
    popout.ui \
    dialog.ui
