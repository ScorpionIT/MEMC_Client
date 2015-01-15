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
    QObject::connect (login, SIGNAL( loginSuccesful() ), &mainWin, SLOT( newConnection() ) );
    login->show();

    return a.exec();
}
