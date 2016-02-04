#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T17:38:34
#
#-------------------------------------------------

QT       -= core gui

TARGET = dht22
TEMPLATE = lib
CONFIG += c++11

DEFINES += DHT22_LIBRARY

SOURCES += piio.cpp \
           dht22.cpp


HEADERS += piio.h \
           dht22.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
