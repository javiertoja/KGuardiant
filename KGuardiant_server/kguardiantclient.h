#ifndef KGUARDIANTCLIENT_H
#define KGUARDIANTCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "logger.h"
#include "movementdetector.h"

class KGuardiantClient : public QObject
{
    Q_OBJECT
public:
    explicit KGuardiantClient(qintptr descriptor, QObject *parent = 0);

signals:
    void endAlgoritm(int algId);
    void error(QTcpSocket::SocketError socketerror);
public slots:
    void connected();
    void disconnected();
    void readyRead();

    void resultAlgDetector();
    void restulAlgVisor();

private:
    QTcpSocket *socket;
    int stop;
    qintptr socketDescriptor;
    MovementDetector *mvDetector;

};

#endif // KGUARDIANTCLIENT_H
