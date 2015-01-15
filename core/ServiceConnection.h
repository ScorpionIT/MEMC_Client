#ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <QThread>
#include <QTcpSocket>
#include <QString>
#include "core/Session.h"

namespace core
{
    class ServiceConnection : public QThread
    {
        Q_OBJECT

    private:
        QString lastError;
        QString sessionID;
        QTcpSocket* server;
        Session* session;
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

#endif // SERVICECONNECTION_H
