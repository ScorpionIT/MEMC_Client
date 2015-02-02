#include "DlnaManager.h"

using namespace userInterface;

DlnaManager::DlnaManager(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QHBoxLayout();
    this->buttonLayout = new QVBoxLayout();

    this->supportLayout = new QVBoxLayout();
    this->supportLabel = new QLabel( "<b>AVAIABLE MEDIA FILES</b>" );
    this->supportLabel->setAlignment( Qt::AlignCenter );
    this->myMediaList = new MixedMediaFileWidgetList ();
    this->supportLayout->addWidget( this->supportLabel );
    this->supportLayout->addWidget( this->myMediaList );
    this->mainLayout->addLayout( this->supportLayout );

    this->addToSharedButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::UPLOAD), "Add to shared");
    this->addToSharedButton->setEnabled( false );
    connect (this->addToSharedButton, SIGNAL( clicked() ), this, SLOT( addToSharedPressed() ) );

    this->removeFromSharedButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::DEL), "Remove from shared");
    this->removeFromSharedButton->setEnabled( false );
    connect ( this->removeFromSharedButton, SIGNAL( clicked() ), this, SLOT( removeFromSharedPressed() ) );

    this->cleanAndUpdateButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::CLEAN), "Clean and reload\n my media list");
    this->cleanAndUpdateButton->setEnabled( false );
    connect ( this->cleanAndUpdateButton, SIGNAL( clicked() ), this, SLOT( cleanAndUpdatePressed() ) );

    this->startDlnaShareButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::DLNA_GREEN), "Start DLNA share");
    this->startDlnaShareButton->setEnabled( false );
    connect( this->startDlnaShareButton, SIGNAL( clicked() ), this, SLOT( startDlnaSharePressed() ) );

    this->stopDlnaShareButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::DLNA_RED), "Stop DLNA share");
    connect( this->stopDlnaShareButton, SIGNAL( clicked() ), this, SLOT( stopDlnaSharePressed() ) );
    this->stopDlnaShareButton->setEnabled( false );

    this->buttonLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );
    this->buttonLayout->addWidget( this->addToSharedButton, 0, Qt::AlignVCenter);
    this->buttonLayout->addWidget( this->removeFromSharedButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( this->cleanAndUpdateButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( this->startDlnaShareButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( this->stopDlnaShareButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );
    this->mainLayout->addLayout( this->buttonLayout);

    this->supportLayout = new QVBoxLayout();
    this->supportLabel = new QLabel( "<b>DLNA SHARED MEDIA FILES</b>" );
    this->supportLabel->setAlignment( Qt::AlignCenter );
    this->sharedMediaList = new MixedMediaFileWidgetList ();
    this->supportLayout->addWidget( this->supportLabel );
    this->supportLayout->addWidget( this->sharedMediaList );
    this->mainLayout->addLayout( this->supportLayout );

    this->setLayout( this->mainLayout );
    loadMediaList();
}

DlnaManager::~DlnaManager()
{
    delete this->mainLayout;
    delete this->myMediaList;
    delete this->sharedMediaList;
    delete this->addToSharedButton;
    delete this->removeFromSharedButton;
}

void DlnaManager::addToSharedPressed()
{
    QList<core::media::MediaFile*> selected = this->myMediaList->selectedMedia();
    for ( QList<core::media::MediaFile*>::iterator i = selected.begin(); i != selected.end(); i++ )
    {
        this->myMediaList->deleteMedia( *i );
        this->sharedMediaList->addMedia( *i );
    }
}

void DlnaManager::removeFromSharedPressed()
{
    QList<core::media::MediaFile*> selected = this->sharedMediaList->selectedMedia();
    for ( QList<core::media::MediaFile*>::iterator i = selected.begin(); i != selected.end(); i++ )
    {
        this->sharedMediaList->deleteMedia( *i );
        this->myMediaList->addMedia( *i );
    }
}

void DlnaManager::cleanAndUpdatePressed()
{
    this->myMediaList->clear();
    this->sharedMediaList->clear();
    this->loadMediaList();
}

void DlnaManager::startDlnaSharePressed()
{
    if (this->sharedMediaList->count() > 0)
    {
        this->setState( DlnaState::UPDATESTATE );
        core::service::DlnaService* dlnaService = new core::service::DlnaService(this->sharedMediaList->getMediaFiles(), core::service::DLNAOperation::NEWSHARE );
        connect (dlnaService, SIGNAL( finish(QString) ), this, SLOT( dlnaServiceResponse(QString) ));
        dlnaService->start();
    }
}

void DlnaManager::stopDlnaSharePressed()
{
    this->sharedMediaList->clear();
    core::service::DlnaService* dlnaService = new core::service::DlnaService(this->sharedMediaList->getMediaFiles(), core::service::DLNAOperation::NEWSHARE );
    connect (dlnaService, SIGNAL( finish(QString) ), this, SLOT( dlnaServiceResponse(QString) ));
    dlnaService->start();
}

void DlnaManager::dlnaServiceResponse(QString message)
{
    if (message == "not running" )
        this->setState( DlnaState::STOPPED );
    else if (message == "ok")
        this->cleanAndUpdatePressed();
    else if ( message != "SHARESTATUS_OK" )
        QMessageBox::critical( this, "Server error", message, QMessageBox::Ok );
}

void DlnaManager::loadMediaList()
{
    core::service::DlnaService* dlnaService = new core::service::DlnaService(this->sharedMediaList->getMediaFiles(), core::service::DLNAOperation::SHARESTATUS );
    connect (dlnaService, SIGNAL( shareStatus(QList<core::media::MediaFile*>*) ), this, SLOT( addSharedMedia(QList<core::media::MediaFile*>*) ) );
    connect (dlnaService, SIGNAL( finish(QString) ), this, SLOT( dlnaServiceResponse(QString) ));
    dlnaService->start();
}

void DlnaManager::setState(DlnaState state)
{
    this->shareStatus = state;
    if ( state == DlnaState::STOPPED )
    {
        this->addToSharedButton->setEnabled( true );
        this->removeFromSharedButton->setEnabled( true );
        this->cleanAndUpdateButton->setEnabled( true );
        this->startDlnaShareButton->setEnabled( true );
        this->stopDlnaShareButton->setEnabled( false );
    }
    else if ( state == DlnaState::RUNNING )
    {
        this->addToSharedButton->setEnabled( false );
        this->removeFromSharedButton->setEnabled( false );
        this->cleanAndUpdateButton->setEnabled( false );
        this->startDlnaShareButton->setEnabled( false );
        this->stopDlnaShareButton->setEnabled( true );
    }
    else if ( state == DlnaState::UPDATESTATE )
    {
        this->addToSharedButton->setEnabled( false );
        this->removeFromSharedButton->setEnabled( false );
        this->cleanAndUpdateButton->setEnabled( false );
        this->startDlnaShareButton->setEnabled( false );
        this->stopDlnaShareButton->setEnabled( false );
    }
}

void DlnaManager::addMediaFileList(QList<core::media::MediaFile*> *mediaList, QString response )
{
    if (response == "end")
    {
        QList<core::media::MediaFile*> *toAdd = new QList<core::media::MediaFile*>;

        if ( this->sharedMediaList->count() > 0 )
        {
            QList<core::media::MediaFile*> shared = this->sharedMediaList->getMediaFiles();
            for ( QList<core::media::MediaFile*>::iterator z = mediaList->begin() ; z != mediaList->end(); z++ )
            {
                bool find = false;
                for ( QList<core::media::MediaFile*>::iterator i = shared.begin() ; i != shared.end(); i++ )
                {
                    if ( (*i)->getFullName() == (*z)->getFullName() )
                    {
                        find = true;
                        break;
                    }
                }
                if ( !find )
                    toAdd->append( (*z) );
            }
        }
        else
            toAdd = mediaList;

        for ( QList<core::media::MediaFile*>::iterator i = toAdd->begin() ; i != toAdd->end(); i++ )
        {
            this->myMediaList->addMedia( (*i) );
        }
        this->myMediaList->setCurrentItem( this->myMediaList->item( 0 ) );
    }

    delete sender();
}

void DlnaManager::addSharedMedia(QList<core::media::MediaFile *> *shared)
{
    if ( !shared->isEmpty() )
    {
        for ( QList<core::media::MediaFile*>::iterator i = shared->begin() ; i != shared->end(); i++ )
        {
            this->sharedMediaList->addMedia( (*i) );
        }
        this->sharedMediaList->setCurrentItem( this->myMediaList->item( 0 ) );
        this->setState( DlnaState::RUNNING );
    }

    core::service::FileListService* fileListService = new core::service::FileListService ( core::media::MediaType::MOVIE );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addMediaFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();

    fileListService = new core::service::FileListService ( core::media::MediaType::MUSIC );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addMediaFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();

    fileListService = new core::service::FileListService ( core::media::MediaType::IMAGE );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addMediaFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();
}
