#-------------------------------------------------
#
# Project created by QtCreator 2011-10-13T18:08:44
#
#-------------------------------------------------



TARGET = ParasolidServer
TEMPLATE = app


SOURCES += main.cpp\
          psserver.cpp \
    psclient.cpp \
    debug/moc_psclient.cpp \
    debug/moc_psserver.cpp \
    Session.cpp

HEADERS  +=     psserver.h \
    psclient.h \
    Include/frustrum_ifails.h \
    Include/frustrum_tokens.h \
    Include/kernel_interface.h \
    Include/parasolid_debug.h \
    Include/parasolid_ifails.h \
    Include/parasolid_kernel.h \
    Include/parasolid_tokens.h \
    Include/parasolid_typedefs.h \
    Session.h \
INCLUDEPATH += "D:/ClientServerPar/ParasolidServer/Include"

QT       += widgets network





