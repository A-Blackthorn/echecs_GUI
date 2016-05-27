#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T21:52:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = echecs_GUI
TEMPLATE = app

win32:RC_ICONS += chess.ico

SOURCES += main.cpp\
        echequier.cpp \
    joueur.cpp

HEADERS  += echequier.h \
    joueur.h

FORMS    += echequier.ui

RESOURCES += \
    pieces.qrc

