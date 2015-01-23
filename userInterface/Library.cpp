#include "Library.h"

using namespace userInterface;

Library::Library( QWidget *parent) : QWidget(parent)
{
    this->mediaInfo = nullptr;
    this->currentMediaSection = core::media::INVALIDMEDIA;
    this->buttonsLayout = new QHBoxLayout();
    this->movieButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::MOVIE ), "MOVIES" );
    connect ( this->movieButton, SIGNAL( clicked() ), this, SLOT( movieButtonPressed() ) );

    this->musicButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::MUSIC ) , "MUSIC" );
    connect ( this->musicButton, SIGNAL( clicked() ), this, SLOT( musicButtonPressed() ) );

    this->imageButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::IMAGE ), "IMAGES" );
    connect ( this->imageButton, SIGNAL( clicked() ), this, SLOT( imageButtonPressed() ) );

    this->buttonsLayout->addWidget( this->movieButton );
    this->buttonsLayout->addWidget( this->musicButton );
    this->buttonsLayout->addWidget( this->imageButton );

    this->vLayout = new QVBoxLayout();
    this->mediaHLayout = new QHBoxLayout();
    this->mediaVLayout = new QVBoxLayout();

    this->vLayout->addLayout( this->buttonsLayout);

    this->mediaList = new MediaFileWidgetList();
    connect( this->mediaList, SIGNAL( itemSelectionChanged() ), this, SLOT( mediaSelected() ) );

    this->mediaButtonLayout = new QHBoxLayout();

    this->deleteMediaButton = new MPushButton ( IconLoader::getIstance()->getIcon( IconLoader::DEL ), "Delete media" );
    connect( this->deleteMediaButton, SIGNAL( clicked() ), this, SLOT( deleteMediaPressed() ) );

    this->toPrivateButton = new MPushButton ( IconLoader::getIstance()->getIcon( IconLoader::LOCK ), "Make private" );
    connect(this->toPrivateButton, SIGNAL( clicked() ), this, SLOT( toPrivatePressed() ) );

    this->toPublicButton = new MPushButton ( IconLoader::getIstance()->getIcon( IconLoader::UNLOCK ), "Make public" );
    connect(this->toPublicButton, SIGNAL( clicked() ), this, SLOT( toPublicPressed() ) );

    this->mediaButtonLayout->addWidget( this->deleteMediaButton );
    this->mediaButtonLayout->addWidget( this->toPublicButton );
    this->mediaButtonLayout->addWidget( this->toPrivateButton );

    this->mediaVLayout->addWidget( this->mediaList );
    this->mediaVLayout->addLayout( this->mediaButtonLayout );
    this->mediaHLayout->addLayout( this->mediaVLayout );

    this->vLayout->addLayout( this->mediaHLayout );
    this->setLayout(vLayout);
    this->movieButtonPressed();
}


Library::~Library()
{

}

void Library::setMediaInfoWidget(MediaInfoView *mediaInfoView)
{
    if ( this->mediaInfo != nullptr )
    {
        delete this->mediaInfo;
        this->mediaInfo = nullptr;
    }

    if (mediaInfoView != nullptr)
    {
        this->mediaInfo = mediaInfoView;
        this->mediaHLayout->addWidget( this->mediaInfo );

    }
}

void Library::loadMediaList()
{
    this->mediaList->clear();
    if ( this->currentMediaSection != core::media::INVALIDMEDIA )
    {
        core::service::FileListService* fileListService = new core::service::FileListService ( this->currentMediaSection );
        connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addFileList( QList<core::media::MediaFile*>*,QString ) ) );
        fileListService->start();
    }
}

void Library::addFileList(QList<core::media::MediaFile*> *mediaList, QString response)
{
    if (response == "end")
    {
        for ( QList<core::media::MediaFile*>::iterator i = mediaList->begin() ; i != mediaList->end(); i++ )
            this->mediaList->addMedia( (*i) );
        this->mediaList->setCurrentItem( this->mediaList->item( 0 ) );
    }
    delete sender();
}

void Library::movieButtonPressed()
{
    this->currentMediaSection = core::media::MediaType::MOVIE;
    this->setMediaInfoWidget( new MovieMediaInfoWidget() );
    this->movieButton->setEnabled( false );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( true );
    this->loadMediaList();
}

void Library::musicButtonPressed()
{
    this->currentMediaSection = core::media::MediaType::MUSIC;
    this->setMediaInfoWidget( new MusicMediaInfo() );
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( false );
    this->imageButton->setEnabled( true );
    this->loadMediaList();
}

