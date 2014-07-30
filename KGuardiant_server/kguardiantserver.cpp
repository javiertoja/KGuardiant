#include "kguardiantserver.h"
//#include "kguardiantthread.h"
#include "kguardiantclient.h"

KGuardiantServer::KGuardiantServer(QObject *parent) :
    QTcpServer(parent)
{
}

KGuardiantServer::~KGuardiantServer()
{
    capture.release();
}

void KGuardiantServer::startServer()
{
    Configuracion* singleton = Configuracion::Instance();
    QString port = singleton->getValueConfig("configuracion","porto");

    if(!this->listen(QHostAddress::Any,port.toInt()))
    {
        qDebug() << "Erro o arrancar o servidor";
        Logger::Instance()->log(QString("Erro o arrancar o servidor.\n"));
    }
    else
    {
         Logger::Instance()->log((QString("Escoitando o porto [%1]").arg(port)));
    }

    capture.open(0);

    if (capture.isOpened())
    {
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 480);
        capture.set(CV_CAP_PROP_FPS, 30);
        qDebug() << "Cámara correcta!";
    }else
    {
        qDebug() << "Error o abrir a camara";
        return;
    }
}

//Esta funcion é chamada cando se produce unha nova conexión.
void KGuardiantServer::incomingConnection(qintptr socketDescriptor)
{
    //Temos unha nova conexión
    qDebug() << "Conectando cliente ID [" << socketDescriptor << "]";
    Logger::Instance()->log((QString("Conectando cliente ID [%1]").arg(socketDescriptor)));
    //Por cada nova conexión creamos un novo thread
    //KGuardiantThread *thread = new KGuardiantThread(socketDescriptor,this);

    //Conectamos as sinales con novo thread, unha vez que o thread non se
    //necesite limparanse.
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    //thread->start();

    KGuardiantClient *client = new KGuardiantClient(socketDescriptor,&capture,this);
}
