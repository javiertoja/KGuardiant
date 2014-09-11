#-------------------------------------------------
#
# Project created by QtCreator 2014-07-12T12:05:15
#
#-------------------------------------------------
include(qtOpencv/QtOpenCV.pri)

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KGuardiant_Client
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
LIBS += -lcvblob

SOURCES += main.cpp\
        client.cpp \
    ClickableLabel.cpp

HEADERS  += client.h \
    ClickableLabel.h

FORMS    += client.ui

OTHER_FILES += \
    client.ini
