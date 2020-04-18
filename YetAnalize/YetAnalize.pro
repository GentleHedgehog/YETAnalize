#-------------------------------------------------
#
# Project created by QtCreator 2019-02-10T13:57:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YetAnalize
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    yetanalizer.cpp

HEADERS  += mainwindow.h \
    yetanalizer.h \
    yetfiller.h \
    yetfiller.h

FORMS    += mainwindow.ui

RESOURCES += \
    rsc.qrc \


TRANSLATIONS += QtLanguage_ru.ts
CODECFORSRC     = UTF-8

#DEFINES += LANG_EN
