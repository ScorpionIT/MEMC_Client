#include "MainWindow.h"
#include <QMenu>

using namespace userInterface;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle( "MEMC - Client");
    this->resize( 800, 600);
    this->connection = nullptr;
    this->library = nullptr;
    this->fileUploader = nullptr;
}

MainWindow::~MainWindow()
{
    if( this->connection != nullptr )
        delete this->connection;
    if( this->library != nullptr )
     delete this->library;
    if( this->fileUploader != nullptr )
        delete this->fileUploader;
}

void MainWindow::configureToolBar()
{
    this->toolBar = this->addToolBar( "MainMenu" );
    this->toolBar->setMinimumHeight( 55 );
    this->toolBar->setMovable( false );
    this->toolBar->setStyleSheet( "background-color: #6389A8;");

    this->libraryButton = new MPushButton ( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/library.png" ), "Library" );
    connect( this->libraryButton, SIGNAL( clicked() ), this, SLOT( libraryButtonPressed() ) );
    this->libraryButton->setFlat( true );
    this->libraryButton->setDisabled( true );
    this->libraryButton->setStyleSheet( "color: white; border-bottom: 1px solid red;" );
    this->toolBar->addWidget( this->libraryButton );
    this->toolBar->addSeparator();

    this->uploadButton = new MPushButton( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/add.png" ), "Upload" );
    connect( this->uploadButton, SIGNAL( clicked() ), this, SLOT( uploadButtonPressed() ) );
    this->uploadButton->setFlat( true );
    this->uploadButton->setStyleSheet( "color: white;" );
    this->toolBar->addWidget( this->uploadButton );
    this->toolBar->addSeparator();

    this->settingsButton = new MPushButton ( QPixmap( QDir::homePath()+"/Dropbox/Progetto Condiviso/Incigneria/Client/image/settings.png" ), "Settings" );
    connect( this->settingsButton, SIGNAL( clicked() ), this, SLOT( settingsButtonPressed() ) );
    this->settingsButton->setFlat( true );
    this->settingsButton->setStyleSheet( "color: white;" );
    this->toolBar->addWidget( this->settingsButton );
}

void MainWindow::newConnection()
{
    this->library = new Library();
    this->fileUploader = new FileUploader();
    this->libraryButtonPressed();
    this->show();
}

void MainWindow::libraryButtonPressed()
{
    this->libraryButton->setEnabled( false );
    this->uploadButton->setEnabled( true );
    this->settingsButton->setEnabled( true );

    this->fileUploader->setParent( nullptr );
    this->setCentralWidget( this->library );
}

void MainWindow::uploadButtonPressed()
{
    this->libraryButton->setEnabled( true );
    this->uploadButton->setEnabled( false );
    this->settingsButton->setEnabled( true );

    this->library->setParent( nullptr );
    this->setCentralWidget( this->fileUploader );
}

void MainWindow::settingsButtonPressed()
{
    this->libraryButton->setEnabled( true );
    this->uploadButton->setEnabled( true );
    this->settingsButton->setEnabled( false );

    this->library->setParent( nullptr );
    this->fileUploader->setParent( nullptr );
    this->setCentralWidget( nullptr );
}

