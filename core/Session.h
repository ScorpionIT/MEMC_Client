#ifndef SESSION_H
#define SESSION_H

#include <QString>

namespace core
{
    class Session
    {

    friend class Connection;

    private:
        static Session* currentSession;
        Session();
        ~Session();
        QString serverAddress;
        QString username;
        QString sessionID;
        int fileTransferPort;
        int fileManagerPort;
        int fileListPort;
        int DlnaManagerPort;

        void setSession ( QString ServerAddress, QString username, QString sessionID );
        void setServicePort (int fileTransferPort, int fileManagerPort, int fileListPort, int DlnaManagerPort );

    public:
        static Session* getSession();
        QString getServerAddress();
        QString getUsername();
        QString getID();
        int getFileTransfertPort();
        int getManagerTransfertPort();
        int getFileListPort();
        int getDlnaManagerPort();

    };
}

#endif // SESSION_H
