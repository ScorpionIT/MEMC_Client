#include "FileManagerService.h"
#include <QDebug>

using namespace core;
using namespace service;

FileManagerService::FileManagerService(QList<media::MediaFile *> mediaList, Operation operation ) : ServiceConnection()
{
    this->mediaList = mediaList;
    this->operation = operation;
    network::Session* session = network::Session::getSession();
    this->setPort( session->getFileManagerPort() );
}

FileManagerService::~FileManagerService()
{

}

void FileManagerService::processService(QTcpSocket *server)
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
        else if ( message == "files[END to stop]" )
        {
            for ( QList<media::MediaFile *>::iterator i = this->mediaList.begin(); i != this->mediaList.end(); i++ )
            {
                server->write( (*i)->getFullName().toUtf8()+"\n" );
                server->waitForBytesWritten( -1 );
            }

            server->write( "END\n" );
            server->waitForBytesWritten( -1 );
        }
        else if (message == "[MUSIC=1, VIDEO=2, IMAGE=3]")
        {
            server->write( QString ( QString::number( this->mediaList.first()->getType() ) + "\n" ).toUtf8() );
            server->waitForBytesWritten( -1 );
        }
        else if (message == "what do I have to do?[DELETE_FILE=1, LOCK_FILE=2, UNLOCK_FILE=3, FINISH=4]")
        {
            server->write( QString ( QString::number( this->operation ) + "\n" ).toUtf8() );
            server->waitForBytesWritten( -1 );
        }
        else if ( message.contains( "Server error: " ) )
        {
            emit this->finish( message );
            end = true;
        }
        else if ( message == "Done" )
        {
            emit this->finish( message );
            if (this->operation == Operation::DELETE)
                server->write( "3\n" );
            else
                server->write( "4\n" );

            server->waitForBytesWritten( -1 );
            end = true;
        }
    }
}
