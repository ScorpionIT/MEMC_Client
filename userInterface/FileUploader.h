#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

#include <QWidget>
#include <QVector>
#include <QDir>
#include <QFileInfo>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include "userInterface/MPushButton.h"
#include "core/Uploader.h"
#include "core/Connection.h"

namespace userInterface
{
    class FileUploader : public QWidget
    {
        Q_OBJECT

    private:
        QListWidget* selectedFileList;
        QProgressBar* progressBar;
        MPushButton* cleanButton;
        MPushButton* browseButton;
        MPushButton* uploadButton;
        QPushButton* stopUploadButton;
        QHBoxLayout* buttonLayout;
        QHBoxLayout* progressLayout;
        QVBoxLayout* vLayout;
        core::Uploader* uploader;
        QVector<QFileInfo>* selectdFile;
        core::Connection* connection;

    public:
        explicit FileUploader(core::Connection* conn, QWidget *parent = 0);
        ~FileUploader();

    signals:

    private slots:
        void clearButtonPressed();
        void stopUploadButtonPressed();
        void browseButtonPressed();
        void uploadButtonPressed();
        void uploadProgress( int percent, QString fileName );
        void uploadFinished( QString error );
    };
}

#endif // FILEUPLOADER_H
