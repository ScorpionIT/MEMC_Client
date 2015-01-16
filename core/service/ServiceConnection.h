#ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <QThread>
#include <QTcpSocket>
#include <QString>
#include "core/network/Session.h"

namespace core
{
    namespace service
    {
        class ServiceConnection : public QThread
        {
            Q_OBJECT

        private:
            QString lastError;
            QString sessionID;
            QTcpSocket* server;
            network::Session* session;
            int serverPort;
            void run();

        protected:
            static const unsigned long SESSION_TIMER;
            void setPort (int serverPort );
            virtual void processService(QTcpSocket* server) = 0;

        public:
            ServiceConnection();
            ~ServiceConnection();
        };
    }
}

#endif // SERVICECONNECTION_H
