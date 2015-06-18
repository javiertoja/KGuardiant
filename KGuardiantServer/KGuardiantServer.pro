#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T12:54:03
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = KGuardiantServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    configuracion.cpp \
    logger.cpp \
    devicemgr.cpp \
    movementdetector.cpp \
    console.cpp \
    tcpserver.cpp \
    tcpconnection.cpp \
    kguardiantserver.cpp \
    basedetector.cpp

HEADERS += \
    configuracion.h \
    logger.h \
    devicemgr.h \
    movementdetector.h \
    console.h \
    tcpserver.h \
    tcpconnection.h \
    kguardiantserver.h \
    basedetector.h

OTHER_FILES += \
    server.ini

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv


unix: PKGCONFIG += libopenni
