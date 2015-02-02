#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <vlc-qt/Instance.h>
#include <vlc-qt/Common.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/MediaPlayer.h>
#include <vlc-qt/WidgetVideo.h>
#include <vlc-qt/WidgetSeek.h>
#include <vlc-qt/WidgetVolumeSlider.h>

#include "userInterface/MPushButton.h"
#include "userInterface/Spacer.h"
#include "core/media/MediaFile.h"
#include "core/network/Session.h"

namespace userInterface
{
    class MediaPlayerWidget : public QWidget
    {
        Q_OBJECT

    private:
        QVBoxLayout *mainLayout;
        QHBoxLayout *controlsLayout;
        QPushButton *playPauseButton;
        QPushButton *stopButton;
        VlcInstance *vlcInstance;
        VlcMediaPlayer *vlcPlayer;
        VlcWidgetVideo *videoWidget;
        VlcWidgetSeek *seekWidget;
        VlcWidgetVolumeSlider *volumeSlider;
        VlcMedia *media;

    public:
        MediaPlayerWidget(QWidget *parent = 0);
        ~MediaPlayerWidget();

    public slots:
        void setMedia( core::media::MediaFile *mediaFile );

    private slots:
        void playPausePressed ();

    };
}

#endif // MEDIAPLAYER_H
