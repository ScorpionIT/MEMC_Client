#include "Session.h"

using namespace core;

Session* Session::currentSession = nullptr;

Session::Session()
{

}

Session::~Session()
{
    this->currentSession = nullptr;
}

void Session::setSession(QString serverAddress, QString username, QString sessionID)
{
    this->serverAddress = serverAddress;
    this->username = username;
    this->sessionID = sessionID;
}

void Session::setServicePort(int fileTransferPort, int fileManagerPort, int fileListPort, int DlnaManagerPort)
{
    this->fileTransferPort = fileTransferPort;
    this->fileManagerPort = fileManagerPort;
    this->fileListPort = fileListPort;
    this->DlnaManagerPort = DlnaManagerPort;
}

Session *core::Session::getSession()
{
    if ( currentSession == nullptr )
        currentSession = new Session();

    return currentSession;
}

QString Session::getServerAddress()
{
    return this->serverAddress;
}

QString Session::getUsername()
{
    return this->username;
}

QString Session::getID()
{
    return this->sessionID;
}

int Session::getFileTransfertPort()
{
    return this->fileTransferPort;
}

int Session::getManagerTransfertPort()
{
    return this->fileManagerPort;
}

int Session::getFileListPort()
{
    return this->fileListPort;
}

int Session::getDlnaManagerPort()
{
    return this->DlnaManagerPort;
}
