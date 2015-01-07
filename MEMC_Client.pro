QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEMC_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    connection.cpp \
    fileuploader.cpp \
    mpushbutton.cpp \
    library.cpp \
    serviceconnection.cpp

HEADERS  += mainwindow.h \
    login.h \
    connection.h \
    fileuploader.h \
    mpushbutton.h \
    library.h \
    serviceconnection.h
