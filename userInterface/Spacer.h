#ifndef SPACER_H
#define SPACER_H

#include <QWidget>

namespace userInterface
{
    enum SpacerOrientation { HORIZZONTAL, VERTICAL };

    class Spacer : public QWidget
    {
        public:
            Spacer(QWidget *parent = 0, SpacerOrientation orientation = SpacerOrientation::HORIZZONTAL);
            ~Spacer();
    };
}

#endif // SPACER_H
