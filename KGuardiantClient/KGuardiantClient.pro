#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T18:21:01
#
#-------------------------------------------------
include(qtOpencv/QtOpenCV.pri)
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KGuardiantClient
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

SOURCES += main.cpp\
        kguardiantclient.cpp \
    conectardialog.cpp \
    aboutdialog.cpp \
    customtab.cpp \
    roiselectordlg.cpp \
    addroidlg.cpp \
    logger.cpp \
    configuracion.cpp \
    clickablelabel.cpp \
    stationdefinition.cpp \
    roidefinition.cpp

HEADERS  += kguardiantclient.h \
    conectardialog.h \
    aboutdialog.h \
    customtab.h \
    roiselectordlg.h \
    addroidlg.h \
    logger.h \
    configuracion.h \
    clickablelabel.h \
    stationdefinition.h \
    roidefinition.h

FORMS    += kguardiantclient.ui \
    conectardialog.ui \
    aboutdialog.ui \
    customtab.ui \
    roiselectordlg.ui \
    addroidlg.ui

OTHER_FILES += \
    client.ini
