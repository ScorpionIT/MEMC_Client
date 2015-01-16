#include "MusicMediaInfo.h"
#include <QDebug>

using namespace userInterface;

MusicMediaInfo::MusicMediaInfo()
{
    this->fileName = nullptr;
    this->mediaLogo = new QLabel ();
    this->mediaLogo->setPixmap ( IconLoader::getIstance()->getIcon( IconLoader::MUSIC ) );
    this->mediaLogo->resize (128, 98);

    this->playMediaButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::MUSIC ), "Play Media" );
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
    vLayout->addWidget( this->playMediaButton );
    this->setLayout( vLayout );
}

MusicMediaInfo::~MusicMediaInfo()
{

}

void MusicMediaInfo::setMedia()
{

}
