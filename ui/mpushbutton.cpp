#include "mpushbutton.h"

MPushButton::MPushButton( const QString &text, QWidget *parent) : QPushButton( text, parent )
{
    this->setMemcStyle();
}

MPushButton::MPushButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton( icon, text, parent )
{
    this->setMemcStyle();
}


void MPushButton::setMemcStyle()
{
    QFont buttonFont;
    buttonFont.setPointSize( 10 );
    QSize buttonIconSize ( 40, 40 );

    this->setIconSize( buttonIconSize );
    this->setFont( buttonFont );
}
