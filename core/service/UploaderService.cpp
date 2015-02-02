#include "UploaderService.h"

using namespace core;
using namespace service;

UploaderService::UploaderService(QList<media::MediaFile *> mediaFiles )
    : ServiceConnection ( )
{
    network::Session* session = network::Session::getSession();
    this->setPort( session->getFileTransferPort() );
    this->toUpload = mediaFiles;
    this->stopUploadProcess = false;
}

UploaderService::~UploaderService()
{
}

void UploaderService::stopUpload()
{
    this->stopUploadProcess = true;
}

void UploaderService::processService(QTcpSocket *server)
{
    QString message;
    QString stopCause;
    int mediaNumber = 0;
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
        else if (message == "what do you have for me?[MUSIC=1, VIDEO=2, IMAGES=3, FINISH=4]")
        {
            if ( mediaNumber == this->toUpload.size() || this->stopUploadProcess )
            {
                server->write( "4\n" );
                server->waitForBytesWritten( -1 );
                end = true;
            }
            else
            {
                QString mediaType = QString::number( this->toUpload.at( mediaNumber )->getType() );
                QFileInfo fileInfo( this->toUpload.at( mediaNumber )->getFullPath() );

                emit progress(0, this->toUpload.at ( mediaNumber ) );
                server->write( mediaType.toUtf8() );
                server->waitForBytesWritten( -1 );

                if ( server->bytesAvailable() == 0 )
                    server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                message = server->readLine();
                message.chop( 1 );

                if (message == "name?")
                {
                    server->write( this->toUpload.at( mediaNumber )->getFullName().toUtf8()+"\n" );
                    server->waitForBytesWritten( -1 );

                    if ( server->bytesAvailable() == 0 )
                        server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                    message = server->readLine();
                    message.chop( 1 );

                    if (message == "buffer length?")
                    {
                        server->write( "512" );
                        server->waitForBytesWritten( -1 );

                        QFile file(this->toUpload.at( mediaNumber )->getFullPath() );
                        file.open( QIODevice::ReadOnly );
                        int fileSize = fileInfo.size();
                        int chunkNunmber = fileSize / 512 +1;

                        int chunkCounter = 0;
                        QByteArray chunk;
                        bool fileEnd = false;
                        while ( !fileEnd && !this->stopUploadProcess)
                        {
                            chunkCounter++;
                            chunk = file.read( 512 );
                            if ( chunk.isEmpty() )
                                fileEnd = true;
                            else
                            {
                                server->write(chunk);
                                server->waitForBytesWritten( -1 );

                                if ( server->bytesAvailable() == 0 )
                                    server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                                QString response = server->readLine();
                                response.chop( 1 );
                                if (response != QString::number( chunkCounter ) )
                                {
                                    this->stopUpload();
                                    stopCause = "chunk lost";
                                }
                                emit progress(100*chunkCounter/chunkNunmber, this->toUpload.at ( mediaNumber ));
                            }
                        }
                        file.close();

                        if (this->stopUploadProcess)
                        {
                            server->write( "STOP\n" );
                            server->waitForBytesWritten( -1 );
                        }
                        else
                        {
                            server->write( "END\n" );
                            server->waitForBytesWritten( -1 );
                        }

                        if ( server->bytesAvailable() == 0 )
                            server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                        message = server->readLine();
                        message.chop( 1 );
                        if ( message != "ok" )
                            emit finish( "no final confirm" );
                        mediaNumber++;
                    }
                    else
                        emit finish( "protocol error" );
                }
                else
                     emit finish( "protocol error" );
            }
        }
        else
             emit finish( "unknow initial message: " + message );
    }
    server->close();
    emit finish( stopCause );
}
