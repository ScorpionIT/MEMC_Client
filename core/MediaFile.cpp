#include "core/MediaFile.h"

using namespace core;

MediaFile::MediaFile(QString name, MediaType type)
{
    this->local = false;
    this->name = name;
    this->type = type;
}

MediaFile::MediaFile(QString filepath)
{
    QFileInfo info( filepath );
    this->local = true;
    this->name = info.completeBaseName();
    this->fullName = info.fileName();
    this->path = info.absoluteFilePath();
    this->type = recognizeType(info.suffix());
}

MediaType MediaFile::recognizeType( QString extension )
{
    if ( extension ==  "mkv" || extension ==  "avi")
        return MediaType::MOVIE;
    else if ( extension ==  "mp3" || extension ==  "wav")
        return MediaType::MUSIC;
}

QString MediaFile::getName()
{
    return this->name;
}

QString MediaFile::getFullName()
{
    if (!local)
        return QString();

    return this->fullName;
}

QString MediaFile::getFullPath()
{
    if (!local)
        return QString();

    return this->path;
}

MediaType MediaFile::getType()
{
    return this->type;
}

MediaFile::~MediaFile()
{

}
