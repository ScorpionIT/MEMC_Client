#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include "mpushbutton.h"

class FileUploader : public QWidget
{
    Q_OBJECT

private:
    QListWidget* selectedFile;
    QProgressBar* progressBar;
    MPushButton* cleanButton;
    MPushButton* browseButton;
    MPushButton* uploadButton;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* vLayout;

public:
    explicit FileUploader(QWidget *parent = 0);
    ~FileUploader();

signals:

private slots:
    void browseButtonPressed();
    void uploadButtonPressed();
};

#endif // FILEUPLOADER_H
