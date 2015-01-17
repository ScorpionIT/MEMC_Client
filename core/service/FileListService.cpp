#include "FileListService.h"

using namespace core;
using namespace service;

FileListService::FileListService( media::MediaType type ) : ServiceConnection()
{
    network::Session* session = network::Session::getSession();
    this->type = type;
    this->mediaList = new QList<media::MediaFile*>;
    this->setPort( session->getFileListPort() );
}

FileListService::~FileListService()
{
    delete this->mediaList;
}

void FileListService::processService(QTcpSocket *server)
{
    QString message;
    bool end = false;
    while ( !end )
    {
        if ( server->bytesAvailable() == 0 )
            server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        message = server->readLine();
        message.chop( 1 );
        if ( message.isEmpty() )
        {
            end = true;
        }
        else if (message == "? [MUSIC=1, VIDEOS=2, IMAGES=3]")
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
            emit this->finish( this->mediaList, message );
            end = true;
        }
        else
        {
            this->mediaList->append( new media::MediaFile ( message, type ) );
        }
    }
}

