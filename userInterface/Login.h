#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEventLoop>
#include <QMessageBox>
#include "core/Connection.h"

namespace userInterface
{
    class Login : public QWidget
    {
        Q_OBJECT

    private:
        QLabel* serverAddressLabel;
        QLabel* usernameLabel;
        QLabel* passwordLabel;
        QLineEdit* serverAddress;
        QLineEdit* username;
        QLineEdit* password;
        QPushButton* loginButton;
        QHBoxLayout* hLayout;
        QHBoxLayout* hLayout2;
        QHBoxLayout* hLayout3;
        QVBoxLayout* vLayout;

    public:
        Login(QWidget *parent = 0);
        ~Login();

    signals:
        void loginSuccesful(core::Connection* conn);

    private slots:
        void loginButtonPressed();

    };
}

#endif // LOGIN_H
