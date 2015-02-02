#include "AddUserWidget.h"

using namespace userInterface;
using namespace admin;

AddUserWidget::AddUserWidget(QWidget *parent) : QWidget (parent)
{
    this->setWindowModality (Qt::WindowModal);
    this->setWindowFlags( Qt::FramelessWindowHint | Qt::Dialog );
    this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    this->mainLayout = new QHBoxLayout();
    this->userName = new QLineEdit();
    this->selectedMemory = new QSpinBox();
    this->addUserButton = new QPushButton( "Add user" );
    connect( this->addUserButton, SIGNAL( clicked() ), this, SLOT( addUserPressed() ) );

    this->mainLayout->addWidget( this->userName );
    this->mainLayout->addWidget( this->selectedMemory );
    this->mainLayout->addWidget( this->addUserButton );

    this->setLayout( this->mainLayout);
}

AddUserWidget::~AddUserWidget()
{

}

void AddUserWidget::addUserPressed()
{
    emit addUser( this->userName->text() );
    this->userName->clear();
    this->hide();
}

