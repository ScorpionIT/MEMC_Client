QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEMC_Client
TEMPLATE = app


SOURCES += main.cpp\
    core/Connection.cpp \
    core/Fileservice.cpp \
    core/ServiceConnection.cpp \
    core/Uploader.cpp \
    userInterface/FileUploader.cpp \
    userInterface/Library.cpp \
    userInterface/Login.cpp \
    userInterface/MainWindow.cpp \
    userInterface/MPushButton.cpp \
    userInterface/MusicMediaInfo.cpp

HEADERS  += \
    core/Connection.h \
    core/FileService.h \
    core/ServiceConnection.h \
    core/Uploader.h \
    userInterface/FileUploader.h \
    userInterface/Library.h \
    userInterface/Login.h \
    userInterface/MainWindow.h \
    userInterface/MPushButton.h \
    userInterface/MusicMediaInfo.h
