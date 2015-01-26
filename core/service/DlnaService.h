#ifndef DLNASERVICE_H
#define DLNASERVICE_H

#include "core/service/ServiceConnection.h"
#include "core/network/Session.h"
#include "core/media/MediaFile.h"

namespace core
{
    namespace service
    {
        enum DLNAOperation {NEWSHARE = 1, SHARESTATUS };

        class DlnaService : public ServiceConnection
        {
            Q_OBJECT

        private:
            DLNAOperation operation;
            QList<media::MediaFile*> mediaList;
            virtual void processService( QTcpSocket* server );

        public:
            DlnaService( QList<media::MediaFile*> mediaList, DLNAOperation operation );
            ~DlnaService();

        signals:
            void shareStatus (QList<core::media::MediaFile *>*);
            void finish (QString message);

        };
    }
}

#endif // DLNASERVICE_H
