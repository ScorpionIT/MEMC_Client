#include "FileUploader.h"
#include <QDebug>

using namespace userInterface;

FileUploader::FileUploader(core::Connection *conn, QWidget *parent) : QWidget(parent)
{
    this->connection = conn;
    this->selectdFile = new QVector<QFileInfo>;
    this->selectedFileList = new QListWidget();
    this->selectedFileList->setSelectionMode( QAbstractItemView::ExtendedSelection );
    this->selectedFileList->setAlternatingRowColors( true );

    this->buttonLayout = new QHBoxLayout();
    this->cleanButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/clean.png" ), "CLEAN" );
    connect( this->cleanButton, SIGNAL( clicked() ), this, SLOT( clearButtonPressed() ) );

    this->browseButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/filemanager.png" ), "BROWSE" );
    connect( this->browseButton, SIGNAL( clicked() ), this, SLOT( browseButtonPressed() ) );

    this->uploadButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/add.png" ), "UPLOAD" );
    connect( this->uploadButton, SIGNAL( clicked() ), this, SLOT( uploadButtonPressed() ) );

    this->buttonLayout->addWidget( this->cleanButton );
    this->buttonLayout->addWidget( this->browseButton );
    this->buttonLayout->addWidget( this->uploadButton );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->buttonLayout );
    this->vLayout->addWidget( this->selectedFileList );

    this->progressLayout = new QHBoxLayout();
    this->progressBar = new QProgressBar();
    this->progressBar->setVisible( false );
    this->progressLayout->addWidget( this->progressBar );
    this->stopUploadButton = new QPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/deleteicon.png" ), "STOP" );
    this->stopUploadButton->setVisible( false );
    connect( this->stopUploadButton, SIGNAL( clicked() ), this, SLOT( stopUploadButtonPressed()) );
    this->progressLayout->addWidget( this->stopUploadButton );

    this->vLayout->addLayout( (this->progressLayout) );
    this->setLayout( this->vLayout );
}

FileUploader::~FileUploader()
{
}

void FileUploader::clearButtonPressed()
{
    this->selectdFile->clear();
    this->selectedFileList->clear();
}

void FileUploader::stopUploadButtonPressed()
{
    this->uploader->stopUpload();
}

void FileUploader::browseButtonPressed()
{
    QStringList chosenFiles = QFileDialog::getOpenFileNames( this, "Select one or more files to open", QDir::homePath(), "Media (*.avi *.mkv *mp3 *.wav)");
    for ( int i = 0; i < chosenFiles.size(); i++ )
    {
        this->selectdFile->append( QFileInfo ( chosenFiles[i] ));
        QString extension = this->selectdFile->last().suffix();

        QListWidgetItem* item = new QListWidgetItem( this->selectdFile->last().completeBaseName(), this->selectedFileList );
        QSize tmp = item->sizeHint();
        tmp.setHeight( 35 );
        item->setSizeHint( tmp );

        if ( extension == "avi" || extension == "mkv")
            item->setIcon( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png" ) );
        else if ( extension == "mp3" || extension == "wav")
            item->setIcon( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ) );
    }
}

void FileUploader::uploadButtonPressed()
{
    this->cleanButton->setEnabled( false );
    this->browseButton->setEnabled( false );
    this->uploadButton->setEnabled( false );
    uploader = new core::Uploader (this->selectdFile, "127.0.0.1", "80002", "Elia", this->connection->getSessionID());
    connect (uploader, SIGNAL( progress( int,QString) ), this, SLOT( uploadProgress(int,QString) ) );
    connect (uploader, SIGNAL( finish( QString ) ), this, SLOT( uploadFinished( QString) ) );
    uploader->start();
}

void FileUploader::uploadProgress(int percent, QString fileName)
{
    this->progressBar->setValue( percent );
    this->progressBar->setFormat( fileName+" (%p%)");
    this->progressBar->setVisible( true );
    this->stopUploadButton->setVisible( true );
    if (percent == 100)
    {
        QListWidgetItem* item = this->selectedFileList->findItems(fileName, Qt::MatchExactly).first();
        delete  item;
    }
}

void FileUploader::uploadFinished(QString error)
{
    if ( error.isEmpty() )
    {
        this->progressBar->setVisible( false );
        this->stopUploadButton->setVisible( false );
        this->cleanButton->setEnabled( true );
        this->browseButton->setEnabled( true );
        this->uploadButton->setEnabled( true );
    }
    else
        this->progressBar->setFormat( error );
    delete sender();
}

