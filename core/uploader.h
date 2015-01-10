#ifndef UPLOADER_H
#define UPLOADER_H

#include <QFileInfo>
#include <QVector>
#include "core/serviceconnection.h"

class Uploader : public ServiceConnection
{
    Q_OBJECT

private:
    QVector<QFileInfo>* toUpload;
    bool stopUploadProcess;

protected:
    virtual void processService(QTcpSocket* server);

public:
    Uploader(QVector<QFileInfo> *selectdFile, QString serverAddr, QString serverPort, QString username, QString sessionID );
    ~Uploader();
    void stopUpload();

signals:
    void progress(int percent, QString filename);
    void finish ( QString status );

};

#endif // UPLOADER_H
