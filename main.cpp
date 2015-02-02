#include <QApplication>
#include "userInterface/admin/AdminWindow.h"
#include "userInterface/MainWindow.h"
#include "userInterface/Login.h"

using namespace userInterface;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    admin::AdminWidget adminWidget;

    MainWindow mainWin;
    mainWin.configureToolBar();

    Login* login = new Login();
    QObject::connect (login, SIGNAL( loginSuccesful() ), &mainWin, SLOT( newConnection() ) );
    QObject::connect (login, SIGNAL( adminLoginSuccesful() ), &adminWidget, SLOT( show() ) );
    login->show();

    return a.exec();
}
