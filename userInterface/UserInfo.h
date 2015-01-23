#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "core/network/Session.h"

namespace userInterface
{
    class UserInfo : public QWidget
    {
        Q_OBJECT

    private:
        QLabel* supportLabel;
        QVBoxLayout* mainLayout;
        QPushButton* logoutButton;

    public:
        UserInfo(QWidget *parent = 0);
        ~UserInfo();

    signals:

    public slots:
    };
}

#endif // USERINFO_H
