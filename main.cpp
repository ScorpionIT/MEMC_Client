#include <QApplication>
#include "login.h"
#include "filemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.show();

    FileManager fileManager;
    fileManager.show();

    return a.exec();
}
