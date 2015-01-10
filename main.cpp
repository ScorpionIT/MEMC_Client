#include <QApplication>
#include "ui/mainwindow.h"
#include "ui/login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWin;
    mainWin.configureToolBar();

    Login* login = new Login();
    QObject::connect (login, SIGNAL( loginSuccesful(Connection*) ), &mainWin, SLOT( newConnection(Connection*) ) );
    login->show();

    return a.exec();
}
