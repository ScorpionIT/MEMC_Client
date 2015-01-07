#ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <QObject>

class ServiceConnection : public QObject
{
    Q_OBJECT
public:
    explicit ServiceConnection(QObject *parent = 0);
    ~ServiceConnection();

signals:

public slots:
};

#endif // SERVICECONNECTION_H
