#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "MPushButton.h"
#include "core/Connection.h"
#include "core/FileService.h"
#include <userInterface/MusicMediaInfo.h>

namespace userInterface
{
    class Library : public QWidget
    {
        Q_OBJECT

    private:
        MPushButton* movieButton;
        MPushButton* musicButton;
        MPushButton* imageButton;
        QListWidget* fileList;
        QHBoxLayout* buttonsLayout;
        QHBoxLayout* hLayout;
        QVBoxLayout* vLayout;
        core::FileService* fileService;
        core::Connection* connection;

    public:
        Library(core::Connection* conn, QWidget *parent = 0);
        ~Library();

    signals:

    private slots:
        void loadFileList( QStringList* fileList, QString response );
        void movieButtonPressed();
        void musicButtonPressed();
        void imageButtonPressed();
    };
}

#endif // FILEMANAGER_H
