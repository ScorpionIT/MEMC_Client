#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "login.h"
#include "mpushbutton.h"
#include "library.h"
#include "fileuploader.h"

#include "core/connection.h"
#include "core/fileservice.h"

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
    Connection* connection;
    ~MainWindow();
    void configureToolBar();

private slots:
    void newConnection( Connection* conn );
    void libraryButtonPressed();
    void uploadButtonPressed();
    void settingsButtonPressed();
};

#endif // MAINWINDOW_H
