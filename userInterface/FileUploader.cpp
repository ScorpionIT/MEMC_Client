#include "FileUploader.h"
#include <QDebug>

using namespace userInterface;

FileUploader::FileUploader(QWidget *parent) : QWidget(parent)
{
    this->selectdFile = new QVector<QFileInfo>;
    this->selectedMediaList = new MediaFileUploadWidgetList();

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
    this->vLayout->addWidget( this->selectedMediaList );

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
    this->selectedMediaList->clear();
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
        this->selectedMediaList->addMedia( new core::MediaFile (chosenFiles[i]) );
    }
}

void FileUploader::uploadButtonPressed()
{
    this->cleanButton->setEnabled( false );
    this->browseButton->setEnabled( false );
    this->uploadButton->setEnabled( false );
    uploader = new core::Uploader ( this->selectedMediaList->getMediaFiles() );
    connect (uploader, SIGNAL( progress( int, core::MediaFile* ) ), this, SLOT( uploadProgress( int, core::MediaFile* ) ) );
    connect (uploader, SIGNAL( finish( QString ) ), this, SLOT( uploadFinished( QString) ) );
    uploader->start();
}

void FileUploader::uploadProgress(int percent, core::MediaFile* media)
{
    this->progressBar->setValue( percent );
    this->progressBar->setFormat( media->getName()+" (%p%)");
    this->progressBar->setVisible( true );
    this->stopUploadButton->setVisible( true );
    if (percent == 100)
        this->selectedMediaList->deleteMedia( media );
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

