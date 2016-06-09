#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T12:46:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labyrinth-v2
TEMPLATE = app
CONFIG += c++11 c++14

SOURCES += main.cpp\
        window.cpp \
    labyrinth.cpp \
    generatorlabyrinth.cpp \
    persistlabyrinth.cpp \
    qgraphicscellitem.cpp \
    qgraphicslabyrinthitem.cpp \
    cell.cpp \
    dijkstra.cpp

HEADERS  += window.hpp \
    labyrinth.hpp \
    generatorlabyrinth.hpp \
    persistlabyrinth.hpp \
    qgraphicscellitem.hpp \
    qgraphicslabyrinthitem.hpp \
    cell.hpp \
    dijkstra.hpp

FORMS    += window.ui
