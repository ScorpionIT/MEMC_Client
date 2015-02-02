#include "Login.h"

using namespace userInterface;

Login::Login(QWidget *parent) : QWidget(parent)
{
    this->serverAnnunce = new QUdpSocket();
    this->serverAnnunce->bind(79000, QUdpSocket::ShareAddress);
    connect (this->serverAnnunce, SIGNAL( readyRead() ), this, SLOT( newServerAnnunce() ) );

    this->advancedMode = false;
    this->setWindowTitle( "MEMC - Login");

    this->serverList = new QListWidget();
    this->serverList->setAlternatingRowColors( true );
    connect ( this->serverList, SIGNAL( itemSelectionChanged() ), this, SLOT( setServerAddress() ) );

    this->serverAddressLayout = new QHBoxLayout();
    this->serverAddressLabel = new QLabel ( "Server Address" );
    this->serverAddressLabel->setMinimumWidth ( 100 );
    this->serverAddressLabel->setVisible( false );
    this->serverAddress = new QLineEdit ();
    this->serverAddress->setVisible( false );

    this->serverAddressLayout->addWidget( this->serverAddressLabel );
    this->serverAddressLayout->addWidget( this->serverAddress );

    this->hLayout2 = new QHBoxLayout();
    this->usernameLabel = new QLabel ( "Username" );
    this->usernameLabel->setMinimumWidth ( 100 );
    this->username = new QLineEdit ();
    this->hLayout2->addWidget( this->usernameLabel );
    this->hLayout2->addWidget( this->username );

    this->hLayout3 = new QHBoxLayout();
    this->passwordLabel = new QLabel ( "Password" );
    this->passwordLabel->setMinimumWidth ( 100 );
    this->password = new QLineEdit ();
    this->password->setEchoMode( QLineEdit::Password );
    this->hLayout3->addWidget( this->passwordLabel );
    this->hLayout3->addWidget( this->password );

    this->buttonLayout = new QHBoxLayout();

    this->advancedOptionButton = new QPushButton ( "Advanced");
    connect( this->advancedOptionButton, SIGNAL( clicked() ), this, SLOT( advancedOptionButtonPressed() ) );
    this->buttonLayout->addWidget( this->advancedOptionButton );

    this->loginButton = new QPushButton ( "Login" );
    connect( this->loginButton, SIGNAL( pressed() ), this, SLOT( loginButtonPressed() ) );
    this->buttonLayout->addWidget( this->loginButton );

    this->adminLoginButton = new QPushButton ( "Login as Admin" );
    this->adminLoginButton->setVisible( false );
    connect( this->adminLoginButton, SIGNAL( clicked() ), this, SLOT( adminLoginButtonPressed() ) );
    this->buttonLayout->addWidget( this->adminLoginButton );

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addWidget( this->serverList );
    this->mainLayout->addLayout( this->serverAddressLayout );
    this->mainLayout->addLayout( this->hLayout2 );
    this->mainLayout->addLayout( this->hLayout3 );
    this->mainLayout->addLayout( this->buttonLayout );
    this->setLayout( mainLayout );

    // DEBUG FAST LOGIN
    this->serverAddress->setText( "127.0.0.1" );
    this->username->setText( "Elia" );
    this->password->setText( "elia" );
    // DEBUG FAST LOGIN
    this->setFocus();
}

Login::~Login()
{
    delete serverAddress;
    delete serverAddressLabel;
    delete username;
    delete usernameLabel;
    delete password;
    delete passwordLabel;
    delete serverAddressLayout;
    delete hLayout2;
    delete hLayout3;
    delete mainLayout;
}

void Login::loginButtonPressed()
{
    QString serverAddress = this->serverAddress->text();
    QString username = this->username->text();
    QString password = this->password->text();

    this->loginButton->setEnabled( false );
    this->loginButton->setText( "Connecting..." );

    core::network::Connection* connection= new core::network::Connection (serverAddress, username, password);

    if (connection->getLastError().isEmpty())
    {
        emit loginSuccesful();
        delete this;
    }
    else
    {
        this->loginButton->setEnabled( true );
        this->loginButton->setText( "Login" );
        QMessageBox::warning(this, "Warning", "Impossibile connettersi: \n"+connection->getLastError());
    }
}

void Login::adminLoginButtonPressed()
{
    emit adminLoginSuccesful();
    delete this;
}

void Login::advancedOptionButtonPressed()
{
    if ( this->advancedMode )
    {
        this->serverAddressLabel->setVisible( false );
        this->serverAddress->setVisible( false );
        this->adminLoginButton->setVisible( false );
        this->advancedMode = false;
    }
    else
    {
        this->serverAddressLabel->setVisible( true );
        this->serverAddress->setVisible( true );
        this->adminLoginButton->setVisible( true );
        this->advancedMode = true;
    }
}

void Login::newServerAnnunce()
{
    while ( this->serverAnnunce->hasPendingDatagrams() )
    {
        QByteArray datagram;
        QHostAddress sender;
        datagram.resize( this->serverAnnunce->pendingDatagramSize() );
        this->serverAnnunce->readDatagram( datagram.data(), datagram.size(), &sender );

        if (datagram == "MEMC-SERVER")
        {
            QString toMatch = "MEMC SERVER - " + sender.toString();
            QList<QListWidgetItem *> servers = this->serverList->findItems( toMatch, Qt::MatchExactly );
            if ( servers.count() == 0 )
                new QListWidgetItem ( toMatch, this->serverList );
        }
    }
}

void Login::setServerAddress()
{
    QList<QListWidgetItem *> items = this->serverList->selectedItems();

    if ( items.count() > 0 )
         this->serverAddress->setText( items.first()->text().split("-")[1].replace(" ", "") );
}

