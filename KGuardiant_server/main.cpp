#include <QCoreApplication>
#include <kguardiantserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    //Creamos o servidor
    KGuardiantServer server;
    server.startServer();

    return a.exec();
}
