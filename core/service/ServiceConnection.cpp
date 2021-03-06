#include "ServiceConnection.h"

using namespace core;
using namespace service;

const unsigned long ServiceConnection::SESSION_TIMER = 10000;

ServiceConnection::ServiceConnection() : QThread ()
{
    this->session = network::Session::getSession();
    this->serverPort = -1;
}

ServiceConnection::~ServiceConnection()
{
    this->server->close();
    delete this->server;
}

void ServiceConnection::setPort (int serverPort )
{
    this->serverPort = serverPort;
}

void ServiceConnection::run()
{
    this->lastError = "";
    this->server = new QTcpSocket();
    this->server->connectToHost( this->session->getServerAddress(), this->serverPort );
    if ( this->server->waitForConnected( ServiceConnection::SESSION_TIMER ) )
    {
        QString response;
        if ( server->bytesAvailable() == 0 )
            this->server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        response = this->server->readLine();
        response.chop( 1 );

        this->server->write( QString (this->session->getUsername() + " " + this->session->getID() + "\n").toUtf8() );
        this->server->waitForBytesWritten( -1 );

        if ( server->bytesAvailable() == 0 )
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
