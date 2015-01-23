#ifndef MIXEDMEDIAFILEWIDGETLIST_H
#define MIXEDMEDIAFILEWIDGETLIST_H

#include "userInterface/MediaFileWidgetList.h"

namespace userInterface
{
    class MixedMediaFileWidgetList : public MediaFileWidgetList
    {

    private:

    protected:
        virtual QListWidgetItem *makeMediaFileWidgetListItem( core::media::MediaFile *file );


    public:
        MixedMediaFileWidgetList();
        ~MixedMediaFileWidgetList();

    };
}

#endif // MIXEDMEDIAFILEWIDGETLIST_H
