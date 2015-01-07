#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mpushbutton.h"

class FileManager : public QWidget
{
    Q_OBJECT

private:
    MPushButton* movieButton;
    MPushButton* musicButton;
    MPushButton* imageButton;
    QListWidget* fileList;
    QHBoxLayout* buttonsLayout;
    QVBoxLayout* vLayout;

public:
    FileManager(QWidget *parent = 0);
    ~FileManager();

signals:

private slots:
    void movieButtonPressed();
    void musicButtonPressed();
    void imageButtonPressed();
};

#endif // FILEMANAGER_H
