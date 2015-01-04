#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    this->hLayout = new QHBoxLayout();
    this->serverAddressLabel = new QLabel ( "Server Address" );
    this->serverAddressLabel->setMinimumWidth ( 100 );
    this->serverAddress = new QLineEdit ();
    this->hLayout->addWidget( this->serverAddressLabel );
    this->hLayout->addWidget( this->serverAddress );

    this->hLayout2 = new QHBoxLayout();
    this->usernameLabel = new QLabel ( "Nome Utente" );
    this->usernameLabel->setMinimumWidth ( 100 );
    this->username = new QLineEdit ();
    this->hLayout2->addWidget( this->usernameLabel );
    this->hLayout2->addWidget( this->username );

    this->hLayout3 = new QHBoxLayout();
    this->passwordLabel = new QLabel ( "Password" );
    this->passwordLabel->setMinimumWidth ( 100 );
    this->password = new QLineEdit ();
    this->hLayout3->addWidget( this->passwordLabel );
    this->hLayout3->addWidget( this->password );

    this->loginButton = new QPushButton ( "Login" );
    connect ( this->loginButton, SIGNAL( pressed() ), this, SLOT( loginButtonPressed() ) );

    this->vLayout = new QVBoxLayout();
    this->vLayout->addLayout( this->hLayout );
    this->vLayout->addLayout( this->hLayout2 );
    this->vLayout->addLayout( this->hLayout3 );
    this->vLayout->addWidget( this->loginButton );
    this->setLayout( vLayout );
}

Login::~Login()
{
    delete serverAddress;
    delete serverAddressLabel;
    delete username;
    delete usernameLabel;
    delete password;
    delete passwordLabel;
    delete hLayout;
    delete hLayout2;
    delete hLayout3;
    delete vLayout;
}

void Login::loginButtonPressed()
{
    QString serverAddress = this->serverAddress->text();
    QString username = this->username->text();
    QString password = this->password->text();

    this->loginButton->setEnabled( false );
    this->loginButton->setText( "Connecting..." );

    Connection* connection= new Connection (serverAddress, username, password);

    if (connection->getLastError().isEmpty())
    {
        this->loginButton->setText( "Connected" );
        emit loginSuccesful(connection);
    }
    else
    {
        this->loginButton->setEnabled( true );
        QMessageBox::warning(this, "Warning", "Impossibile connettersi: \n"+connection->getLastError());
    }
}
