#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T20:26:02
#
#-------------------------------------------------

QMAKE_MAC_SDK = macosx10.12
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_tutarial3
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    hex.cpp \
    hex_board.cpp \
    button.cpp

HEADERS  += \
    game.h \
    hex.h \
    hex_board.h \
    button.h \
    player_type.h

FORMS    +=
