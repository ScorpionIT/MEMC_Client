#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "MPushButton.h"
#include <userInterface/MediaFileWidgetList.h>
#include <userInterface/MusicMediaInfo.h>
#include "core/FileService.h"
#include "core/MediaFile.h"

namespace userInterface
{
    class Library : public QWidget
    {
        Q_OBJECT

    private:
        MPushButton* movieButton;
        MPushButton* musicButton;
        MPushButton* imageButton;
        MediaFileWidgetList* mediaList;
        QHBoxLayout* buttonsLayout;
        QHBoxLayout* hLayout;
        QVBoxLayout* vLayout;
        core::FileService* fileService;

    public:
        Library(QWidget *parent = 0);
        ~Library();

    signals:

    private slots:
        void loadFileList(QList<core::MediaFile*>* mediaList, QString response);
        void movieButtonPressed();
        void musicButtonPressed();
        void imageButtonPressed();
    };
}

#endif // FILEMANAGER_H
