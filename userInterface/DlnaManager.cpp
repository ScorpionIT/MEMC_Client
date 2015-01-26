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
    connect (this->addToSharedButton, SIGNAL( clicked() ), this, SLOT( addToSharedPressed() ) );

    this->removeFromSharedButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::DEL), "Remove from shared");
    connect ( this->removeFromSharedButton, SIGNAL( clicked() ), this, SLOT( removeFromSharedPressed() ) );

    this->cleanAndUpdateButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::CLEAN), "Clean and reload\n my media list");
    connect ( this->cleanAndUpdateButton, SIGNAL( clicked() ), this, SLOT( cleanAndUpdatePressed() ) );

    this->confirmDlnaShareButton = new MPushButton (IconLoader::getIstance()->getIcon(IconLoader::DLNA_COLOR), "Share with DLNA");
    connect( this->confirmDlnaShareButton, SIGNAL( clicked() ), this, SLOT( confirmDlnaSharePressed() ) );

    this->buttonLayout->addWidget( new Spacer( this, SpacerOrientation::VERTICAL ) );
    this->buttonLayout->addWidget( this->addToSharedButton, 0, Qt::AlignVCenter);
    this->buttonLayout->addWidget( this->removeFromSharedButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( this->cleanAndUpdateButton, 0, Qt::AlignVCenter );
    this->buttonLayout->addWidget( this->confirmDlnaShareButton, 0, Qt::AlignVCenter );
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

void DlnaManager::confirmDlnaSharePressed()
{
    core::service::DlnaService* dlnaService = new core::service::DlnaService(this->sharedMediaList->getMediaFiles(), core::service::DLNAOperation::NEWSHARE );
    connect (dlnaService, SIGNAL( finish(QString) ), this, SLOT( dlnaServiceResponse(QString) ));
    dlnaService->start();
}

void DlnaManager::dlnaServiceResponse(QString message)
{
    if (message != "ok")
        QMessageBox::critical( this, "Server error", message, QMessageBox::Ok );
}

void DlnaManager::loadMediaList()
{
    core::service::FileListService* fileListService = new core::service::FileListService ( core::media::MediaType::MOVIE );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addDLNAFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();

    fileListService = new core::service::FileListService ( core::media::MediaType::MUSIC );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addDLNAFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();

    fileListService = new core::service::FileListService ( core::media::MediaType::IMAGE );
    connect( fileListService, SIGNAL( finish( QList<core::media::MediaFile*>*,QString ) ), this, SLOT( addDLNAFileList( QList<core::media::MediaFile*>*,QString ) ) );
    fileListService->start();

    core::service::DlnaService* dlnaService = new core::service::DlnaService(this->sharedMediaList->getMediaFiles(), core::service::DLNAOperation::SHARESTATUS );
    connect (dlnaService, SIGNAL( shareStatus(QList<core::media::MediaFile*>*) ), this, SLOT( addSharedMedia(QList<core::media::MediaFile*>*) ) );
    connect (dlnaService, SIGNAL( finish(QString) ), this, SLOT( dlnaServiceResponse(QString) ));
    dlnaService->start();
}

void DlnaManager::addDLNAFileList(QList<core::media::MediaFile*> *mediaList, QString response )
{
    if (response == "end")
    {
        for ( QList<core::media::MediaFile*>::iterator i = mediaList->begin() ; i != mediaList->end(); i++ )
            this->myMediaList->addMedia( (*i) );
        this->myMediaList->setCurrentItem( this->myMediaList->item( 0 ) );
    }
    delete sender();
}

void DlnaManager::addSharedMedia(QList<core::media::MediaFile *> *shared)
{
    qDebug() << "ESEGUI";
    qDebug() << shared->count();
    if ( !shared->isEmpty() )
    {
        for ( QList<core::media::MediaFile*>::iterator i = shared->begin() ; i != shared->end(); i++ )
            this->sharedMediaList->addMedia( (*i) );
        this->sharedMediaList->setCurrentItem( this->myMediaList->item( 0 ) );
    }
}
