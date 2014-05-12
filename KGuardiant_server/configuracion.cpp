#include "configuracion.h"
#include <QDebug>

//Reseteamos la instancia del singleton
Configuracion* Configuracion::pinstance = 0;

//Método para recuperar a instancia do singleton
Configuracion* Configuracion::Instance()
{
    if (pinstance == 0){
        qDebug() << "Creando singleton";
        pinstance = new Configuracion();
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

QString Configuracion::getValueConfig(QString tag, QString lbl)
{
    return config->value(tag+"/"+lbl).toString();
}

void Configuracion::setValueConfig(QString tag, QString lbl, QString value)
{
    config->setValue(tag+"/"+lbl,value);
    config->sync();
}
