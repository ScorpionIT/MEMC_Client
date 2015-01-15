#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QStringList>
#include "core/ServiceConnection.h"
#include "core/MediaFile.h"
#include "core/Session.h"

namespace core
{
    class FileService : public ServiceConnection
    {
        Q_OBJECT

    private:
        MediaType type;
        QList<MediaFile*>* mediaList;
        virtual void processService( QTcpSocket* server );

    public:
        FileService(MediaType type);
        ~FileService();

    signals:
        void finish ( QList<core::MediaFile*>*, QString response );

    };
}

#endif // FILESERVICE_H
