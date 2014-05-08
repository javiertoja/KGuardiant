#ifndef KGUARDIANTTHREAD_H
#define KGUARDIANTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class KGuardiantThread : public QThread
{
    Q_OBJECT
public:
    explicit KGuardiantThread(qintptr ID, QObject *parent = 0);
    
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

};

#endif // KGUARDIANTTHREAD_H
