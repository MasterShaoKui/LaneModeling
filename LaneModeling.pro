#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T18:34:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaneModeling
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    lanemodel.cpp \
    algorithm.cpp \
    loadjsonfile.cpp \
    mark.cpp \
    jigsawlane.cpp \
    controller.cpp \
    laneview.cpp \
    mainwindow.cpp

HEADERS += \
        widget.h \
    lanemodel.h \
    algorithm.h \
    scriptcaller.h \
    mark.h \
    jigsawlane.h \
    controller.h \
    constants.h \
    laneview.h \
    guessbean.h \
    mainwindow.h

FORMS += \
        widget.ui \
    laneview.ui \
    mainwindow.ui

INCLUDEPATH += C:\Users\ezios\AppData\Local\Programs\Python\Python36-32\include
LIBS += C:\Users\ezios\AppData\Local\Programs\Python\Python36-32\libs\python36.lib
