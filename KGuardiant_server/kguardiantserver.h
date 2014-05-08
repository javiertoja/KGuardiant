#ifndef KGUARDIANTSERVER_H
#define KGUARDIANTSERVER_H

#include <QTcpServer>

class KGuardiantServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit KGuardiantServer(QObject *parent = 0);
    void startServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // KGUARDIANTSERVER_H
