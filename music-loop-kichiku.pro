#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T14:26:12
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets

TARGET = music-loop-kichiku
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

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv aubio

macx {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        aubiobeat.cpp \
        utils.cpp \
        loopplayer.cpp

HEADERS += \
        mainwindow.h \
        aubiobeat.h \
        utils.h \
        loopplayer.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
