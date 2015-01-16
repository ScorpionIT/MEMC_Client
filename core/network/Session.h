#ifndef SESSION_H
#define SESSION_H

#include <QString>

namespace core
{
    namespace network
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
            int fileListPort;
            int fileManagerPort;
            int DlnaManagerPort;

            void setSession ( QString ServerAddress, QString username, QString sessionID );
            void setServicePort (int fileTransfertPort, int fileListPort, int fileManagerPort, int DlnaManagerPort );

        public:
            static Session* getSession();
            QString getServerAddress();
            QString getUsername();
            QString getID();
            int getFileTransferPort();
            int getFileListPort();
            int getFileManagerPort();
            int getDlnaManagerPort();

        };
    }
}

#endif // SESSION_H
