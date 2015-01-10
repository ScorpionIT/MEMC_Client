#include "uploader.h"

Uploader::Uploader(QVector<QFileInfo>* toUpload, QString serverAddr, QString serverPort, QString username, QString sessionID)
    : ServiceConnection ( serverAddr, serverPort, username, sessionID )
{
    this->toUpload = toUpload;
    this->stopUploadProcess = false;
}

Uploader::~Uploader()
{
}

void Uploader::stopUpload()
{
    this->stopUploadProcess = true;
}

void Uploader::processService(QTcpSocket *server)
{
    QString message;
    int fileNumber = 0;
    bool end = false;
    while ( !end )
    {
        server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
        message = server->readLine();
        message.chop( 1 );

        if (message == "what do you have for me?[MUSIC=1, VIDEO=2, IMAGES=3, FINISH=4]")
        {
            if ( fileNumber == this->toUpload->size() || this->stopUploadProcess)
            {
                server->write( "4\n" );
                server->waitForBytesWritten( -1 );
                end = true;
            }
            else
            {
                QString extension = this->toUpload->at( fileNumber ).suffix();
                QString fileName = this->toUpload->at( fileNumber ).completeBaseName();
                QString fileType;

                if ( extension == "avi" || extension == "mkv")
                    fileType = "2\n";
                else if ( extension == "mp3" || extension == "wav")
                    fileType = "1\n";

                emit progress(0, fileName);
                server->write( fileType.toUtf8() );
                server->waitForBytesWritten( -1 );

                server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                message = server->readLine();
                message.chop( 1 );

                if (message == "name?")
                {
                    server->write( this->toUpload->at( fileNumber ).fileName().toUtf8()+"\n" );
                    server->waitForBytesWritten( -1 );

                    server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                    message = server->readLine();
                    message.chop( 1 );

                    if (message == "buffer length?")
                    {
                        server->write( "512" );
                        server->waitForBytesWritten( -1 );

                        QFile file(this->toUpload->at( fileNumber ).filePath() );
                        file.open( QIODevice::ReadOnly );
                        int fileSize = this->toUpload->at( fileNumber ).size();
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

                                server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                                QString response = server->readLine();
                                response.chop( 1 );
                                if (response != QString::number( chunkCounter ) )
                                    qDebug() << "chunck lost";

                                emit progress(100*chunkCounter/chunkNunmber, fileName);
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

                        server->waitForReadyRead( ServiceConnection::SESSION_TIMER );
                        message = server->readLine();
                        message.chop( 1 );
                        if ( message != "ok" )
                            qDebug() << "no final confirm";
                        fileNumber++;
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
    emit finish("");
    server->close();
}
