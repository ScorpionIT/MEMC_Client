#ifndef MOVIEMEDIAINFO_H
#define MOVIEMEDIAINFO_H

#include <QString>
#include <QPixmap>

namespace core
{
    namespace media
    {
        class MovieMediaInfo
        {
        private:
            QString title;
            QString duration;
            QString description;
            QPixmap cover;
            QPixmap fanArt;

        public:
            MovieMediaInfo();
            ~MovieMediaInfo();

        };
    }
}


#endif // MOVIEMEDIAINFO_H
