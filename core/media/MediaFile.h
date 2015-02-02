#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QString>
#include <QStringList>
#include <QFileInfo>

namespace core
{
    namespace media
    {
        enum MediaType {INVALIDMEDIA = 0, MUSIC, MOVIE, IMAGE };

        class MediaFile
        {

        private:
            QString name;
            QString fullName;
            QString path;
            MediaType type;
            bool local;
            bool publicMedia;
            MediaType recognizeType(QString extension);

        public:
            MediaFile(QString serverString, MediaType type, bool manualInsert = false);
            MediaFile(QString filepath);
            MediaFile();
            QString getName();
            QString getFullName();
            QString getFullPath();
            MediaType getType();
            bool isPublic();
            void setPublic ( bool publicMedia );
            ~MediaFile();
        };
    }
}

#endif // MEDIAFILE_H
