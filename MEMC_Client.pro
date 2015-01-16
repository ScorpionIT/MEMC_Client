QT += core gui widgets network
CONFIG += c++11

TARGET = MEMC_Client

HEADERS += \
    core/media/MediaFile.h \
    core/media/MediaInfo.h \
    core/network/Connection.h \
    core/network/Session.h \
    core/service/ServiceConnection.h \
    userInterface/FileUploader.h \
    userInterface/Library.h \
    userInterface/Login.h \
    userInterface/MainWindow.h \
    userInterface/MediaFileUploadWidgetList.h \
    userInterface/MediaFileWidgetList.h \
    userInterface/MediaInfoView.h \
    userInterface/MPushButton.h \
    userInterface/MusicMediaInfo.h \
    core/media/MovieMediaInfo.h \
    userInterface/MToolPushButton.h \
    userInterface/IconLoader.h \
    core/service/UploaderService.h \
    core/service/FileListService.h \
    core/service/FileManagerService.h

SOURCES += \
    core/media/MediaFile.cpp \
    core/media/MediaInfo.cpp \
    core/network/Connection.cpp \
    core/network/Session.cpp \
    core/service/ServiceConnection.cpp \
    userInterface/FileUploader.cpp \
    userInterface/Library.cpp \
    userInterface/Login.cpp \
    userInterface/MainWindow.cpp \
    userInterface/MediaFileUploadWidgetList.cpp \
    userInterface/MediaFileWidgetList.cpp \
    userInterface/MPushButton.cpp \
    userInterface/MusicMediaInfo.cpp \
    main.cpp \
    core/media/MovieMediaInfo.cpp \
    userInterface/MToolPushButton.cpp \
    userInterface/IconLoader.cpp \
    core/service/UploaderService.cpp \
    core/service/FileListService.cpp \
    core/service/FileManagerService.cpp

