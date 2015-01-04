QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEMC_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    connection.cpp

HEADERS  += mainwindow.h \
    login.h \
    connection.h
