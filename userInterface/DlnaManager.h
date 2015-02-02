#ifndef DLNAMANAGER_H
#define DLNAMANAGER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "userInterface/MixedMediaFileWidgetList.h"
#include "userInterface/MPushButton.h"
#include "userInterface/Spacer.h"

#include "core/service/FileListService.h"
#include "core/service/DlnaService.h"
#include "core/media/MediaFile.h"

namespace userInterface
{
    enum DlnaState { RUNNING, STOPPED, UPDATESTATE };

    class DlnaManager : public QWidget
    {
        Q_OBJECT

    private:
        MixedMediaFileWidgetList* myMediaList;
        MixedMediaFileWidgetList* sharedMediaList;
        MPushButton* addToSharedButton;
        MPushButton* removeFromSharedButton;
        MPushButton* cleanAndUpdateButton;
        MPushButton* startDlnaShareButton;
        MPushButton* stopDlnaShareButton;
        QHBoxLayout* mainLayout;
        QVBoxLayout* buttonLayout;
        QVBoxLayout* supportLayout;
        QLabel* supportLabel;
        DlnaState shareStatus;
        bool waitShared;
        void loadMediaList();
        void setState (DlnaState state);

    public:
        DlnaManager(QWidget *parent = 0);
        ~DlnaManager();

    signals:

    private slots:
        void addMediaFileList( QList<core::media::MediaFile*> *mediaList, QString response );
        void addSharedMedia (QList<core::media::MediaFile *> *shared );
        void addToSharedPressed();
        void removeFromSharedPressed();
        void cleanAndUpdatePressed();
        void startDlnaSharePressed();
        void stopDlnaSharePressed();
        void dlnaServiceResponse( QString message );
    };
}

#endif // DLNAMANAGER_H
