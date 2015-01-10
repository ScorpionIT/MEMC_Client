#include "connection.h"

const unsigned long Connection::SESSION_TIMER = 10000;

Connection::Connection(QString serverAddr, QString username, QString password)
{
    this->lastError = "";
    this->server = new QTcpSocket( this );
    this->server->connectToHost( serverAddr, 80000);
    if ( this->server->waitForConnected( Connection::SESSION_TIMER ) )
    {
        QString response;
        this->server->waitForReadyRead( Connection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );
        //qDebug() << response;

        this->server->write( QString (username + "\n").toUtf8() );
        this->server->waitForBytesWritten( -1 );

        this->server->waitForReadyRead( Connection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );
        //qDebug() << response;
        if (response == "pls pw")
        {
            this->server->write( QString (password + "\n").toUtf8() );
            this->server->waitForBytesWritten( -1 );

            this->server->waitForReadyRead( Connection::SESSION_TIMER );
            response = this->server->readLine();
            response.chop( 1 );
            //qDebug() << response;
            if (response == "ok")
            {
                if (this->server->bytesAvailable() == 0)
                    this->server->waitForReadyRead( Connection::SESSION_TIMER );
                response = this->server->readLine();
                response.chop( 1 );
                //qDebug() << response;
                if (response.split( "=" )[0] == "s.id")
                {
                    this->sessionID = response.split( "=" )[1];
                    if (this->server->bytesAvailable() == 0)
                        this->server->waitForReadyRead( Connection::SESSION_TIMER );
                    response = this->server->readLine();
                    response.chop( 1 );
                    //qDebug() << response;
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

QString Connection::getSessionID()
{
    return this->sessionID;
}

void Connection::procesMessage()
{
    while (this->server->bytesAvailable() > 0)
    {
        QString message;
        message = this->server->readLine();
        message.chop ( 1 );
        //qDebug() << message;
        if ( message == "are you there?" )
        {
            this->server->write ("no\n");
            this->server->waitForBytesWritten( -1 );
        }
    }
}

void Connection::closeConnection()
{
    qDebug() << "Connection closed";
    emit connectionClosed();
}


