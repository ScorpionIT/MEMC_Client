#ifndef MEDIAINFOVIEW_H
#define MEDIAINFOVIEW_H

#include <QWidget>

#include "core/media/MediaFile.h"

namespace userInterface
{
    class MediaInfoView : public QWidget
    {
        Q_OBJECT

    public:
        virtual void setMedia ( core::media::MediaFile* mediaFile ) = 0;
    };

}

#endif // MEDIAINFO_H
