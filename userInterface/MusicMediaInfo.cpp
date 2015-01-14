#include "MusicMediaInfo.h"
#include <QDebug>

using namespace userInterface;

MusicMediaInfo::MusicMediaInfo()
{
    this->fileName = nullptr;
    this->mediaLogo = new QLabel ();
    this->mediaLogo->setPixmap ( QPixmap ( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ) );
    this->mediaLogo->resize (128, 98);

    this->deleteMediaButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/clean.png" ), "Delete media" );
    //connect (this->deleteMediaButton, SIGNAL( clicked() ), this, SLOT( deleteMediaButtonPressed() ) );

    this->vLayout = new QVBoxLayout();
    vLayout->addWidget( this->mediaLogo );

    QLabel* label = new QLabel ( "<b>Title:</b> " );
    vLayout->addWidget ( label );
    label = new QLabel ( "<b>Author:</b> " );
    vLayout->addWidget ( label );

    label = new QLabel ( "<b>Album:</b> " );
    vLayout->addWidget ( label );
    label = new QLabel ( "<b>Duration:</b> " );
    vLayout->addWidget ( label );
    vLayout->addSpacing( 50 );
    vLayout->addWidget( this->deleteMediaButton );
    this->setLayout( vLayout );
}

MusicMediaInfo::~MusicMediaInfo()
{

}
