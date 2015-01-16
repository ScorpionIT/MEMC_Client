#ifndef MEDIAFILEUPLOADWIDGETLIST_H
#define MEDIAFILEUPLOADWIDGETLIST_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include "userInterface/MediaFileWidgetList.h"
#include "core/media/MediaFile.h"

namespace userInterface
{
    class MediaFileUploadWidgetList : public MediaFileWidgetList
    {

    private:
        virtual QListWidgetItem *MediaFileWidgetListItem( core::media::MediaFile *file );

    public:
        MediaFileUploadWidgetList( QWidget* parent = nullptr );

    };
}

#endif // MEDIAFILEUPLOADWIDGETLIST_H
