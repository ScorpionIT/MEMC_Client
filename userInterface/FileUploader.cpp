#include "FileUploader.h"
#include <QDebug>

using namespace userInterface;

FileUploader::FileUploader(QWidget *parent) : QWidget(parent)
{
    this->selectedMediaList = new MediaFileUploadWidgetList();

    this->buttonLayout = new QHBoxLayout();
    this->cleanButton = new MPushButton( IconLoader::getIstance()->getIcon(IconLoader::CLEAN), "CLEAN" );
    connect( this->cleanButton, SIGNAL( clicked() ), this, SLOT( clearButtonPressed() ) );

    this->browseButton = new MPushButton( IconLoader::getIstance()->getIcon(IconLoader::BROWSE), "BROWSE" );
    connect( this->browseButton, SIGNAL( clicked() ), this, SLOT( browseButtonPressed() ) );

    this->uploadButton = new MPushButton( IconLoader::getIstance()->getIcon(IconLoader::UPLOAD), "UPLOAD" );
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
    this->stopUploadButton = new QPushButton( IconLoader::getIstance()->getIcon(IconLoader::DEL), "STOP" );
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
    this->selectedMediaList->clear();
}

void FileUploader::stopUploadButtonPressed()
{
    this->uploadService->stopUpload();
}

void FileUploader::browseButtonPressed()
{
    QStringList chosenFiles = QFileDialog::getOpenFileNames( this, "Select one or more files to open", QDir::homePath(), "Media (*.avi *.mkv *mp3 *.wav)");
    for ( int i = 0; i < chosenFiles.size(); i++ )
        this->selectedMediaList->addMedia( new core::media::MediaFile (chosenFiles[i]) );
}

void FileUploader::uploadButtonPressed()
{
    if (this->selectedMediaList->count() > 0)
    {
        this->cleanButton->setEnabled( false );
        this->browseButton->setEnabled( false );
        this->uploadButton->setEnabled( false );
        uploadService = new core::service::UploaderService ( this->selectedMediaList->getMediaFiles() );
        connect (uploadService, SIGNAL( progress( int, core::media::MediaFile* ) ), this, SLOT( uploadProgress( int, core::media::MediaFile* ) ) );
        connect (uploadService, SIGNAL( finish( QString ) ), this, SLOT( uploadFinished( QString) ) );
        uploadService->start();
    }
}

void FileUploader::uploadProgress(int percent, core::media::MediaFile* media)
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
    }
    else
        this->progressBar->setFormat( error );

    this->cleanButton->setEnabled( true );
    this->browseButton->setEnabled( true );
    this->uploadButton->setEnabled( true );

    delete sender();
}

