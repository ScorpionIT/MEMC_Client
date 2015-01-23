#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QPixmap>
#include <QMap>
#include <QDir>

namespace userInterface
{
    class IconLoader
    {

    public:
        enum Icon {MOVIE = 0, MUSIC, IMAGE, DEL, LOCK, UNLOCK, LIBRARY, BROWSE, UPLOAD, CLEAN, SETTINGS, DLNA, DLNA_COLOR  };
        static IconLoader* getIstance();
        QPixmap getIcon(Icon icon);

    private:
        static IconLoader* istance;
        const QString ICONPATH = QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/";
        IconLoader();
        ~IconLoader();
        QMap<Icon, QPixmap*> icons;
    };
}

#endif // ICONLOADER_H
