#ifndef GETMOVIEINFO_H
#define GETMOVIEINFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidget>
#include <QListWidgetItem>
#include "core/media/MediaFile.h"
#include "userInterface/CoverLoader.h"

namespace userInterface
{
    class GetMovieInfo : public QWidget
    {
        Q_OBJECT

    private:
        QVBoxLayout* mainLayout;
        QVBoxLayout* baseVLayout;
        QHBoxLayout* baseHLayout;
        QHBoxLayout* buttonLayout;
        QPushButton* okButton;
        QPushButton* closeButton;
        QPushButton* nextPageButton;
        QPushButton* previousPageButton;
        QListWidget* searchResult;
        QLineEdit* movieName;
        QLabel* posterContainer;
        QJsonArray results;
        QNetworkRequest *lastPosterNetworkRequest;
        QNetworkRequest *lastOverviewNetworkRequest;
        QPixmap poster;
        QLabel title;
        QTextEdit overview;
        int currentPage;

    public:
        GetMovieInfo( QWidget* parent,  core::media::MediaFile* mediaFile );
        ~GetMovieInfo();

    signals:


    private slots:
        void findMovieInfo(int page = 1);
        void dataReceived(QNetworkReply* recivedData);
        void posterReceived(QNetworkReply* recivedData);
        void overviewReceived(QNetworkReply* recivedData);
        void processSelectedMedia();
        void getNextPage();
        void getPreviousPage();
        void okPressed();
    };
}

#endif // GETMOVIEINFO_H
