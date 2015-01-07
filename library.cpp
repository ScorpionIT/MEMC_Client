#include "library.h"
FileManager::FileManager(QWidget *parent) : QWidget(parent)
{

    this->buttonsLayout = new QHBoxLayout();
    this->movieButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png" ), "MOVIES" );
    connect ( this->movieButton, SIGNAL( clicked() ), this, SLOT( movieButtonPressed() ) );

    this->musicButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ), "MUSIC" );
    connect ( this->musicButton, SIGNAL( clicked() ), this, SLOT( musicButtonPressed() ) );

    this->imageButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png" ), "IMAGES" );
    connect ( this->imageButton, SIGNAL( clicked() ), this, SLOT( imageButtonPressed() ) );

    this->buttonsLayout->addWidget( this->movieButton );
    this->buttonsLayout->addWidget( this->musicButton );
    this->buttonsLayout->addWidget( this->imageButton );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->buttonsLayout);

    this->fileList = new QListWidget();
    this->vLayout->addWidget( this->fileList );

    this->setLayout(vLayout);
    this->movieButtonPressed();
}

FileManager::~FileManager()
{

}

void FileManager::movieButtonPressed()
{
    this->movieButton->setEnabled( false );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( true );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");
}

void FileManager::musicButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( false );
    this->imageButton->setEnabled( true );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");
}

void FileManager::imageButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( false );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");
}

