#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T21:50:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = marabaraba_cpp
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


LIBS += -lWS2_32

SOURCES += main.cpp \
    pos.cpp \
    cell.cpp \
    checker.cpp \
    board.cpp \
    game.cpp \
    pop_strategy.cpp \
    move_strategy.cpp \
    put_strategy.cpp

HEADERS += \
    pos.h \
    cell.h \
    checker.h \
    board.h \
    game.h \
    pop_strategy.h \
    move_strategy.h \
    put_strategy.h

