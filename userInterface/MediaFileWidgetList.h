#ifndef MEDIAFILEWIDGETLIST_H
#define MEDIAFILEWIDGETLIST_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMap>
#include "userInterface/IconLoader.h"

#include "core/media/MediaFile.h"

namespace userInterface
{
    class MediaFileWidgetList : public QListWidget
    {

    private:
        QMap<QListWidgetItem*, core::media::MediaFile*>* index;

    protected:
        virtual QListWidgetItem *makeMediaFileWidgetListItem(core::media::MediaFile *file );

    public:
        MediaFileWidgetList( QWidget* parent = nullptr );
        ~MediaFileWidgetList();

        void addMedia (core::media::MediaFile* mediaFile );
        void deleteMedia (core::media::MediaFile* file );
        QList<core::media::MediaFile *> selectedMedia();
        QList<core::media::MediaFile *> getMediaFiles();
        void clear();
    };
}

#endif // MEDIAFILEWIDGETLIST_H
