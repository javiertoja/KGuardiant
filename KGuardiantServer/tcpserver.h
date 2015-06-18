#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QHash>
#include <tcpconnection.h>
#include <configuracion.h>
#include <logger.h>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = 0);

private:
    Configuracion *settings;
    Logger *log;
    QHash<qintptr, TCPConnection *> *clientMap;
protected:
    void incomingConnection(qintptr socketDescriptor);
    
signals:
    void addClient();
    void delClient();
    void newImg(QByteArray data);
    void clientList(QHash<qintptr, TCPConnection *> *clientMap);
public slots:
    void startServer();
    void stopServer();
    void sendImg(QByteArray data);
    void removeClient(qintptr socketDescriptor);
    void requestClients();
};

#endif // TCPSERVER_H
