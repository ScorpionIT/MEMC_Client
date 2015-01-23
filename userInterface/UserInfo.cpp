#include "UserInfo.h"

using namespace userInterface;

UserInfo::UserInfo(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QVBoxLayout();
    this->supportLabel = new QLabel ("<b>" + core::network::Session::getSession()->getUsername()  +"</b>" );
    this->mainLayout->addWidget( this->supportLabel );

    this->supportLabel = new QLabel ("<b>Space avaiable:</b> " + QString::number(core::network::Session::getSession()->getAvaiableSpace())  + " TB" );
    this->mainLayout->addWidget( this->supportLabel );

    /*this->logoutButton = new QPushButton( "logout" );
    //this->logoutButton->setFlat( true );
    this->mainLayout->addWidget( this->logoutButton );*/

    this->setStyleSheet( "background-color: transparent; color:white; ");
    this->setLayout( this->mainLayout );
}

UserInfo::~UserInfo()
{

}

