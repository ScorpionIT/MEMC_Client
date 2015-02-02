#include "AdminWindow.h"
#include <QDebug>

using namespace userInterface;
using namespace admin;

AdminWidget::AdminWidget(QWidget *parent) : QWidget(parent)
{
    this->addUserWidget = new AddUserWidget( this );
    connect ( this->addUserWidget, SIGNAL( addUser(QString) ), this, SLOT( newUser(QString) ) );
    this->mainLayout = new QVBoxLayout();

    this->userList = new QListWidget();
    this->userList->setAlternatingRowColors( true );
    this->mainLayout->addWidget( this->userList );

    this->buttonLayout = new QHBoxLayout();
    this->deleteUserButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::DEL ), "Delete user" );
    //CONNECT
    this->buttonLayout->addWidget( this->deleteUserButton );

    this->addUserButton = new MPushButton( IconLoader::getIstance()->getIcon( IconLoader::UPLOAD ), "Add user" );
    connect(this->addUserButton, SIGNAL( clicked() ), this->addUserWidget, SLOT( show() ) );
    this->buttonLayout->addWidget( this->addUserButton );

    this->mainLayout->addLayout( this->buttonLayout );
    this->setLayout( this->mainLayout );
}

AdminWidget::~AdminWidget()
{

}

void AdminWidget::newUser(QString userName)
{
    new QListWidgetItem ( userName, this->userList );
}

void AdminWidget::removeUser(QString userName)
{

}

