#include "tcpconnection.h"


TCPConnection::TCPConnection(qintptr id, QObject *parent) :
    QObject(parent)
{
   // qDebug() << "Conexión creada";
    this->socketDescriptor = id;
    socket = new QTcpSocket(parent);
    log = Logger::Instance();
}

TCPConnection::~TCPConnection(){
    log = NULL;
    //socket->close();
    socket = NULL;
}


void TCPConnection::run()
{
    //qDebug() << "Creando fío para conexión.";
    log->log("Creando fío para conexión.");


    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        qDebug() <<socket->error();
        emit error(socket->error());
    }

    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(readyRead()));

    connect(socket,
            SIGNAL(disconnected()),
            this,
            SLOT(disconnected()));

    log->log(QString("Establecida conexión co cliente [%1]")
             .arg(socketDescriptor));

    //qDebug() << "Establecida conexión co cliente ["
    //         << socketDescriptor << "]";

    //exec();
}

/**
 * @brief TCPConnection::readyRead
 */
void TCPConnection::readyRead()
{
    socket->write(socket->readAll());
}

/**
 * @brief TCPConnection::disconnected
 */
void TCPConnection::disconnected()
{
    //qDebug() << "Desconectado o cliente ["
    //         << socketDescriptor << "]";
    log->log(QString("Desconectado o cliente [%1]")
             .arg(socketDescriptor));

    emit delClient(socketDescriptor);

    socket->deleteLater();
    //exit(0);

}

/**
 * @brief TCPConnection::sendImg
 * @param data
 */
void TCPConnection::sendImg(QByteArray data)
{
    //qDebug() << "Enviado imaxe o cliente ["
    //         << socketDescriptor << "]";

    //log->log(QString("Enviado imaxe o cliente [%1]")
    //         .arg(socketDescriptor));

    socket->write(data);
}
