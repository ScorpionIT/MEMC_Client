#include "Session.h"

using namespace core;
using namespace network;

Session* Session::currentSession = nullptr;

Session::Session()
{
    this->spaceAvaiable = 10;
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

void Session::setServicePort(int fileTransfertPort, int fileListPort, int fileManagerPort, int DlnaManagerPort)
{
    this->fileTransferPort = fileTransfertPort;
    this->fileListPort = fileListPort;
    this->fileManagerPort = fileManagerPort;
    this->DlnaManagerPort = DlnaManagerPort;
}

Session *Session::getSession()
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

int Session::getFileTransferPort()
{
    return this->fileTransferPort;
}

int Session::getFileListPort()
{
    return this->fileListPort;
}

int Session::getFileManagerPort()
{
    return this->fileManagerPort;
}

int Session::getDlnaManagerPort()
{
    return this->DlnaManagerPort;
}

int Session::getAvaiableSpace()
{
    return this->spaceAvaiable;
}
