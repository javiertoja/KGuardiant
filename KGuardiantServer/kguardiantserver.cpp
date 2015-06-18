#include "kguardiantserver.h"

KGuardiantServer::KGuardiantServer(QObject *parent) :
    QObject(parent)
{
    //Instancia da aplicación que se está a executar.
    app = QCoreApplication::instance();

    //Preparamos as propiedades do sistema.
    app->setApplicationName("KGServer");
    app->setApplicationVersion("1.0");

    //Creación de obxectos globais.
    settings = Configuracion::Instance();
    settings->setParent(this);

    log = Logger::Instance();
    log->setParent(this);





}


/**
 * @brief KGuardiantServer::run
 */
void KGuardiantServer::run()
{
    //Bloque de código principal.
    qDebug() << "KGuardiantServer.Run is executing";
    log->log("KGuardiantServer.Run is executing");



    cam = new DeviceMgr(this);
    clock = new QTimer(this);
    clock->setInterval(300);
    clock->setSingleShot(false);

    connect(cam,
            SIGNAL(finished()),
            cam,
            SLOT(deleteLater()));

    connect(clock,
            SIGNAL(timeout()),
            cam,
            SLOT(requestImage()));

    detector = new MovementDetector(this);

    connect(cam,
            SIGNAL(newImage(cv::Mat&)),
            detector,
            SLOT(processImg(cv::Mat&)),
                 Qt::DirectConnection);
    connect(cam,
            SIGNAL(newImage(cv::Mat&,cv::Mat&)),
            detector,
            SLOT(processImg(cv::Mat&,cv::Mat&))
            ,Qt::DirectConnection);

    connect(detector,
            SIGNAL(processedImg(QByteArray)),
            &server,
            SLOT(sendImg(QByteArray)));

    connect(detector,
            SIGNAL(finished()),
            detector,
            SLOT(deleteLater()));


    console = new Console(this);

    connect(console,SIGNAL(finished()),console,SLOT(deleteLater()));
    connect(console,SIGNAL(startServer()),&server,SLOT(startServer()));
    connect(console,SIGNAL(stopServer()),&server,SLOT(stopServer()));
    connect(console,SIGNAL(checkClients()),&server,SLOT(requestClients()));
    connect(&server,
            SIGNAL(clientList(QHash<qintptr,TCPConnection*>*)),
            console,
            SLOT(printClients(QHash<qintptr,TCPConnection*>*)));
    connect(console,SIGNAL(finish()),this,SLOT(quit()));




    cam->start();
    detector->start();
    clock->start();
    server.startServer();
    //console->start();
    //QTimer::singleShot(10,console,SLOT(startC()));
    //Débese chamar a quit() para finalizar o bucle de eventos do sistema.
    //quit();
}

/**
 * @brief KGuardiantServer::quit
 */
void KGuardiantServer::quit()
{
    //Código para limpeza de variables.
    //qDebug() << "Saindo da app";
    //Emítese o sinal de finished cara o CoreApplication
    emit finished();
}
/**
 * @brief KGuardiantServer::aboutToQuitApp
 */
void KGuardiantServer::aboutToQuitApp()
{
    //qDebug() << "Parando fios.";
    //Paramos os fíos que podan quedar en execución.
    //clock->stop();

    //detector->deleteLater();
    server.close();
    //server->close();
    //Espérase un segundo para agardar a finalización de todos os fíos
    QThread::sleep(1);
}
