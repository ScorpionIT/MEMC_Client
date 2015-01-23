#ifndef MEDIAFILEUPLOADWIDGETLIST_H
#define MEDIAFILEUPLOADWIDGETLIST_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QMap>
#include "userInterface/MediaFileWidgetList.h"
#include "core/media/MediaFile.h"

namespace userInterface
{
    class MediaFileUploadWidgetList : public MediaFileWidgetList
    {

    private:
        virtual QListWidgetItem *makeMediaFileWidgetListItem( core::media::MediaFile *file );
        QMap<core::media::MediaFile*, QProgressBar*> progressBars;

    public:
        MediaFileUploadWidgetList( QWidget* parent = nullptr );
        QProgressBar* getMediaProgressBar (core::media::MediaFile *mediaFile );

    };
}

#endif // MEDIAFILEUPLOADWIDGETLIST_H
