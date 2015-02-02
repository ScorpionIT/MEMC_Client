#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEventLoop>
#include <QMessageBox>
#include <QListWidget>
#include <QUdpSocket>
#include "core/network/Connection.h"

namespace userInterface
{
    class Login : public QWidget
    {
        Q_OBJECT

    private:
        QListWidget *serverList;
        QLabel *serverAddressLabel;
        QLabel *usernameLabel;
        QLabel *passwordLabel;
        QLineEdit *serverAddress;
        QLineEdit *username;
        QLineEdit *password;
        QPushButton *advancedOptionButton;
        QPushButton *loginButton;
        QPushButton *adminLoginButton;
        QHBoxLayout *serverAddressLayout;
        QHBoxLayout *hLayout2;
        QHBoxLayout *hLayout3;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *mainLayout;
        QUdpSocket *serverAnnunce;
        bool advancedMode;

    public:
        Login(QWidget *parent = 0);
        ~Login();

    signals:
        void loginSuccesful();
        void adminLoginSuccesful();

    private slots:
        void loginButtonPressed();
        void adminLoginButtonPressed();
        void advancedOptionButtonPressed();
        void newServerAnnunce();
        void setServerAddress();
    };
}

#endif // LOGIN_H
