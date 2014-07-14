#include "kguardiantclient.h"

KGuardiantClient::KGuardiantClient(qintptr descriptor, QObject *parent) :
    QObject(parent)
{
    this->stop = 0;
    this->socketDescriptor = descriptor;

    QString msg(QString("Fio Para o cliente ID[%1] creado.").arg(descriptor));

    //Creamos un novo socket
    this->socket = new QTcpSocket(this);

    //Se todo vai ben conectamos o socket as señais correspondentes
    //  Esto fai que o slot sexa invocado inmediatamente cando o sinal
    //  é emitido.
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    //Seteamos o ID
    if(!socket->setSocketDescriptor(descriptor))
    {
        //Error a hora de Settear o socket.
        emit error(socket->error());
        return;
    }

    //Identificamos o cliente que se acaba de conectar
    qDebug() << msg;
    Logger::Instance()->log(msg);

    this->camVisor = new CamVisor(false);
    connect(this->camVisor,SIGNAL(resultado(QByteArray)),this,SLOT(resultAlgVisor(QByteArray)),Qt::QueuedConnection);
    connect(this,SIGNAL(endAlgoritm(bool)),this->camVisor,SLOT(stopTask(bool)),Qt::QueuedConnection);
    connect(this->camVisor,SIGNAL(error(int)),this,SLOT(errorAlg(int)));
}


void KGuardiantClient::connected()
{

}

void KGuardiantClient::disconnected()
{
    QString msg(QString("cliente ID[%1] Desconectado.").arg(this->socketDescriptor));

    qDebug() << msg;
    Logger::Instance()->log(msg);

    emit endAlgoritm(1);
}


void KGuardiantClient::readyRead()
{

    QByteArray data = socket->readAll();

    qDebug() << data;

    if(data == "1"){
        emit endAlgoritm(1);
    }else{
        this->camVisor->start();
    }

    socket->write(data);
}

void KGuardiantClient::resultAlgDetector(int number)
{

    socket->write(QString(number).toLatin1());

}

void KGuardiantClient::resultAlgVisor(QByteArray img)
{
    qDebug() << "Sending image.";
    socket->write(img);
}


void KGuardiantClient::errorAlg(int code)
{
    qDebug() << "Error !";
}
