#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

#include <QWidget>
#include <QVector>
#include <QDir>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include "userInterface/MPushButton.h"
#include "userInterface/MediaFileWidgetList.h"
#include "userInterface/MediaFileUploadWidgetList.h"
#include "core/Uploader.h"
#include "core/Session.h"

namespace userInterface
{
    class FileUploader : public QWidget
    {
        Q_OBJECT

    private:
        MediaFileWidgetList* selectedMediaList;
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

    public:
        explicit FileUploader( QWidget *parent = 0);
        ~FileUploader();

    signals:

    private slots:
        void clearButtonPressed();
        void stopUploadButtonPressed();
        void browseButtonPressed();
        void uploadButtonPressed();
        void uploadProgress( int percent, core::MediaFile* media );
        void uploadFinished( QString error );
    };
}

#endif // FILEUPLOADER_H
