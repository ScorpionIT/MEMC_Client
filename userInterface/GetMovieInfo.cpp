#include "GetMovieInfo.h"

using namespace userInterface;

GetMovieInfo::GetMovieInfo(QWidget *parent, core::media::MediaFile *mediaFile) : QWidget(parent)
{
    this->setWindowModality (Qt::WindowModal);
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog );
    this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    this->mainLayout = new QVBoxLayout();
    this->baseVLayout = new QVBoxLayout();
    this->baseHLayout = new QHBoxLayout();

    this->posterContainer = new QLabel();
    this->posterContainer->setPixmap( CoverLoader::getIstance()->getCover()->scaledToWidth( 150 ) );
    this->baseHLayout->addWidget( this->posterContainer );

    this->movieName = new QLineEdit( mediaFile->getName() );
    connect (this->movieName, SIGNAL( editingFinished() ), this, SLOT( findMovieInfo( ) ) );
    this->baseVLayout->addWidget( this->movieName );

    this->searchResult = new QListWidget();
    this->searchResult->setAlternatingRowColors( true );
    this->searchResult->setMinimumWidth( 450 );

    connect (this->searchResult, SIGNAL( itemSelectionChanged() ), this, SLOT( processSelectedMedia() ) );
    this->baseVLayout->addWidget( this->searchResult );

    this->buttonLayout = new QHBoxLayout();

    this->previousPageButton = new QPushButton ("Previous Page");
    this->previousPageButton->setEnabled( false );
    connect (this->previousPageButton, SIGNAL( clicked() ), this, SLOT( getPreviousPage() ) );
    this->buttonLayout->addWidget( this->previousPageButton );

    this->nextPageButton = new QPushButton ("Next Page");
    this->nextPageButton->setEnabled( false );
    connect (this->nextPageButton, SIGNAL( clicked() ), this, SLOT( getNextPage() ) );
    this->buttonLayout->addWidget( this->nextPageButton );

    this->title.setText("<b>Title: </b>");
    this->overview.setTextInteractionFlags( Qt::TextSelectableByMouse );
    this->overview.setAlignment( Qt::AlignJustify );
    this->overview.setMinimumHeight( 150 );
    this->overview.setMaximumHeight( 150 );
    this->overview.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->baseVLayout->addLayout( this->buttonLayout );
    this->baseHLayout->addLayout( this->baseVLayout );
    this->mainLayout->addLayout( this->baseHLayout );
    this->mainLayout->addWidget( new QLabel ( "<b>Title: </b>") );
    this->mainLayout->addWidget( &this->title );
    this->mainLayout->addWidget( new QLabel ( "<b>Overview: </b>") );
    this->mainLayout->addWidget( &this->overview );

    this->buttonLayout = new QHBoxLayout();
    this->closeButton = new QPushButton( "CLOSE");
    connect ( this->closeButton, SIGNAL( clicked() ), this, SLOT( hide() ) );
    this->buttonLayout->addWidget( this->closeButton );

    this->okButton = new QPushButton( "OK");
    connect (this->okButton, SIGNAL( clicked() ), this, SLOT( okPressed() ) );
    this->buttonLayout->addWidget( this->okButton );

    this->mainLayout->addLayout( this->buttonLayout );

    this->setLayout( this->mainLayout );

    this->lastPosterNetworkRequest = nullptr;
    this->lastOverviewNetworkRequest = nullptr;
    this->findMovieInfo();
}

GetMovieInfo::~GetMovieInfo()
{

}

void GetMovieInfo::findMovieInfo(int page)
{
    this->title.setText( "" );
    this->overview.setText( "" );
    QString query = this->movieName->text();
    if ( query.isEmpty() )
        return;

    QString apiKey = "57983e31fb435df4df77afb854740ea9";
    QNetworkAccessManager *findMovieRequest = new QNetworkAccessManager(this);
    connect( findMovieRequest, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( dataRecived( QNetworkReply* ) ) );
    findMovieRequest->get( QNetworkRequest( QUrl( "http://api.tmdb.org/3/search/multi?api_key=" + apiKey + "&query=" + query + "&language=en&page=" + QString::number( page ) ) ) );
}

