#ifndef MUSICMEDIAINFO_H
#define MUSICMEDIAINFO_H

#include <QDir>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <userInterface/MPushButton.h>

namespace userInterface
{
    class MusicMediaInfo : public QWidget
    {
        Q_OBJECT

    private:
        QString* fileName;
        QLabel* mediaLogo;
        MPushButton* deleteMediaButton;
        QHBoxLayout* hLayout;
        QVBoxLayout* vLayout;

    public:
        MusicMediaInfo();
        ~MusicMediaInfo();
    };
}

#endif // MUSICMEDIAINFO_H
