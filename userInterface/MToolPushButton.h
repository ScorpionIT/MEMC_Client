#ifndef MTOOLPUSHBUTTON_H
#define MTOOLPUSHBUTTON_H

#include <QPushButton>

namespace userInterface
{
    class MToolPushButton : public QPushButton
    {
        Q_OBJECT

    private:
        void setMemcStyle();

    public:
        MToolPushButton( const QString & text, QWidget * parent = 0 );
        MToolPushButton( const QIcon & icon, const QString & text, QWidget * parent = 0 );
    };
}

#endif // MTOOLPUSHBUTTON_H
