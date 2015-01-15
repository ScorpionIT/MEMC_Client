#include "MediaFileUploadWidgetList.h"
#include <QDebug>

using namespace userInterface;

MediaFileUploadWidgetList::MediaFileUploadWidgetList(QWidget *parent ) : MediaFileWidgetList ( parent )
{
    this->setSelectionMode( QAbstractItemView::NoSelection);
}

QListWidgetItem *MediaFileUploadWidgetList::MediaFileWidgetListItem( core::MediaFile* file )
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

    mediaName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mediaName->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );

    if ( file->getType() == core::MediaType::MOVIE )
        typeIcon = QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png" );
    else if ( file->getType() == core::MediaType::MUSIC )
       typeIcon = ( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ) );
    else if ( file->getType() == core::MediaType::IMAGE )
       typeIcon = QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png" );

    typeIcon = typeIcon.scaledToHeight( 35 );
    fileTypeIcon->setPixmap( typeIcon );
    layout->addWidget( fileTypeIcon );
    layout->addWidget( mediaName );

    widget->setLayout( layout );

    this->setItemWidget( item, widget );
    return item;
}
