#ifndef ADDUSERWIDGET_H
#define ADDUSERWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

namespace userInterface
{
    namespace admin
    {
        class AddUserWidget : public QWidget
        {
            Q_OBJECT

        private:
            QLineEdit *userName;
            QSpinBox *selectedMemory;
            QHBoxLayout *mainLayout;
            QPushButton *addUserButton;

        public:
            AddUserWidget(QWidget *parent);
            ~AddUserWidget();

        signals:
            void addUser( QString userName);

        private slots:
            void addUserPressed();
        };
    }

}

#endif // ADDUSERWIDGET_H
