#include <QApplication>
#include "userInterface/MainWindow.h"
#include "userInterface/Login.h"

using namespace userInterface;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWin;
    mainWin.configureToolBar();

    Login* login = new Login();
    QObject::connect (login, SIGNAL( loginSuccesful(core::Connection*) ), &mainWin, SLOT( newConnection(core::Connection*) ) );
    login->show();

    return a.exec();
}
