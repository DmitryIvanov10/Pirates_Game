#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T21:42:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp \
    player.cpp \
    ship.cpp \
    npc.cpp \
    voronoi_point.cpp \
    city.cpp \
    wind.cpp \
    game.cpp \
    newgame.cpp \
    island.cpp \
    pirate.cpp \
    voronoi_points.cpp

HEADERS  += \
    player.h \
    ship.h \
    npc.h \
    voronoi_point.h \
    city.h \
    wind.h \
    game.h \
    newgame.h \
    island.h \
    pirate.h \
    voronoi_points.h

FORMS    +=

RESOURCES += \
    resources.qrc \
    img/Islands/islands.qrc \
    img/Islands/islands2.qrc \
    img/Islands/islands4.qrc
