#include "Library.h"

using namespace userInterface;

Library::Library( QWidget *parent) : QWidget(parent)
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
    this->hLayout = new QHBoxLayout();

    this->vLayout->addLayout( this->buttonsLayout);

    this->mediaList = new MediaFileWidgetList();


    this->hLayout->addWidget( this->mediaList );
    this->hLayout->addWidget( new MusicMediaInfo () );

    this->vLayout->addLayout( this->hLayout );
    this->setLayout(vLayout);
    this->movieButtonPressed();
}

Library::~Library()
{

}

void Library::loadFileList(QList<core::MediaFile*> *mediaList, QString response)
{
    if (response == "end")
    {
        for ( QList<core::MediaFile*>::iterator i = mediaList->begin() ; i != mediaList->end(); i++ )
            this->mediaList->addMedia( (*i) );
        this->mediaList->setCurrentItem( this->mediaList->item( 0 ) );
    }
    delete sender();
}

void Library::movieButtonPressed()
{
    this->movieButton->setEnabled( false );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( true );

    this->mediaList->clear();
    this->fileService = new core::FileService ( core::MediaType::MOVIE );
    connect( this->fileService, SIGNAL( finish( QList<core::MediaFile*>*,QString ) ), this, SLOT( loadFileList( QList<core::MediaFile*>*,QString ) ) );
    this->fileService->start();
}

void Library::musicButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( false );
    this->imageButton->setEnabled( true );

    this->mediaList->clear();
    this->fileService = new core::FileService ( core::MediaType::MUSIC );
    connect( this->fileService, SIGNAL( finish( QList<core::MediaFile*>*,QString ) ), this, SLOT( loadFileList( QList<core::MediaFile*>*,QString ) ) );
    this->fileService->start();
}

void Library::imageButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( false );

    this->mediaList->clear();
    this->fileService = new core::FileService ( core::MediaType::IMAGE );
    connect( this->fileService, SIGNAL( finish( QList<core::MediaFile*>*,QString ) ), this, SLOT( loadFileList( QList<core::MediaFile*>*,QString ) ) );
    this->fileService->start();
}

