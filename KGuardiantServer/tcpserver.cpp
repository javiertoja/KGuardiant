#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent)
{
    settings = Configuracion::Instance();
    clientMap = new QHash<qintptr, TCPConnection *>();
    log = Logger::Instance();
}

/**
 * @brief TCPServer::startServer
 */
void TCPServer::startServer()
{
    if (!this->listen(QHostAddress::Any,
                      settings->getValue("configuracion","porto").toInt()))
    {
        //qDebug()  << "Erro o arrancar o server";

    }else{
        qDebug()  << "Servidor arrancado con éxito, escoitando ["
                  << settings->getValue("configuracion","porto").toInt()
                  << "]";
    }
}

/**
 * @brief TCPServer::incomingConnection
 * @param socketDescriptor
 */
void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    //qDebug() << "Conexión entrante do cliente ID["
    //        << socketDescriptor << "]";
    log->log(QString("Conexión entrante do cliente ID[%1]")
             .arg(socketDescriptor));


    clientMap->insert(socketDescriptor,new TCPConnection(socketDescriptor,this->parent()));
    /*connect(clientMap->value(socketDescriptor),
            SIGNAL(finished()),
            clientMap->value(socketDescriptor),
            SLOT(deleteLater()));*/

    connect(this,
            SIGNAL(newImg(QByteArray)),
            clientMap->value(socketDescriptor),
            SLOT(sendImg(QByteArray)));
    connect(clientMap->value(socketDescriptor),
            SIGNAL(delClient(qintptr)),
            this,
            SLOT(removeClient(qintptr)),
            Qt::DirectConnection);


    clientMap->value(socketDescriptor)->run();
}

/**
 * @brief TCPServer::stopServer
 */
void TCPServer::stopServer()
{
    this->close();
}

/**
 * @brief TCPServer::sendImg
 * @param data
 */
void TCPServer::sendImg(QByteArray data)
{
    emit newImg(data);
}

/**
 * @brief TCPServer::removeClient
 * @param socketDescriptor
 */
void TCPServer::removeClient(qintptr socketDescriptor)
{

    disconnect(this,
            SIGNAL(newImg(QByteArray)),
            clientMap->value(socketDescriptor),
            SLOT(sendImg(QByteArray)));
    disconnect(clientMap->value(socketDescriptor),
            SIGNAL(delClient(qintptr)),
            this,
            SLOT(removeClient(qintptr)));
    clientMap->remove(socketDescriptor);
}

/**
 * @brief TCPServer::requestClients
 */
void TCPServer::requestClients()
{
    emit clientList(clientMap);
}
