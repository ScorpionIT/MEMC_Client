#include "MediaFileWidgetList.h"
#include <QDebug>

using namespace userInterface;

MediaFileWidgetList::MediaFileWidgetList(QWidget *parent ) : QListWidget ( parent )
{
    this->setAlternatingRowColors( true );
    this->setSelectionMode( QAbstractItemView::ExtendedSelection);

    index = new QMap<QListWidgetItem*, core::media::MediaFile*>;
}

MediaFileWidgetList::~MediaFileWidgetList()
{
    delete index; // SE VABBÈ!
}

void MediaFileWidgetList::addMedia(core::media::MediaFile* mediaFile )
{
    QListWidgetItem* item = this->makeMediaFileWidgetListItem( mediaFile );
    index->insert( item, mediaFile );
}

void MediaFileWidgetList::deleteMedia(core::media::MediaFile *file)
{
    QListWidgetItem* item = index->key (file);
    this->removeItemWidget( item );
    this->takeItem( this->row ( item ) );
}

QList<core::media::MediaFile*> MediaFileWidgetList::selectedMedia()
{
    QList<QListWidgetItem*> items = this->selectedItems();
    QList<core::media::MediaFile*> selectedMediaFiles;

    for ( QList<QListWidgetItem*>::iterator i = items.begin(); i != items.end(); i++ )
            selectedMediaFiles.append( this->index->value(*i) );

    return selectedMediaFiles;
}

QList<core::media::MediaFile *> MediaFileWidgetList::getMediaFiles()
{
    QList<core::media::MediaFile*> mediaFiles;
    for ( int i = 0; i < this->count(); i++ )
        mediaFiles.append( this->index->value( this->item( i ) ) );

    return mediaFiles;
}

void MediaFileWidgetList::clear()
{
    index->clear();
    QListWidget::clear();
}

QListWidgetItem *MediaFileWidgetList::makeMediaFileWidgetListItem( core::media::MediaFile* file )
{
    QListWidgetItem* item = new QListWidgetItem( file->getName(), this );;
    if ( file->isPublic() )
        item->setIcon( IconLoader::getIstance()->getIcon(IconLoader::UNLOCK) );
    else
        item->setIcon( IconLoader::getIstance()->getIcon(IconLoader::LOCK) );

    QSize tmp = item->sizeHint();
    tmp.setHeight( 50 );
    item->setSizeHint( tmp );
    return item;
}