void Library::imageButtonPressed()
{
    this->currentMediaSection = core::media::MediaType::IMAGE;
    this->setMediaInfoWidget( nullptr );
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( false );
    this->loadMediaList();
}

void Library::deleteMediaPressed()
{
    QList<core::media::MediaFile*> selectedMedia = this->mediaList->selectedMedia();
    QString toRemove;
    for( QList<core::media::MediaFile*>::iterator i = selectedMedia.begin(); i != selectedMedia.end(); i++ )
    {
        toRemove.append( (*i)->getName() );
        if ( i+1 != selectedMedia.end() )
            toRemove.append( "\n" );
    }
    if ( !toRemove.isEmpty() )
    {
        int ret = QMessageBox::warning(this, "Remove Media", toRemove + "\n\nDo you want to remove these files from the server?",
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes)
        {
            core::service::FileManagerService* fileManagerService = new core::service::FileManagerService (selectedMedia, core::service::Operation::DELETE);
            connect (fileManagerService, SIGNAL( finish( QString ) ), this, SLOT( serviceResponse( QString ) ) );
            fileManagerService->start();
        }
    }
}

void Library::toPrivatePressed()
{
    QList<core::media::MediaFile*> selectedMedia = this->mediaList->selectedMedia();
    if ( selectedMedia.count() == 1 )
    {
        core::service::FileManagerService* fileManagerService = new core::service::FileManagerService (selectedMedia, core::service::Operation::LOCK);
        connect (fileManagerService, SIGNAL( finish( QString ) ), this, SLOT( serviceResponse( QString ) ) );
        fileManagerService->start();
    }
    else
    {
        QString toLock;
        for( QList<core::media::MediaFile*>::iterator i = selectedMedia.begin(); i != selectedMedia.end(); i++ )
        {
            toLock.append( (*i)->getName() );
            if ( i+1 != selectedMedia.end() )
                toLock.append( "\n" );
        }
        if ( !toLock.isEmpty() )
        {
            int ret = QMessageBox::warning(this, "Remove Media", toLock + "\n\nDo you want to set these files private?",
                                           QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes)
            {
                core::service::FileManagerService* fileManagerService = new core::service::FileManagerService (selectedMedia, core::service::Operation::LOCK);
                connect (fileManagerService, SIGNAL( finish( QString ) ), this, SLOT( serviceResponse( QString ) ) );
                fileManagerService->start();
            }
        }
    }
}

void Library::toPublicPressed()
{
    QList<core::media::MediaFile*> selectedMedia = this->mediaList->selectedMedia();
    if ( selectedMedia.count() == 1 )
    {
        core::service::FileManagerService* fileManagerService = new core::service::FileManagerService (selectedMedia, core::service::Operation::UNLOCK);
        connect (fileManagerService, SIGNAL( finish( QString ) ), this, SLOT( serviceResponse( QString ) ) );
        fileManagerService->start();
    }
    else
    {
        QString toLock;
        for( QList<core::media::MediaFile*>::iterator i = selectedMedia.begin(); i != selectedMedia.end(); i++ )
        {
            toLock.append( (*i)->getName() );
            if ( i+1 != selectedMedia.end() )
                toLock.append( "\n" );
        }
        if ( !toLock.isEmpty() )
        {
            int ret = QMessageBox::warning(this, "Remove Media", toLock + "\n\nDo you want to set these files public?",
                                           QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes)
            {
                core::service::FileManagerService* fileManagerService = new core::service::FileManagerService (selectedMedia, core::service::Operation::UNLOCK);
                connect (fileManagerService, SIGNAL( finish( QString ) ), this, SLOT( serviceResponse( QString ) ) );
                fileManagerService->start();
            }
        }
    }
}

void Library::mediaSelected()
{
    QList<core::media::MediaFile*> selectedMedia = this->mediaList->selectedMedia();
    if ( !selectedMedia.isEmpty() )
    {
        if( selectedMedia.count() == 1 )
        {
            if ( selectedMedia.first()->isPublic() )
            {
                this->toPublicButton->setEnabled( false );
                this->toPrivateButton->setEnabled( true );
            }
            else
            {
                this->toPublicButton->setEnabled( true );
                this->toPrivateButton->setEnabled( false );
            }
            if ( this->mediaInfo != nullptr )
                this->mediaInfo->setMedia( selectedMedia.first() );
        }
        else
        {
            this->toPublicButton->setEnabled( true );
            this->toPrivateButton->setEnabled( true );
        }
    }
}

void Library::serviceResponse(QString response)
{
    if (response == "Done")
        this->loadMediaList();
    else
        QMessageBox::critical(this, "Error", response, QMessageBox::Ok);

    delete sender();
}

