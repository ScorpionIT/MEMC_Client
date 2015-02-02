#include "MediaPlayerWidget.h"

#include <QDebug>

using namespace userInterface;

MediaPlayerWidget::MediaPlayerWidget(QWidget *parent) : QWidget(parent)
{
    this->media = nullptr;
    this->mainLayout = new QVBoxLayout();
    this->controlsLayout = new QHBoxLayout();

    this->vlcInstance = new VlcInstance( VlcCommon::args(), this );
    this->vlcPlayer = new VlcMediaPlayer( this->vlcInstance );

    this->videoWidget = new VlcWidgetVideo();
    this->videoWidget->setMediaPlayer( this->vlcPlayer );
    this->vlcPlayer->setVideoWidget( this->videoWidget );
    this->videoWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    this->mainLayout->addWidget( this->videoWidget );

    this->seekWidget = new VlcWidgetSeek();
    this->seekWidget->setMediaPlayer( this->vlcPlayer );
    this->mainLayout->addWidget( this->seekWidget );

    this->playPauseButton = new QPushButton ( "Play" );
    connect (this->playPauseButton, SIGNAL( clicked() ), this, SLOT( playPausePressed() ) );
    this->controlsLayout->addWidget( this->playPauseButton );

    this->stopButton = new MPushButton ( "Stop" );
    connect (this->stopButton, SIGNAL( clicked() ), this->vlcPlayer, SLOT( stop() ) );
    this->controlsLayout->addWidget( this->stopButton );

    this->controlsLayout->addWidget( new Spacer() );
    this->volumeSlider = new VlcWidgetVolumeSlider();
    this->volumeSlider->setOrientation( Qt::Horizontal );
    this->volumeSlider->setMediaPlayer( this->vlcPlayer );
    this->volumeSlider->setVolume( 100 );
    this->volumeSlider->setEnabled( true );
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

    if ( tmp != nullptr )
        delete tmp;
}

void MediaPlayerWidget::playPausePressed()
{
    if (this->vlcPlayer->state() == Vlc::State::Playing)
        this->vlcPlayer->pause();
    else
        this->vlcPlayer->play();
}

/*this->vlcInstance = new VlcInstance( QStringList() );
this->player = new VlcMediaPlayer( this->vlcInstance );
QString sessionID = core::network::Session::getSession()->getID();
QString userName = core::network::Session::getSession()->getUsername();*/
/*VlcMedia *test = new VlcMedia ( "http://localhost:8085/" + sessionID + "/" + userName + "/Men In Black.mkv", false, this->vlcInstance );
//VlcMedia *test = new VlcMedia ( "http://localhost:8085/~elia/MIB.mkv", false, this->vlcInstance );
this->player->open( test );
this->player->play();*/


/*QUrl resource ("http://localhost/1023652/elia/Swing Gitan Solista.mp3");
    resource.setPort(8086);

    this->player = new QMediaPlayer( 0, QMediaPlayer::StreamPlayback );
    this->player->setMedia( resource );
    this->player->play();
    connect (this->player, SIGNAL( error(QMediaPlayer::Error) ), this, SLOT( mediaError(QMediaPlayer::Error ) ) );
    connect (this->player, SIGNAL( mediaStatusChanged(QMediaPlayer::MediaStatus) ), this, SLOT( mediaStatusChanged(QMediaPlayer::MediaStatus) ) );*/


/*this->duration = 0;
this->mediaPositionClicked = false;
this->mainLayout = new QVBoxLayout();

this->videoWidget = new QVideoWidget();
this->mediaPos = new QSlider( Qt::Horizontal );

this->mainLayout->addWidget( this->videoWidget );
this->mainLayout->addWidget( this->mediaPos );

this->buttonLayout = new QHBoxLayout();
this->playButton = new MPushButton ( "Play" );
//this->playButton->setEnabled( false );
connect (this->playButton, SIGNAL( clicked() ), this, SLOT( playButtonPressed() ) );
this->buttonLayout->addWidget( this->playButton );

this->pauseButton = new MPushButton ( "Pause" );
//this->pauseButton->setEnabled( false );
connect (this->pauseButton, SIGNAL( clicked() ), this, SLOT( pauseButtonPressed() ) );
this->buttonLayout->addWidget( this->pauseButton );

this->stopButton = new MPushButton ( "Stop" );
//this->stopButton->setEnabled( false );
connect (this->stopButton, SIGNAL( clicked() ), this, SLOT( stopButtonPressed() ) );
this->buttonLayout->addWidget( this->stopButton );

this->mainLayout->addLayout( this->buttonLayout );
this->setLayout( this->mainLayout );

this->duration = false;

this->player = new QMediaPlayer( 0, QMediaPlayer::StreamPlayback );
this->player->setVideoOutput( this->videoWidget );
connect (this->player, SIGNAL( positionChanged(qint64) ), this, SLOT( positionChanged(qint64) ) );
connect (this->player, SIGNAL( durationChanged(qint64) ), this, SLOT( durationChanged(qint64) ) );
connect (this->mediaPos, SIGNAL( sliderReleased() ), this, SLOT( chagePosition() ) );
connect (this->mediaPos, SIGNAL( sliderPressed() ), this, SLOT( mediaPositionPressed() ) );*/
