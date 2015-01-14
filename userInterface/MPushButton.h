#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include <QPushButton>

namespace userInterface
{
    class MPushButton : public QPushButton
    {
        Q_OBJECT

    private:
        void setMemcStyle();

    public:
        MPushButton( const QString & text, QWidget * parent = 0 );
        MPushButton( const QIcon & icon, const QString & text, QWidget * parent = 0 );
    };
}

#endif // MEMCPUSHBUTTON_H
