#ifndef MUSICMEDIAINFO_H
#define MUSICMEDIAINFO_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <userInterface/MPushButton.h>
#include <userInterface/MediaInfoView.h>
#include <userInterface/IconLoader.h>

namespace userInterface
{
    class MusicMediaInfo : public MediaInfoView
    {
        Q_OBJECT

    private:
        QString* fileName;
        QLabel* mediaLogo;
        MPushButton* playMediaButton;
        QHBoxLayout* hLayout;
        QVBoxLayout* vLayout;

    public:
        MusicMediaInfo();
        ~MusicMediaInfo();
        void setMedia(core::media::MediaFile *mediaFile);
    };
}

#endif // MUSICMEDIAINFO_H
