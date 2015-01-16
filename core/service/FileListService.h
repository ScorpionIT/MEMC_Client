#ifndef FILELISTSERVICE_H
#define FILELISTSERVICE_H

#include <QStringList>
#include "core/service/ServiceConnection.h"
#include "core/media/MediaFile.h"
#include "core/network/Session.h"

namespace core
{
    namespace service
    {
        class FileListService : public ServiceConnection
        {
            Q_OBJECT

        private:
            media::MediaType type;
            QList<media::MediaFile*>* mediaList;
            virtual void processService( QTcpSocket* server );

        public:
            FileListService(media::MediaType type);
            ~FileListService();

        signals:
            void finish ( QList<core::media::MediaFile*>*, QString response );

        };
    }
}

#endif // FILELISTSERVICE_H
