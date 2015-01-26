#include "core/media/MediaFile.h"

using namespace core;
using namespace media;

MediaFile::MediaFile(QString serverString, MediaType type)
{
    QStringList serverData = serverString.split( "$" );
    if (serverData.count() == 2)
    {
        this->name = serverData[0].section( ".", 0, -2  );
        this->fullName = serverData[0];
        if (serverData[1] == "public")
            this->publicMedia = true;
        else
            this->publicMedia = false;

        this->type = type;
        this->local = false;
    }
    else
    {
        this->name = "";
        this->fullName = "";
        this->publicMedia = false;
        this->type = MediaType::INVALIDMEDIA;
        this->local = false;
    }
}

MediaFile::MediaFile(QString filepath)
{
    QFileInfo info( filepath );
    this->local = true;
    this->name = info.completeBaseName();
    this->fullName = info.fileName();
    this->path = info.absoluteFilePath();
    this->type = recognizeType(info.suffix());
    this->publicMedia = false;
}

MediaFile::MediaFile()
{
    this->type = MediaType::INVALIDMEDIA;
    this->local = false;
    this->publicMedia = false;
}

MediaType MediaFile::recognizeType( QString extension )
{
    if ( extension ==  "mkv" || extension ==  "avi")
        return MediaType::MOVIE;
    else if ( extension ==  "mp3" || extension ==  "wav")
        return MediaType::MUSIC;
    else
        return MediaType::INVALIDMEDIA;
}

QString MediaFile::getName()
{
    return this->name;
}

QString MediaFile::getFullName()
{
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

bool MediaFile::isPublic()
{
    return this->publicMedia;
}

void MediaFile::setPublic(bool publicMedia)
{
    this->publicMedia = publicMedia;
}

MediaFile::~MediaFile()
{

}
