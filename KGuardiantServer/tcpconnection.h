#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include <logger.h>

class TCPConnection : public QObject
{
    Q_OBJECT
public:
    explicit TCPConnection(qintptr id, QObject *parent = 0);
    ~TCPConnection();
    void run();

private:

    QTcpSocket *socket;
    qintptr socketDescriptor;
    Logger *log;
signals:
    
    void error(QTcpSocket::SocketError socketError);
    void delClient(qintptr socketDescriptor);
public slots:
    
    void readyRead();
    void disconnected();
    void sendImg(QByteArray data);
};

#endif // TCPCONNECTION_H
