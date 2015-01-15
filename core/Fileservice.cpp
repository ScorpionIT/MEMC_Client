#include "FileService.h"

using namespace core;

FileService::FileService( MediaType type ) : ServiceConnection()
{
    Session* session = Session::getSession();
    this->type = type;
    this->mediaList = new QList<MediaFile*>;
    this->setPort( session->getFileListPort() );
}

FileService::~FileService()
{
    delete this->mediaList;
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
            emit this->finish( this->mediaList, message );
            end = true;
        }
        else
        {
            this->mediaList->append( new MediaFile ( message, type ) );
        }
    }
}

