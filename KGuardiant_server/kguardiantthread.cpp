#include "kguardiantthread.h"

KGuardiantThread::KGuardiantThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;

}

void KGuardiantThread::run()
{
    //Iniciamos o novo Thread
    qDebug() << "Thread Iniciado.";
    Logger::Instance()->log(
                QString("Thread Iniciado"));

    socket = new QTcpSocket();

    //Seteamos o ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        //Error a hora de Settear o socket.
        emit error(socket->error());
        return;
    }

    //Se todo vai ben conectamos o socket as señais correspondentes
    //Usamos QT::DirectConnection por que o servidor é multithread
    //  Esto fai que o slot sexa invocado inmediatamente cando o sinal
    //  é emitido.
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()),
            Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    //Identificamos o cliente que se acaba de conectar
    qDebug() << "Cliente Conectado[" << socketDescriptor << "]";

    exec();
}

void KGuardiantThread::readyRead()
{
    //Recollemos a información do socket
    QByteArray data = socket->readAll();

    //Imprimimos os datos recibidos
    qDebug() << "Datos recibidos de ["<< socketDescriptor << "]["
             << data <<"]";

    socket->write(data);
}

void KGuardiantThread::disconnected()
{
    QString msg(QString("Desconectado o ID[%1]").arg(socketDescriptor));

    qDebug() << msg;
    Logger::Instance()->log(msg);

    socket->deleteLater();
    exit(0);
}
