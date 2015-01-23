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
    QList<QListWidgetItem*> selected = this->myMediaList->selectedItems();
    for ( QList<QListWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++ )
    {
        this->myMediaList->takeItem( this->myMediaList->row( (*i) ));
        this->sharedMediaList->insertItem( this->sharedMediaList->count(), (*i) );
    }
}

void DlnaManager::removeFromSharedPressed()
{
    QList<QListWidgetItem*> selected = this->sharedMediaList->selectedItems();
    for ( QList<QListWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++ )
    {
        this->sharedMediaList->takeItem( this->sharedMediaList->row( (*i) ));
        this->myMediaList->insertItem( this->myMediaList->count(), (*i) );
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
    QMessageBox::warning( this, "Function not implemented", "Function not implemented yet", QMessageBox::Ok );
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
}

void DlnaManager::addDLNAFileList(QList<core::media::MediaFile*> *mediaList, QString response)
{
    if (response == "end")
    {
        for ( QList<core::media::MediaFile*>::iterator i = mediaList->begin() ; i != mediaList->end(); i++ )
            this->myMediaList->addMedia( (*i) );
        this->myMediaList->setCurrentItem( this->myMediaList->item( 0 ) );
    }
    delete sender();
}
