#include "MediaFileUploadWidgetList.h"
#include <QDebug>

using namespace userInterface;

MediaFileUploadWidgetList::MediaFileUploadWidgetList(QWidget *parent ) : MediaFileWidgetList ( parent )
{
    this->setSelectionMode( QAbstractItemView::NoSelection);
}

QProgressBar *MediaFileUploadWidgetList::getMediaProgressBar(core::media::MediaFile *mediaFile)
{
    return this->progressBars.value( mediaFile );
}

QListWidgetItem *MediaFileUploadWidgetList::makeMediaFileWidgetListItem( core::media::MediaFile* file )
{
    QListWidgetItem* item = new QListWidgetItem( "", this );
    QSize tmp = item->sizeHint();
    tmp.setHeight( 50 );
    item->setSizeHint( tmp );

    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* fileTypeIcon = new QLabel();
    QPixmap typeIcon;
    QLabel* mediaName = new QLabel( file->getName() );
    QProgressBar* progressBar = new QProgressBar();

    this->progressBars.insert( file, progressBar );

    mediaName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaName->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );

    if ( file->getType() == core::media::MediaType::MOVIE )
        typeIcon = IconLoader::getIstance()->getIcon(IconLoader::MOVIE);
    else if ( file->getType() == core::media::MediaType::MUSIC )
       typeIcon = IconLoader::getIstance()->getIcon(IconLoader::MUSIC);
    else if ( file->getType() == core::media::MediaType::IMAGE )
       typeIcon = IconLoader::getIstance()->getIcon(IconLoader::IMAGE);

    typeIcon = typeIcon.scaledToHeight( 35 );
    fileTypeIcon->setPixmap( typeIcon );
    layout->addWidget( fileTypeIcon );
    layout->addWidget( mediaName );
    layout->addWidget( progressBar );

    widget->setLayout( layout );

    this->setItemWidget( item, widget );
    return item;
}
