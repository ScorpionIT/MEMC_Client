#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Connection: public QObject
{
    Q_OBJECT

private:
    static const unsigned long SESSION_TIMER;
    QTcpSocket* server;
    QString lastError;
    QString sessionID;

public:
    Connection(QString serverAddr , QString username, QString password);
    ~Connection();
    QString getLastError();
    QString getSessionID();

private slots:
    void procesMessage();
    void closeConnection();

signals:
    void connectionClosed ();
};

#endif // CONNECTION_H
