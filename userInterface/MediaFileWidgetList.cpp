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
    QListWidgetItem* item = this->MediaFileWidgetListItem( mediaFile );
    index->insert( item, mediaFile );
}

void MediaFileWidgetList::deleteMedia(core::media::MediaFile *file)
{
    for (QMap<QListWidgetItem*, core::media::MediaFile*>::iterator i = index->begin(); i != index->end(); i++)
    {
        if (i.value() == file)
        {
            delete i.key();
            return;
        }
    }
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
    return index->values();
}

void MediaFileWidgetList::clear()
{
    index->clear();
    QListWidget::clear();
}

QListWidgetItem *MediaFileWidgetList::MediaFileWidgetListItem( core::media::MediaFile* file )
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
