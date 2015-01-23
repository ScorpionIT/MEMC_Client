#ifndef COVERLOADER_H
#define COVERLOADER_H

#include <QObject>
#include <QPixmap>
#include <QMap>
#include <QDir>

namespace userInterface
{
    class CoverLoader : public QObject
    {
        Q_OBJECT

    private:
         static CoverLoader* istance;
         QMap<QString, QPixmap*> covers;
         CoverLoader();

    public:
        static CoverLoader* getIstance();
        const QString COVERPATH = QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/";
        QPixmap* getCover( QString cover = "" );

    signals:

    public slots:

    };
}

#endif // COVERLOADER_H
