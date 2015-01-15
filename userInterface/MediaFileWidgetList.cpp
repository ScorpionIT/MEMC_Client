#include "MediaFileWidgetList.h"
#include <QDebug>

using namespace userInterface;

MediaFileWidgetList::MediaFileWidgetList(QWidget *parent ) : QListWidget ( parent )
{
    this->setAlternatingRowColors( true );
    this->setSelectionMode( QAbstractItemView::SingleSelection);

    index = new QMap<QListWidgetItem*, core::MediaFile*>;
}

MediaFileWidgetList::~MediaFileWidgetList()
{
    delete index; // SE VABBÈ!
}

void MediaFileWidgetList::addMedia(core::MediaFile* file )
{
    QListWidgetItem* item = this->MediaFileWidgetListItem( file );
    index->insert( item, file );
}

void MediaFileWidgetList::deleteMedia(core::MediaFile *file)
{
    for (QMap<QListWidgetItem*, core::MediaFile*>::iterator i = index->begin(); i != index->end(); i++)
    {
        if (i.value() == file)
        {
            delete i.key();
            return;
        }
    }
}

QList<core::MediaFile *> MediaFileWidgetList::getMediaFiles()
{
    return index->values();
}

void MediaFileWidgetList::clear()
{
    index->clear();
    QListWidget::clear();
}

QListWidgetItem *MediaFileWidgetList::MediaFileWidgetListItem( core::MediaFile* file )
{
    QListWidgetItem* item = new QListWidgetItem( file->getName(), this );
    QSize tmp = item->sizeHint();
    tmp.setHeight( 50 );
    item->setSizeHint( tmp );
    return item;
}
