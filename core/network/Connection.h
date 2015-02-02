#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <core/network/Session.h>

namespace core
{
    namespace network
    {
        class Connection: public QObject
        {
            Q_OBJECT

        private:
            static const unsigned long SESSION_TIMER;
            QTcpSocket* server;
            QString lastError;

        public:
            Connection(QString serverAddr , QString username, QString password);
            ~Connection();
            QString getLastError();

        private slots:
            void processMessage();
            void closeConnection();

        signals:
            void connectionClosed ();
        };
    }
}

#endif // CONNECTION_H
