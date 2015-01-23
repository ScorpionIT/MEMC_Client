#include "MainWindow.h"
#include <QMenu>

using namespace userInterface;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle( "MEMC - Client");
    this->resize( 1024, 700 );
    this->library = nullptr;
    this->fileUploader = nullptr;
    this->dlnaManager = nullptr;
    this->userInfo = nullptr;
}

MainWindow::~MainWindow()
{
    if( this->library != nullptr )
     delete this->library;
    if( this->fileUploader != nullptr )
        delete this->fileUploader;
    if( this->dlnaManager != nullptr )
        delete this->dlnaManager;
    if (this->userInfo != nullptr)
        delete this->userInfo;
}

void MainWindow::configureToolBar()
{
    this->toolBar = this->addToolBar( "MainMenu" );
    this->toolBar->setMinimumHeight( 55 );
    this->toolBar->setMovable( false );
    this->toolBar->setStyleSheet( "background-color: #6389A8;");

    this->libraryButton = new MToolPushButton ( IconLoader::getIstance()->getIcon( IconLoader::LIBRARY ), "Library" );
    connect( this->libraryButton, SIGNAL( clicked() ), this, SLOT( libraryButtonPressed() ) );

    this->toolBar->addWidget( this->libraryButton );
    this->toolBar->addSeparator();

    this->uploadButton = new MToolPushButton( IconLoader::getIstance()->getIcon( IconLoader::UPLOAD ), "Upload" );
    connect( this->uploadButton, SIGNAL( clicked() ), this, SLOT( uploadButtonPressed() ) );

    this->toolBar->addWidget( this->uploadButton );
    this->toolBar->addSeparator();

    this->dlnaButton = new MToolPushButton ( IconLoader::getIstance()->getIcon( IconLoader::DLNA ), "DLNA" );
    connect(this->dlnaButton, SIGNAL( clicked() ), this, SLOT( dlnaButtonPressed() ) );
    this->toolBar->addWidget( this->dlnaButton );
    this->toolBar->addSeparator();

    this->settingsButton = new MToolPushButton ( IconLoader::getIstance()->getIcon( IconLoader::SETTINGS ), "Settings" );
    connect( this->settingsButton, SIGNAL( clicked() ), this, SLOT( settingsButtonPressed() ) );
    this->toolBar->addWidget( this->settingsButton );

    this->toolBar->addWidget( new Spacer( this, SpacerOrientation::HORIZZONTAL ) );


}

void MainWindow::newConnection()
{
    this->library = new Library();
    this->fileUploader = new FileUploader();
    this->dlnaManager = new DlnaManager();
    this->userInfo = new UserInfo();
    this->toolBar->addSeparator();
    this->toolBar->addWidget( userInfo );
    this->libraryButtonPressed();
    this->show();
}

void MainWindow::libraryButtonPressed()
{
    this->libraryButton->setEnabled( false );
    this->uploadButton->setEnabled( true );
    this->dlnaButton->setEnabled( true );
    this->settingsButton->setEnabled( true );

    this->fileUploader->setParent( nullptr );
    this->dlnaManager->setParent( nullptr );
    this->setCentralWidget( this->library );
}

void MainWindow::uploadButtonPressed()
{
    this->libraryButton->setEnabled( true );
    this->uploadButton->setEnabled( false );
    this->dlnaButton->setEnabled( true );
    this->settingsButton->setEnabled( true );

    this->library->setParent( nullptr );
    this->dlnaManager->setParent( nullptr );
    this->setCentralWidget( this->fileUploader );
}

void MainWindow::settingsButtonPressed()
{
    this->libraryButton->setEnabled( true );
    this->uploadButton->setEnabled( true );
    this->dlnaButton->setEnabled( true );
    this->settingsButton->setEnabled( false );

    this->library->setParent( nullptr );
    this->fileUploader->setParent( nullptr );
    this->dlnaManager->setParent( nullptr );
    this->setCentralWidget( nullptr );
}

void MainWindow::dlnaButtonPressed()
{
    this->libraryButton->setEnabled( true );
    this->uploadButton->setEnabled( true );
    this->dlnaButton->setEnabled( false );
    this->settingsButton->setEnabled( true );

    this->library->setParent( nullptr );
    this->fileUploader->setParent( nullptr );
    this->setCentralWidget( this->dlnaManager );
}
