#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T21:08:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = totoscope
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    videodecomposer.cpp \
    controller.cpp \
    drawingzone.cpp \
    splashgui.cpp \
    newprojectgui.cpp \
    exportgui.cpp \
    project.cpp \
    thumbnail.cpp

HEADERS  += gui.h \
    videodecomposer.h \
    controller.h \
    drawingzone.h \
    splashgui.h \
    newprojectgui.h \
    exportgui.h \
    project.h \
    thumbnail.h

FORMS    += gui.ui
