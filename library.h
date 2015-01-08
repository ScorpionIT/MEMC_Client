#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mpushbutton.h"
#include "connection.h"
#include "fileservice.h"

class Library : public QWidget
{
    Q_OBJECT

private:
    MPushButton* movieButton;
    MPushButton* musicButton;
    MPushButton* imageButton;
    QListWidget* fileList;
    QHBoxLayout* buttonsLayout;
    QVBoxLayout* vLayout;
    FileService* fileService;
    Connection* connection;

public:
    Library(Connection* conn, QWidget *parent = 0);
    ~Library();

signals:

private slots:
    void loadFileList( QStringList* fileList, QString response );
    void movieButtonPressed();
    void musicButtonPressed();
    void imageButtonPressed();
};

#endif // FILEMANAGER_H
