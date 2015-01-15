#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QObject>
#include <QString>
#include <QFileInfo>

namespace core
{
    enum MediaType { MUSIC = 1, MOVIE, IMAGE };

    class MediaFile : public QObject
    {
        Q_OBJECT

    private:
        QString name;
        QString fullName;
        QString path;
        MediaType type;
        bool local;
        MediaType recognizeType(QString extension);

    public:
        MediaFile(QString name, MediaType type);
        MediaFile(QString filepath);
        QString getName();
        QString getFullName();
        QString getFullPath();
        MediaType getType();
        ~MediaFile();

    signals:

    public slots:

    };
}

#endif // MEDIAFILE_H
