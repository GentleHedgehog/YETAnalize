include(gtest_dependency.pri)

QT += widgets
QT += testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

HEADERS += \
        ..\YetAnalize\yetanalizer.h \
    tst_YetAnalizer.h \
    macros_inc.h \
    test_qt_signals.h

SOURCES += \
        main.cpp \
        ..\YetAnalize\yetanalizer.cpp \
