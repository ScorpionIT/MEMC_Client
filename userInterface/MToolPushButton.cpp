#include "MToolPushButton.h"

using namespace userInterface;

MToolPushButton::MToolPushButton( const QString &text, QWidget *parent) : QPushButton( text, parent )
{
    this->setMemcStyle();
}

MToolPushButton::MToolPushButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton( icon, text, parent )
{
    this->setMemcStyle();
}

void MToolPushButton::setMemcStyle()
{
    QFont buttonFont;
    buttonFont.setPointSize( 10 );
    QSize buttonIconSize ( 40, 40 );

    this->setIconSize( buttonIconSize );
    this->setFont( buttonFont );
    QString  style = "QPushButton {"
            "background-color: transparent;"
            "border: none;"
            "color: white;"
            "padding: 5;"
            "border-radius: 3"
            "}"
            "QPushButton:hover {"
            "background-color: #89BEE8;"
            "}"
            "QPushButton:disabled {"
            "background-color: #89BEE8;"
            "}";
    this->setStyleSheet( style );
}
