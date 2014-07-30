#include "kguardiantclient.h"

KGuardiantClient::KGuardiantClient(qintptr descriptor, cv::VideoCapture *capture, QObject *parent) :
    QObject(parent)
{
    this->stop = 0;
    this->socketDescriptor = descriptor;
    this->capture = capture;

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

    if(atoi(data.data()) == START_CAM){
        this->camVisor = new CamVisor(false,capture);
        connect(this->camVisor,SIGNAL(resultado(QByteArray)),this,SLOT(resultAlgVisor(QByteArray)),Qt::QueuedConnection);
        connect(this,SIGNAL(endAlgoritm(bool)),this->camVisor,SLOT(stopTask(bool)),Qt::QueuedConnection);
        connect(this->camVisor,SIGNAL(error(int)),this,SLOT(errorAlg(int)));
        this->camVisor->start();
    }

    if(atoi(data.data()) == STOP_CAM){
        emit endAlgoritm(STOP_CAM);
    }

    if(atoi(data.data()) == START_MOV){
        //this->camVisor->start();
    }

    if(atoi(data.data()) == STOP_MOV){
        //emit endAlgoritm(STOP_MOV);
    }

}

void KGuardiantClient::resultAlgDetector(int number)
{

    socket->write(QString(number).toLatin1());

}

void KGuardiantClient::resultAlgVisor(QByteArray img)
{

    socket->write(img);
}


void KGuardiantClient::errorAlg(int code)
{
    qDebug() << "Error !";
}
