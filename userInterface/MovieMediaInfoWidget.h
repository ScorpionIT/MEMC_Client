#ifndef MOVIEMEDIAINFOWIDGET_H
#define MOVIEMEDIAINFOWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "userInterface/MediaInfoView.h"
#include "userInterface/MPushButton.h"
#include "userInterface/IconLoader.h"
#include "userInterface/Spacer.h"
#include "userInterface/FilmCoverUploader.h"

namespace userInterface
{
    class MovieMediaInfoWidget : public MediaInfoView
    {
        Q_OBJECT

    private:
        QLabel* title;
        QLabel* description;
        QPushButton* mediaLogo;
        MPushButton* editMediaInfoButton;
        QHBoxLayout* hLayout;
        QVBoxLayout* vLayout;
        GetMovieInfo* getMovieInfo;
        core::media::MediaFile* mediaFile;

    public:
        MovieMediaInfoWidget();
        ~MovieMediaInfoWidget();
        virtual void setMedia (core::media::MediaFile *mediaFile);

    private slots:
        void editMediaInfoPressed();

    };
}

#endif // MOVIEMEDIAINFOWIDGET_H
