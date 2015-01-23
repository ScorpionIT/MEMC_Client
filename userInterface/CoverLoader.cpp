#include "CoverLoader.h"

using namespace userInterface;

CoverLoader* CoverLoader::istance = nullptr;

CoverLoader::CoverLoader() : QObject( nullptr )
{
    this->covers["loading"] = new QPixmap ( this->COVERPATH + "loading-poster.jpg" );
}

CoverLoader *CoverLoader::getIstance()
{
    if ( istance == nullptr )
        istance = new CoverLoader();

    return istance;

}

QPixmap *CoverLoader::getCover(QString cover)
{
    if (this->covers.contains( cover ))
        return this->covers[cover];
    else
        return new QPixmap ( this->COVERPATH + "no-poster.jpg");
}
