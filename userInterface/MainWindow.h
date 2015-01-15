#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "Login.h"
#include "MPushButton.h"
#include "Library.h"
#include "FileUploader.h"

#include "core/Connection.h"
#include "core/FileService.h"

namespace userInterface
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        QToolBar* toolBar;
        MPushButton* libraryButton;
        MPushButton* uploadButton;
        MPushButton* settingsButton;
        Library* library;
        FileUploader* fileUploader;

    public:
        MainWindow(QWidget *parent = 0);
        core::Connection* connection;
        ~MainWindow();
        void configureToolBar();

    private slots:
        void newConnection();
        void libraryButtonPressed();
        void uploadButtonPressed();
        void settingsButtonPressed();
    };
}

#endif // MAINWINDOW_H
