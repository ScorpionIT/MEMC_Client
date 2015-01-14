#include "ServiceConnection.h"

using namespace core;

const unsigned long ServiceConnection::SESSION_TIMER = 10000;

ServiceConnection::ServiceConnection(QString serverAddr, QString serverPort, QString username, QString sessionID) : QThread ()
{
    this->serverAddr = serverAddr;
    this->serverPort = serverPort;
    this->username = username;
    this->sessionID = sessionID;
}

ServiceConnection::~ServiceConnection()
{
    qDebug() << "Service connection closed";
    this->server->close();
    delete this->server;
}

void ServiceConnection::run()
{
    this->lastError = "";
    this->server = new QTcpSocket();
    this->server->connectToHost( this->serverAddr, this->serverPort.toInt() );
    if ( this->server->waitForConnected( ServiceConnection::SESSION_TIMER ) )
    {
        QString response;
        this->server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );

        this->server->write( QString (this->username + " " + this->sessionID + "\n").toUtf8() );
        this->server->waitForBytesWritten( -1 );

        this->server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );

        if (response == "refused")
        {
             qDebug() << "Connection refused";
        }
        else if (response == "ok")
            this->processService( this->server );
    }
    else
        qDebug() <<  "Connection timeout";
}
