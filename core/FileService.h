#ifndef FILESERVICE_H
#define FILESERVICE_H

#include "ServiceConnection.h"
#include <QStringList>

namespace core
{
    enum FileType { MUSIC = 1, MOVIE, IMAGE };

    class FileService : public ServiceConnection
    {
        Q_OBJECT

    private:
        FileType type;
        QStringList* filelist;
        virtual void processService( QTcpSocket* server );

    public:
        FileService(FileType type, QString serverAddr, QString serverPort, QString username, QString sessionID);
        ~FileService();

    signals:
        void finish ( QStringList* fileList, QString response );

    };
}

#endif // FILESERVICE_H
