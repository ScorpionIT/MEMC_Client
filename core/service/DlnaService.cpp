#include "DlnaService.h"

using namespace core;
using namespace service;

DlnaService::DlnaService(QList<media::MediaFile*> mediaList  , DLNAOperation operation)
{
    this->mediaList = mediaList;
    this->operation = operation;
    network::Session* session = network::Session::getSession();
    this->setPort( session->getDlnaManagerPort() );
}

DlnaService::~DlnaService()
{

}

void DlnaService::processService(QTcpSocket *server)
{
    QString message;
    QList<media::MediaFile*> *mediaList = new QList<media::MediaFile*>;
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
            QString message;
            for ( QList<media::MediaFile *>::iterator i = this->mediaList.begin(); i != this->mediaList.end(); i++ )
            {
                if ( (*i)->getType() == core::media::MOVIE )
                    message = "v=";
                else if ( (*i)->getType() == core::media::MUSIC )
                    message = "m=";
                else if ( (*i)->getType() == core::media::IMAGE )
                    message = "i=";
                message += (*i)->getFullName();
                server->write( message.toUtf8()+"\n" );
                server->waitForBytesWritten( -1 );
            }

            server->write( "END\n" );
            server->waitForBytesWritten( -1 );
        }
        else if (message == "[NEWSHARE = 1, SHARESTATUS=2]")
        {
            server->write( QString ( QString::number( this->operation) + "\n" ).toUtf8() );
            server->waitForBytesWritten( -1 );
        }
        else if ( message.contains( "Server error: " ) )
        {
            emit this->finish( message );
            end = true;
        }
        else if ( message == "ok" )
        {
            if ( this->operation == DLNAOperation::SHARESTATUS )
            {
                emit this->shareStatus (mediaList);
                emit this->finish ( "SHARESTATUS_OK");
            }
            else
                emit this->finish( message );
            end = true;
        }
        else if ( message == "not running" )
        {
            if ( this->operation == DLNAOperation::SHARESTATUS )
            {
                emit this->shareStatus (mediaList);
            }
            emit this->finish( message );
            end = true;
        }
        else if ( this->operation == DLNAOperation::SHARESTATUS )
        {
            QStringList tokens = message.split( "=" );
            if ( tokens.count() == 2 )
            {
                if( tokens[0] == "m" )
                    mediaList->append( new media::MediaFile( tokens[1], media::MUSIC, true ) );
                else if( tokens[0] == "v" )
                    mediaList->append( new media::MediaFile( tokens[1], media::MOVIE, true ) );
                else if( tokens[0] == "i" )
                    mediaList->append( new media::MediaFile( tokens[1], media::IMAGE, true ) );
            }
            else
            {
                emit finish ("protocol error");
                end = true;
            }
        }
    }
}
