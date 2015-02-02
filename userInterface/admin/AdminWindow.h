#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "userInterface/admin/AddUserWidget.h"
#include "userInterface/IconLoader.h"
#include "userInterface/MPushButton.h"

namespace userInterface
{
    namespace admin
    {
        class AdminWidget : public QWidget
        {
            Q_OBJECT

        private:
            QVBoxLayout *mainLayout;
            QHBoxLayout *buttonLayout;
            QListWidget *userList;
            QPushButton *addUserButton;
            QPushButton *deleteUserButton;
            AddUserWidget *addUserWidget;
            //AdminConncetion *adminConnection;

        public:
            AdminWidget(QWidget *parent = 0);
            ~AdminWidget();

        signals:

        private slots:
            void newUser ( QString userName );
            void removeUser ( QString userName );

        };
    }
}

#endif // ADMINWIDGET_H
