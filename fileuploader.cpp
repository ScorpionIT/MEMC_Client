#include "fileuploader.h"
#include <QDebug>

FileUploader::FileUploader(QWidget *parent) : QWidget(parent)
{
    this->selectedFile = new QListWidget();
    this->selectedFile->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/add.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");

    this->buttonLayout = new QHBoxLayout();
    this->cleanButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/clean.png" ), "CLEAN" );
    connect( this->cleanButton, SIGNAL( clicked() ), this->selectedFile, SLOT( clear() ) );
    this->browseButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/filemanager.png" ), "BROWSE" );
    connect( this->browseButton, SIGNAL( clicked() ), this, SLOT( browseButtonPressed() ) );
    this->uploadButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/add.png" ), "UPLOAD" );
    connect( this->uploadButton, SIGNAL( clicked() ), this, SLOT( uploadButtonPressed() ) );
    this->buttonLayout->addWidget( this->cleanButton );
    this->buttonLayout->addWidget( this->browseButton );
    this->buttonLayout->addWidget( this->uploadButton );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->buttonLayout );
    this->vLayout->addWidget( this->selectedFile );

    this->progressBar = new QProgressBar();
    this->progressBar->setValue( 50 );
    this->vLayout->addWidget( this->progressBar );

    this->setLayout( this->vLayout );
}

FileUploader::~FileUploader()
{

}

void FileUploader::browseButtonPressed()
{
    QStringList chosedFiles = QFileDialog::getOpenFileNames( this, "Select one or more files to open", QDir::homePath());
    for ( int i = 0; i < chosedFiles.size(); i++ )
        new QListWidgetItem( chosedFiles[i], this->selectedFile );
}

void FileUploader::uploadButtonPressed()
{
    QMessageBox::warning(this, "Warning", "Not implemented yet");
}

