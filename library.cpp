#include "library.h"
Library::Library(Connection *conn, QWidget *parent) : QWidget(parent)
{
    this->connection = conn;
    this->buttonsLayout = new QHBoxLayout();
    this->movieButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png" ), "MOVIES" );
    connect ( this->movieButton, SIGNAL( clicked() ), this, SLOT( movieButtonPressed() ) );

    this->musicButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png" ), "MUSIC" );
    connect ( this->musicButton, SIGNAL( clicked() ), this, SLOT( musicButtonPressed() ) );

    this->imageButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png" ), "IMAGES" );
    connect ( this->imageButton, SIGNAL( clicked() ), this, SLOT( imageButtonPressed() ) );

    this->buttonsLayout->addWidget( this->movieButton );
    this->buttonsLayout->addWidget( this->musicButton );
    this->buttonsLayout->addWidget( this->imageButton );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->buttonsLayout);

    this->fileList = new QListWidget();
    this->vLayout->addWidget( this->fileList );

    this->setLayout(vLayout);
    this->movieButtonPressed();
}

Library::~Library()
{

}

void Library::loadFileList(QStringList *fileList, QString response)
{
    if (response == "end")
    {
        for (int i = 0; i < fileList->size(); i++ )
            new QListWidgetItem( fileList->at( i ), this->fileList );
        delete fileList;
    }
    delete sender();
}

void Library::movieButtonPressed()
{
    this->movieButton->setEnabled( false );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( true );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/movie.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");
    this->fileList->clear();
    this->fileService = new FileService (FileType::MOVIE, "127.0.0.1", "80001", "Elia", this->connection->getSessionID());
    connect( this->fileService, SIGNAL( finish(QStringList*,QString) ), this, SLOT( loadFileList(QStringList*,QString) ) );
    this->fileService->start();
}

void Library::musicButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( false );
    this->imageButton->setEnabled( true );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/music.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");

    this->fileList->clear();
    this->fileService = new FileService (FileType::MUSIC, "127.0.0.1", "80001", "Elia", this->connection->getSessionID());
    connect( this->fileService, SIGNAL( finish(QStringList*,QString) ), this, SLOT( loadFileList(QStringList*,QString) ) );
    this->fileService->start();
}

void Library::imageButtonPressed()
{
    this->movieButton->setEnabled( true );
    this->musicButton->setEnabled( true );
    this->imageButton->setEnabled( false );
    this->fileList->setStyleSheet("background-image: url("+QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/pictures.png); "
                                "background-position: bottom right; "
                                "background-repeat: no-repeat;"
                                "background-color: white;");

    this->fileList->clear();
    this->fileService = new FileService (FileType::IMAGE, "127.0.0.1", "80001", "Elia", this->connection->getSessionID());
    connect( this->fileService, SIGNAL( finish(QStringList*,QString) ), this, SLOT( loadFileList(QStringList*,QString) ) );
    this->fileService->start();
}

