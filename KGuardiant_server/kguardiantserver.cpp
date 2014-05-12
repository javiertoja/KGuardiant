#include "kguardiantserver.h"
#include "kguardiantthread.h"

KGuardiantServer::KGuardiantServer(QObject *parent) :
    QTcpServer(parent)
{
}

void KGuardiantServer::startServer()
{
    Configuracion* singleton = Configuracion::Instance();
    int port = singleton->getValueConfig("configuracion","porto").toInt();

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Erro o arrancar o servidor";
    }
    else
    {
        qDebug() << "Escoitando o porto :"<< port << " ...";
    }
}

//Esta funcion é chamada cando se produce unha nova conexión.
void KGuardiantServer::incomingConnection(qintptr socketDescriptor)
{
    //Temos unha nova conexión
    qDebug() << "Conectando cliente ID [" << socketDescriptor << "]";

    //Por cada nova conexión creamos un novo thread
    KGuardiantThread *thread = new KGuardiantThread(socketDescriptor,this);

    //Conectamos as sinales con novo thread, unha vez que o thread non se
    //necesite limparanse.
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
