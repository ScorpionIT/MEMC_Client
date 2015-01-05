#include "filemanager.h"

FileManager::FileManager(QWidget *parent) : QWidget(parent)
{
    QFont buttonFont;
    QSize buttonIconSize ( 40, 40 );
    buttonFont.setPointSize( 10 );

    this->buttonsLayout = new QHBoxLayout();
    this->movieButton = new QPushButton( QPixmap ( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png" ), "MOVIES" );
    this->movieButton->setFont( buttonFont );
    this->movieButton->setIconSize( buttonIconSize );

    this->musicButton = new QPushButton( QPixmap ( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ), "MUSIC" );
    this->musicButton->setFont( buttonFont );
    this->musicButton->setIconSize( buttonIconSize );

    this->imageButton = new QPushButton( QPixmap ( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png" ), "IMAGES" );
    this->imageButton->setFont( buttonFont );
    this->imageButton->setIconSize( buttonIconSize );

    this->buttonsLayout->addWidget( this->movieButton );
    this->buttonsLayout->addWidget( this->musicButton );
    this->buttonsLayout->addWidget( this->imageButton );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->buttonsLayout);

    this->fileList = new QListWidget();
    this->vLayout->addWidget( this->fileList );

    this->setLayout(vLayout);
}

FileManager::~FileManager()
{

}

void FileManager::movieButtonPressed()
{

}

void FileManager::musicButtonPressed()
{

}

void FileManager::photoButtonPressed()
{

}

