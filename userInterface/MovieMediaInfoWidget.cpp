#include "MovieMediaInfoWidget.h"

using namespace userInterface;


MovieMediaInfoWidget::MovieMediaInfoWidget()
{
    QPixmap poster = QPixmap( "/home/elia/Development/Qt/MEMC_Client/image/no-poster.jpg" ).scaledToWidth(185);

    this->getMovieInfo = nullptr;
    this->mediaLogo = new QPushButton();
    this->mediaLogo->setFlat( true );
    this->mediaLogo->setIcon( poster );
    this->mediaLogo->setIconSize( QSize(poster.width()+5, poster.height()+5) );
    connect ( this->mediaLogo, SIGNAL( clicked() ), this, SLOT( editMediaInfoPressed() ) );

    this->vLayout = new QVBoxLayout();
    vLayout->addWidget( this->mediaLogo );

    vLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );

    this->title = new QLabel ( "<b>Title:</b><br> no data" );
    vLayout->addWidget ( this->title );
    vLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );

    this->description = new QLabel ( "<b>Description:</b><br> no data" );
    this->description->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    vLayout->addWidget ( this->description );

    vLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );
    this->setLayout( vLayout );
}

MovieMediaInfoWidget::~MovieMediaInfoWidget()
{
    if ( this->getMovieInfo != nullptr )
        delete this->getMovieInfo;
}

void MovieMediaInfoWidget::setMedia( core::media::MediaFile* mediaFile )
{
    this->mediaFile = mediaFile;
    if ( this->getMovieInfo != nullptr )
    {
        delete this->getMovieInfo;
        this->getMovieInfo = nullptr;
    }
}

void MovieMediaInfoWidget::editMediaInfoPressed()
{
    this->getMovieInfo = new GetMovieInfo( this, mediaFile );
    this->getMovieInfo->show();
}
