#ifndef MEDIAFILEWIDGETLIST_H
#define MEDIAFILEWIDGETLIST_H

#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QMap>

#include "core/MediaFile.h"

namespace userInterface
{
    class MediaFileWidgetList : public QListWidget
    {

    private:
        QMap<QListWidgetItem*, core::MediaFile*>* index;

    protected:
        virtual QListWidgetItem *MediaFileWidgetListItem(core::MediaFile *file );

    public:
        MediaFileWidgetList( QWidget* parent = nullptr );
        ~MediaFileWidgetList();

        void addMedia (core::MediaFile* file );
        void deleteMedia (core::MediaFile* file );

        QList<core::MediaFile *> getMediaFiles();
        void clear();
    };
}

#endif // MEDIAFILEWIDGETLIST_H
