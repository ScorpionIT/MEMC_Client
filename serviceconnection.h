#ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <QThread>
#include <QTcpSocket>
#include <QString>


class ServiceConnection : public QThread
{
    Q_OBJECT

private:
    QString lastError;
    QString sessionID;
    QTcpSocket* server;
    QString serverAddr;
    QString serverPort;
    QString username;
    void run();

protected:
    static const unsigned long SESSION_TIMER;
    virtual void processService(QTcpSocket* server) = 0;

public:
    ServiceConnection( QString serverAddr, QString serverPort, QString username, QString sessionID);
    ~ServiceConnection();
    QString getLastError();

};

#endif // SERVICECONNECTION_H
