#include "Spacer.h"

using namespace userInterface;

Spacer::Spacer(QWidget* parent, SpacerOrientation orientation) : QWidget (parent)
{
    if ( orientation == SpacerOrientation::VERTICAL )
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    else
        this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred);

    this->setStyleSheet( "background-color: transparent;" );
    this->setVisible(true);
}

Spacer::~Spacer()
{

}

