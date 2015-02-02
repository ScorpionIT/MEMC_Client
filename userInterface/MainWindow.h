#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "userInterface/Login.h"
#include "userInterface/Library.h"
#include "userInterface/FileUploader.h"
#include "userInterface/DlnaManager.h"
#include "userInterface/MediaPlayerWidget.h"
#include "userInterface/MToolPushButton.h"
#include "userInterface/IconLoader.h"
#include "userInterface/UserInfo.h"
#include "userInterface/Spacer.h"

namespace userInterface
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        QToolBar* toolBar;
        MToolPushButton* libraryButton;
        MToolPushButton* uploadButton;
        MToolPushButton* settingsButton;
        MToolPushButton* dlnaButton;
        MToolPushButton* mediaPlayerButton;
        Library* library;
        FileUploader* fileUploader;
        DlnaManager* dlnaManager;
        MediaPlayerWidget* mediaPlayer;
        UserInfo* userInfo;

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void configureToolBar();

    private slots:
        void newConnection();
        void libraryButtonPressed();
        void uploadButtonPressed();
        void settingsButtonPressed();
        void dlnaButtonPressed();
        void mediaPlayerButtonPressed();
    };
}

#endif // MAINWINDOW_H
