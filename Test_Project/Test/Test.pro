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
    voronoi_points.cpp \
    cargo.cpp \
    view.cpp \
    battle.cpp

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
    voronoi_points.h \
    cargo.h \
    view.h \
    battle.h

FORMS    +=

RESOURCES += \
    resources.qrc \
    img/Islands/islands.qrc \
    img/Islands/islands2.qrc \
    img/Islands/islands4.qrc \
    img/Ships/Brig/brig.qrc \
    img/Ships/Caravel/caravel.qrc \
    img/Interface/Temps/interface_temps.qrc \
    img/Interface/HUD/interface_hud.qrc \
    img/Interface/Bars/Menu/menu_bars.qrc \
    img/Interface/Cargo/cargo.qrc \
    img/Ships/Boat/boat.qrc
