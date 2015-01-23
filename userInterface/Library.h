#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "MPushButton.h"

#include <userInterface/MediaFileWidgetList.h>
#include <userInterface/MusicMediaInfo.h>
#include <userInterface/MovieMediaInfoWidget.h>
#include <userInterface/MediaInfoView.h>
#include <userInterface/IconLoader.h>

#include "core/media/MediaFile.h"
#include "core/service/FileListService.h"
#include "core/service/FileManagerService.h"

namespace userInterface
{
    class Library : public QWidget
    {
        Q_OBJECT

    private:
        MPushButton* movieButton;
        MPushButton* musicButton;
        MPushButton* imageButton;
        MPushButton* deleteMediaButton;
        MPushButton* toPublicButton;
        MPushButton* toPrivateButton;
        MediaFileWidgetList* mediaList;
        QHBoxLayout* buttonsLayout;
        QHBoxLayout* mediaButtonLayout;
        QHBoxLayout* mediaHLayout;
        QVBoxLayout* mediaVLayout;
        QVBoxLayout* vLayout;
        MediaInfoView* mediaInfo;
        core::media::MediaType currentMediaSection;
        void setMediaInfoWidget (MediaInfoView* mediaInfoView);
        void loadMediaList ();

    public:
        Library(QWidget *parent = 0);
        ~Library();

    signals:

    private slots:
        void addFileList(QList<core::media::MediaFile*>* mediaList, QString response);
        void movieButtonPressed();
        void musicButtonPressed();
        void imageButtonPressed();
        void deleteMediaPressed();
        void toPrivatePressed();
        void toPublicPressed();
        void mediaSelected();
        void serviceResponse( QString response );
    };
}

#endif // FILEMANAGER_H
