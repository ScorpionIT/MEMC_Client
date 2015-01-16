#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include "core/media/MediaFile.h"

namespace core
{
    namespace media
    {
        class MediaInfo
        {

        public:
            MediaInfo( MediaFile* mediaFile );
            ~MediaInfo();

        };
    }
}

#endif // MEDIAINFO_H
