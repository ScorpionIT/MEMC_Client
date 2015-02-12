#include "MediaPlayerWidget.h"

#include <QDebug>

using namespace userInterface;

MediaPlayerWidget::MediaPlayerWidget(QWidget *parent) : QWidget(parent)
{
    this->media = nullptr;
    this->fullScreen = false;
    this->mainLayout = new QVBoxLayout();
    this->controlsLayout = new QHBoxLayout();

    this->vlcInstance = new VlcInstance( VlcCommon::args(), this );
    this->vlcPlayer = new VlcMediaPlayer( this->vlcInstance );

    this->videoWidget = new VlcWidgetVideo();
    this->videoWidget->setMediaPlayer( this->vlcPlayer );
    this->videoWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    this->videoWidget->setStyleSheet( "background-color: black;" );
    connect( this->videoWidget, SIGNAL( doubleClick() ), this, SLOT( setToggleFullscreen() ) );
    this->vlcPlayer->setVideoWidget( this->videoWidget );
    this->mainLayout->addWidget( this->videoWidget );

    this->fullVideoWidget = new VlcWidgetVideo();
    this->fullVideoWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    this->fullVideoWidget->setStyleSheet( "background-color: black;" );
    connect( this->fullVideoWidget, SIGNAL( doubleClick() ), this, SLOT( setToggleFullscreen() ) );

    this->seekWidget = new VlcWidgetSeek();
    this->seekWidget->setMediaPlayer( this->vlcPlayer );
    this->mainLayout->addWidget( this->seekWidget );

    this->playPauseButton = new QPushButton ( IconLoader::getIstance()->getIcon(IconLoader::PLAY) , "" );
    this->playPauseButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    connect (this->playPauseButton, SIGNAL( clicked() ), this, SLOT( playPausePressed() ) );
    this->controlsLayout->addWidget( this->playPauseButton );

    this->stopButton = new QPushButton ( IconLoader::getIstance()->getIcon( IconLoader::STOP), "" );
    connect (this->stopButton, SIGNAL( clicked() ), this, SLOT( stopPressed() ) );
    this->stopButton->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    this->controlsLayout->addWidget( this->stopButton );

    this->controlsLayout->addWidget( new Spacer() );
    this->volumeSlider = new VlcWidgetVolumeSlider();
    this->volumeSlider->setOrientation( Qt::Horizontal );
    this->volumeSlider->setMediaPlayer( this->vlcPlayer );
    this->volumeSlider->setVolume( 50 );
    this->controlsLayout->addWidget( this->volumeSlider );

    this->mainLayout->addLayout( this->controlsLayout );
    this->setLayout( this->mainLayout );
}

MediaPlayerWidget::~MediaPlayerWidget()
{

}

void MediaPlayerWidget::setMedia(core::media::MediaFile *mediaFile)
{
    this->vlcPlayer->stop();

    VlcMedia *tmp = nullptr;
    if ( this->media != nullptr )
        tmp = this->media;

    QString sessionID = core::network::Session::getSession()->getID();
    QString userName = core::network::Session::getSession()->getUsername();

    this->media = new VlcMedia ( "http://localhost:8086/" + sessionID + "/" + userName + "/" + mediaFile->getFullName(), false, this->vlcInstance );
    this->vlcPlayer->open( this->media );
    this->playPauseButton->setIcon( IconLoader::getIstance()->getIcon(IconLoader::PAUSE ) );

    if ( tmp != nullptr )
        delete tmp;
}

void MediaPlayerWidget::setToggleFullscreen()
{
    qDebug() << "ENTRA";
    if (this->fullScreen)
    {
        float position = this->vlcPlayer->position();
        this->vlcPlayer->stop();
        this->fullScreen = false;
        this->fullVideoWidget->hide();
        this->videoWidget->setMediaPlayer( this->vlcPlayer );
        this->vlcPlayer->setVideoWidget( this->videoWidget );
        this->videoWidget->showFullScreen();
        this->vlcPlayer->play();
        this->vlcPlayer->setPosition(position);
    }
    else
    {
        float position = this->vlcPlayer->position();
        this->vlcPlayer->stop();

        this->fullScreen = true;
        this->fullVideoWidget->setMediaPlayer( this->vlcPlayer );
        this->vlcPlayer->setVideoWidget( this->fullVideoWidget );
        this->fullVideoWidget->showFullScreen();
        this->vlcPlayer->play();
        this->vlcPlayer->setPosition(position);
    }
}

void MediaPlayerWidget::playPausePressed()
{
    if ( this->vlcPlayer->currentMedia() != nullptr )
    {
        if (this->vlcPlayer->state() == Vlc::State::Playing)
        {
            this->vlcPlayer->pause();
            this->playPauseButton->setIcon( IconLoader::getIstance()->getIcon(IconLoader::PLAY ) );
        }

        else
        {
            this->vlcPlayer->play();
            this->playPauseButton->setIcon( IconLoader::getIstance()->getIcon(IconLoader::PAUSE ) );
        }
    }
}

void MediaPlayerWidget::stopPressed()
{
    this->vlcPlayer->stop();
    this->playPauseButton->setIcon( IconLoader::getIstance()->getIcon(IconLoader::PLAY ) );
}
