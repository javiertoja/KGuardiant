#ifndef KGUARDIANTSERVER_H
#define KGUARDIANTSERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include <configuracion.h>
#include <logger.h>
#include <tcpserver.h>
#include <devicemgr.h>
#include <movementdetector.h>
#include <console.h>

class KGuardiantServer : public QObject
{
    Q_OBJECT

private:
    QCoreApplication *app;
    Configuracion *settings;
    Logger *log;
    TCPServer server;
    DeviceMgr *cam;
    QTimer *clock;
    MovementDetector *detector;
    Console *console;
public:
    explicit KGuardiantServer(QObject *parent = 0);
    

signals:
    
    void finished();
public slots:
    
    void quit();
    void run();
    void aboutToQuitApp();
};

#endif // KGUARDIANTSERVER_H
