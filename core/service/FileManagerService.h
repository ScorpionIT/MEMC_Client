#ifndef FILEMANAGERSERVICE_H
#define FILEMANAGERSERVICE_H

#include "core/service/ServiceConnection.h"
#include "core/media/MediaFile.h"

namespace core
{
    namespace service
    {
        enum Operation {DELETE = 1, LOCK, UNLOCK };

        class FileManagerService : public ServiceConnection
        {
            Q_OBJECT

        private:
            Operation operation;
            QList<media::MediaFile*> mediaList;
            virtual void processService( QTcpSocket* server );

        public:
            FileManagerService( QList<media::MediaFile*> mediaList, Operation operation);
            ~FileManagerService();

        signals:
            void finish ( QString response );

        };
    }
}

#endif // FILEMANAGERSERVICE_H
