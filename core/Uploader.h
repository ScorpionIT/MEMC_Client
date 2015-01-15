#ifndef UPLOADER_H
#define UPLOADER_H

#include <QFileInfo>
#include <QVector>
#include "core/ServiceConnection.h"
#include "core/MediaFile.h"

namespace core
{
    class Uploader : public ServiceConnection
    {
        Q_OBJECT

    private:
        QList<MediaFile*> toUpload;
        bool stopUploadProcess;

    protected:
        virtual void processService(QTcpSocket* server);

    public:
        Uploader(QList<MediaFile*> mediaFiles);
        ~Uploader();
        void stopUpload();

    signals:
        void progress(int percent, core::MediaFile* mediaFile);
        void finish ( QString status );

    };
}

#endif // UPLOADER_H
