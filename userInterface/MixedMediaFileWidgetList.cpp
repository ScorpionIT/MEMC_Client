#include "MixedMediaFileWidgetList.h"

using namespace userInterface;

MixedMediaFileWidgetList::MixedMediaFileWidgetList()
{

}

MixedMediaFileWidgetList::~MixedMediaFileWidgetList()
{

}

QListWidgetItem *userInterface::MixedMediaFileWidgetList::makeMediaFileWidgetListItem( core::media::MediaFile *file )
{
    QListWidgetItem* item = new QListWidgetItem( file->getName(), this );

    if ( file->getType() == core::media::MOVIE )
        item->setIcon( IconLoader::getIstance()->getIcon(IconLoader::MOVIE) );
    else if ( file->getType() == core::media::MUSIC)
        item->setIcon( IconLoader::getIstance()->getIcon(IconLoader::MUSIC) );
    else if ( file->getType() == core::media::IMAGE )
        item->setIcon( IconLoader::getIstance()->getIcon(IconLoader::IMAGE) );

    QSize tmp = item->sizeHint();
    tmp.setHeight( 50 );
    item->setSizeHint( tmp );
    return item;
}
