#include "IconLoader.h"

using namespace userInterface;

IconLoader* IconLoader::istance = nullptr;

IconLoader::IconLoader()
{
    this->icons[IconLoader::MOVIE] = new QPixmap( ICONPATH + "movie.png" );
    this->icons[IconLoader::MUSIC] = new QPixmap( ICONPATH + "music.png" );
    this->icons[IconLoader::IMAGE] = new QPixmap( ICONPATH + "pictures.png" );
    this->icons[IconLoader::PLAYER] = new QPixmap( ICONPATH + "player.png" );
    this->icons[IconLoader::DEL] = new QPixmap( ICONPATH + "delete.png" );
    this->icons[IconLoader::LOCK] = new QPixmap( ICONPATH + "lock.png" );
    this->icons[IconLoader::UNLOCK] = new QPixmap( ICONPATH + "unlock.png" );
    this->icons[IconLoader::LIBRARY] = new QPixmap( ICONPATH + "library.png" );
    this->icons[IconLoader::BROWSE] = new QPixmap( ICONPATH + "filemanager.png" );
    this->icons[IconLoader::CLEAN] = new QPixmap( ICONPATH + "clean.png" );
    this->icons[IconLoader::UPLOAD] = new QPixmap( ICONPATH + "upload.png" );
    this->icons[IconLoader::SETTINGS] = new QPixmap( ICONPATH + "settings.png" );
    this->icons[IconLoader::DLNA_GREY] = new QPixmap( ICONPATH + "dlnagrey.png" );
    this->icons[IconLoader::DLNA_GREEN] = new QPixmap( ICONPATH + "dlnagreen.png" );
    this->icons[IconLoader::DLNA_RED] = new QPixmap( ICONPATH + "dlnared.png" );
}

IconLoader::~IconLoader()
{

}

IconLoader *IconLoader::getIstance()
{
    if( istance == nullptr )
    {
        istance =  new IconLoader();
    }

    return istance;
}

QPixmap IconLoader::getIcon(IconLoader::Icon icon)
{
    return *this->icons.value( icon );
}