void GetMovieInfo::dataRecived( QNetworkReply * recivedData )
{
    this->searchResult->clear();
    QJsonDocument data = QJsonDocument::fromJson( recivedData->readAll() );
    this->results = data.object()["results"].toArray();
    int totalPages = data.object()["total_pages"].toInt();
    this->currentPage = data.object()["page"].toInt();

    for ( int i = 0; i < results.count(); i++ )
    {
        QString title, releaseDate;
        if (results.at( i ).toObject()["media_type"].toString() == "tv")
        {
            title = results.at( i ).toObject()["original_name"].toString();
            releaseDate = results.at( i ).toObject()["first_air_date"].toString();
        }
        else if (results.at( i ).toObject()["media_type"].toString() == "movie")
        {
            title = results.at( i ).toObject()["original_title"].toString();
            releaseDate = results.at( i ).toObject()["release_date"].toString();
        }

        if ( !title.isEmpty() )
        {
            releaseDate= releaseDate.section("-", 0, -3);
            this->searchResult->insertItem( i, title + " - " + releaseDate );
        }
    }

    if ( totalPages > 1 )
    {
        if ( this->currentPage == totalPages )
        {
            this->nextPageButton->setEnabled( false );
            this->previousPageButton->setEnabled( true );
        }
        else if ( this->currentPage == 1 )
        {
            this->nextPageButton->setEnabled( true );
            this->previousPageButton->setEnabled( false );
        }
        else
        {
            this->nextPageButton->setEnabled( true );
            this->previousPageButton->setEnabled( true );
        }
    }
    else
    {
        this->nextPageButton->setEnabled( false );
        this->previousPageButton->setEnabled( false );
    }
}

void GetMovieInfo::posterRecived(QNetworkReply *recivedData)
{
    if ( recivedData->request() == *this->lastPosterNetworkRequest )
    {
        this->poster.loadFromData( recivedData->readAll() );
        if ( this->poster.isNull() )
            this->posterContainer->setPixmap( CoverLoader::getIstance()->getCover()->scaledToWidth( 150 ) );
        else
            this->posterContainer->setPixmap( this->poster.scaledToWidth( 150 ) );
    }
}

void GetMovieInfo::overviewRecived(QNetworkReply *recivedData)
{
    if ( recivedData->request() == *this->lastOverviewNetworkRequest )
    {
        QJsonDocument data = QJsonDocument::fromJson( recivedData->readAll() );
        QString recivedOverview = data.object()["overview"].toString();
        if ( recivedOverview.isEmpty() )
            this->overview.setText( "No info available" );
        else
            this->overview.setText( recivedOverview );
    }
}

void GetMovieInfo::processSelectedMedia()
{
    if ( this->searchResult->selectedItems().count() == 1)
    {
        this->posterContainer->setPixmap( CoverLoader::getIstance()->getCover("loading")->scaledToWidth( 150 ) );
        QListWidgetItem* item = this->searchResult->selectedItems().first();
        QString title = item->text().section(" - ", 0, -2);
        QString year = item->text().section(" - ", -1);
        QString tmpTitle;
        QString tmpYear;
        for ( int i = 0; i < this->results.count(); i++ )
        {
            if (results.at( i ).toObject()["media_type"].toString() == "tv")
            {
                tmpTitle = results.at( i ).toObject()["original_name"].toString();
                tmpYear = results.at( i ).toObject()["first_air_date"].toString().section("-", 0, -3);
            }
            else if (results.at( i ).toObject()["media_type"].toString() == "movie")
            {
                tmpTitle = results.at( i ).toObject()["original_title"].toString();
                tmpYear = results.at( i ).toObject()["release_date"].toString().section("-", 0, -3);
            }

            if ( tmpTitle == title && tmpYear == year )
            {
                QString id = QString::number( this->results.at( i ).toObject()["id"].toInt() );
                QString type = this->results.at( i ).toObject()["media_type"].toString();
                QString imgPath = this->results.at( i ).toObject()["poster_path"].toString();
                this->title.setText( title );

                // GET POSTER
                QNetworkAccessManager *posterRequestManager = new QNetworkAccessManager(this);
                connect( posterRequestManager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( posterRecived( QNetworkReply* ) ) );
                this->lastPosterNetworkRequest = new QNetworkRequest(QUrl("http://image.tmdb.org/t/p/w185"+imgPath));
                posterRequestManager->get( *this->lastPosterNetworkRequest );

                // GET OVERVIEW
                QNetworkAccessManager *overviewRequestManager = new QNetworkAccessManager(this);
                connect( overviewRequestManager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( overviewRecived( QNetworkReply* ) ) );
                this->lastOverviewNetworkRequest = new QNetworkRequest (QUrl("http://api.tmdb.org/3/" + type + "/" + id + "?api_key=57983e31fb435df4df77afb854740ea9&language=en"));
                overviewRequestManager->get( *this->lastOverviewNetworkRequest );
                break;
            }
        }
    }
}

void GetMovieInfo::getNextPage()
{
    findMovieInfo( this->currentPage + 1);
}

void GetMovieInfo::getPreviousPage()
{
    findMovieInfo( this->currentPage - 1);
}

void GetMovieInfo::okPressed()
{

}
