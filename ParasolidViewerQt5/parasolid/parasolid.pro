#-------------------------------------------------
#
# Project created by QtCreator 2015-01-06T22:28:32
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parasolid
TEMPLATE = app
INCLUDEPATH += D:/ClientServerPar/ParasolidViewerQt5/Include
LIBS += -LD:/ClientServerPar/ParasolidViewerQt5/Lib
LIBS += -lpskernel


SOURCES += main.cpp\
        mainwindow.cpp\
         Session.cpp\
        glwidget.cpp\
        frustrum.cpp\
        frustrum_delta.cpp
        

HEADERS  += mainwindow.h \
            Session.h\
            glwidget.h\

FORMS    += mainwindow.ui
