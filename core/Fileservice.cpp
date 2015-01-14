#include "FileService.h"

using namespace core;

FileService::FileService(FileType type, QString serverAddr, QString serverPort, QString username, QString sessionID )
    : ServiceConnection ( serverAddr, serverPort, username, sessionID )
{
    this->type = type;
    this->filelist = new QStringList();
}

FileService::~FileService()
{
    delete this->filelist;
}

void FileService::processService(QTcpSocket *server)
{
    QString message;
    bool end = false;
    while ( !end )
    {
        server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        message = server->readLine();
        message.chop( 1 );
        if (message == "? [MUSIC=1, VIDEOS=2, IMAGES=3]")
        {
            server->write( QString ( QString::number( type ) + "\n" ).toUtf8() );
            server->waitForBytesWritten( -1 );
        }
        else if ( message == "error" || message == "no files")
        {
            emit this->finish( nullptr, message );
            end = true;
        }
        else if ( message == "end" )
        {
            emit this->finish( this->filelist, message );
            end = true;
        }
        else
        {
            this->filelist->append( message );
        }
    }
}

