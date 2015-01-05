#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QDir>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FileManager : public QWidget
{
    Q_OBJECT

private:
    QPushButton* movieButton;
    QPushButton* musicButton;
    QPushButton* imageButton;
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
    void photoButtonPressed();
};

#endif // FILEMANAGER_H
