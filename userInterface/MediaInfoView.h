#ifndef MEDIAINFOVIEW_H
#define MEDIAINFOVIEW_H

#include <QWidget>


namespace userInterface
{
    class MediaInfoView : public QWidget
    {
        Q_OBJECT

    public:
        virtual void setMedia () = 0;
    };

}

#endif // MEDIAINFO_H
