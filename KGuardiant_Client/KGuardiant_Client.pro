#-------------------------------------------------
#
# Project created by QtCreator 2014-07-12T12:05:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KGuardiant_Client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp

HEADERS  += client.h

FORMS    += client.ui

OTHER_FILES += \
    client.ini
