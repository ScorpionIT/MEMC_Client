#include "FileUploader.h"

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
    this->errorMessage = new QLabel("Errore");
    this->errorMessage->setAlignment( Qt::AlignCenter );
    this->errorMessage->setStyleSheet( "color:red; font-weight: bold;");
    this->errorMessage->setVisible( false );
    this->progressLayout->addWidget( this->errorMessage );
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
    this->errorMessage->setVisible( false );
}

void FileUploader::stopUploadButtonPressed()
{
    this->uploadService->stopUpload();
}

void FileUploader::browseButtonPressed()
{
    QStringList chosenFiles = QFileDialog::getOpenFileNames( this, "Select one or more files to open", QDir::homePath(), "Media Files (*.avi *.mkv *ogg *.mp3)");
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
    QProgressBar* progressBar = this->selectedMediaList->getMediaProgressBar( media );
    progressBar->setValue( percent );
    progressBar->setFormat( "%p%");
    this->stopUploadButton->setVisible( true );
    if (percent == 100)
        progressBar->setFormat( "Complete" );
}

void FileUploader::uploadFinished(QString error)
{
    this->stopUploadButton->setVisible( false );

    if ( !error.isEmpty() )
    {
        this->errorMessage->setVisible( true );
        this->errorMessage->setText( error );
    }

    this->cleanButton->setEnabled( true );
    this->browseButton->setEnabled( true );
    this->uploadButton->setEnabled( true );

    delete sender();
}

