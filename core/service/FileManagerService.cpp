#include "FileManagerService.h"

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
        else if (message == "what do I have to do?[DELETE_FILE=1, CHANGE_SCOPE=2, FINISH=3]")
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
            server->write( "3\n" );
            server->waitForBytesWritten( -1 );
            end = true;
        }
    }
}
