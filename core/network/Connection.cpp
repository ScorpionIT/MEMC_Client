#include "Connection.h"

using namespace core;
using namespace network;

const unsigned long Connection::SESSION_TIMER = 10000;

Connection::Connection(QString serverAddr, QString username, QString password)
{
    QString port = "80000";
    this->lastError = "";
    this->server = new QTcpSocket( this );
    this->server->connectToHost( serverAddr, port.toInt());
    if ( this->server->waitForConnected( Connection::SESSION_TIMER ) )
    {
        QString response;
        this->server->waitForReadyRead( Connection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );

        this->server->write( QString (username + "\n").toUtf8() );
        this->server->waitForBytesWritten( -1 );

        this->server->waitForReadyRead( Connection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );
        if (response == "pls pw")
        {
            this->server->write( QString (password + "\n").toUtf8() );
            this->server->waitForBytesWritten( -1 );

            this->server->waitForReadyRead( Connection::SESSION_TIMER );
            response = this->server->readLine();
            response.chop( 1 );
            if (response == "ok")
            {
                if (this->server->bytesAvailable() == 0)
                    this->server->waitForReadyRead( Connection::SESSION_TIMER );
                response = this->server->readLine();
                response.chop( 1 );
                if (response.split( "=" )[0] == "s.id")
                {
                    QString sessionID = response.split( "=" )[1];
                    if (this->server->bytesAvailable() == 0)
                        this->server->waitForReadyRead( Connection::SESSION_TIMER );
                    response = this->server->readLine();
                    response.chop( 1 );

                    // TO DO
                    Session* session = Session::getSession();
                    session->setSession(serverAddr, username, sessionID);
                    session->setServicePort(80002, 80001, 80008, 0);
                    // TO DO

                    connect ( this->server, SIGNAL( readyRead() ), this, SLOT ( procesMessage() ) );
                    connect (this->server, SIGNAL( disconnected() ), this, SLOT( closeConnection() ) );
                    procesMessage();
                }
                else
                    this->lastError = "comunication error (no session id recived)";
            }
            else
                this->lastError = "wrong password";
        }
        else
        {
            this->lastError = "wrong user";
        }
    }
    else
        this->lastError = "Connection timeout";
}

Connection::~Connection()
{
    this->server->close();
    delete this->server;
}

QString Connection::getLastError()
{
    return this->lastError;
}

void Connection::procesMessage()
{
    while (this->server->bytesAvailable() > 0)
    {
        QString message;
        message = this->server->readLine();
        message.chop ( 1 );
        if ( message == "are you there?" )
        {
            this->server->write ("yes\n");
            this->server->waitForBytesWritten( -1 );
        }
    }
}

void Connection::closeConnection()
{
    qDebug() << "Connection closed";
    emit connectionClosed();
}


