QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEMC_Client
TEMPLATE = app


SOURCES += main.cpp\
    ui/library.cpp \
    ui/login.cpp \
    ui/mainwindow.cpp \
    ui/mpushbutton.cpp \
    core/connection.cpp \
    core/fileservice.cpp \
    core/serviceconnection.cpp \
    ui/fileuploader.cpp \
    ui/musicmediainfo.cpp \
    core/uploader.cpp

HEADERS  += ui/library.h \
    ui/login.h \
    ui/mainwindow.h \
    ui/mpushbutton.h \
    core/connection.h \
    core/fileservice.h \
    core/serviceconnection.h \
    ui/fileuploader.h \
    ui/musicmediainfo.h \
    core/uploader.h
