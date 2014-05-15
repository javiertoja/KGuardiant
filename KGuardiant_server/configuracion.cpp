#include "configuracion.h"
#include <QDebug>

//Reseteamos la instancia del singleton
Configuracion* Configuracion::pinstance = 0;

//Método para recuperar a instancia do singleton
Configuracion* Configuracion::Instance()
{
    if (pinstance == 0){

        static QMutex mutex;
        mutex.lock();
        if (pinstance == 0){
            pinstance = new Configuracion();
        }
        mutex.unlock();
    }
    return pinstance;
}

//Constructor del singleton
Configuracion::Configuracion(QObject *parent) :
    QObject(parent)
{
    dir = new QDir();
    config = new QSettings(dir->absolutePath()+"/server.ini",
                           QSettings::IniFormat,
                           this);
}

static void Configuracion::drop(){

    static QMutex mutex;
    mutex.lock();
    delete pinstance;
    pinstance = 0;
    mutex.unlock();
}


QString Configuracion::getValueConfig(QString tag, QString lbl)
{
    return config->value(tag+"/"+lbl).toString();
}

void Configuracion::setValueConfig(QString tag, QString lbl, QString value)
{
    config->setValue(tag+"/"+lbl,value);
    config->sync();
}
