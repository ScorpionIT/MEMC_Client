#ifndef UPLOADERSERVICE_H
#define UPLOADERSERVICE_H

#include <QFileInfo>
#include <QVector>
#include "core/service/ServiceConnection.h"
#include "core/media/MediaFile.h"

namespace core
{
    namespace service
    {
        class UploaderService : public ServiceConnection
        {
            Q_OBJECT

        private:
            QList<media::MediaFile*> toUpload;
            bool stopUploadProcess;

        protected:
            virtual void processService(QTcpSocket* server);

        public:
            UploaderService(QList<media::MediaFile*> mediaFiles);
            ~UploaderService();
            void stopUpload();

        signals:
            void progress(int percent, core::media::MediaFile* mediaFile);
            void finish ( QString status );

        };
    }
}

#endif // UPLOADERSERVICE_H
