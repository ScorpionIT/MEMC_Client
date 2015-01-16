#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

#include <QWidget>
#include <QVector>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include "userInterface/MPushButton.h"
#include "userInterface/MediaFileWidgetList.h"
#include "userInterface/MediaFileUploadWidgetList.h"
#include "userInterface/IconLoader.h"
#include "core/service/UploaderService.h"
#include "core/network/Session.h"

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
        core::service::UploaderService* uploader;
        QVector<QFileInfo>* selectdFile;

    public:
        FileUploader( QWidget *parent = 0);
        ~FileUploader();

    signals:

    private slots:
        void clearButtonPressed();
        void stopUploadButtonPressed();
        void browseButtonPressed();
        void uploadButtonPressed();
        void uploadProgress( int percent, core::media::MediaFile* media );
        void uploadFinished( QString error );
    };
}

#endif // FILEUPLOADER_H
