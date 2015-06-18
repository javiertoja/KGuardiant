#include "configuracion.h"

//Reseteamos a instancia do singleton
Configuracion* Configuracion::pinstance = 0;

/**
 * @brief Configuracion::Instance
 * @return Pointer to Configuration instance.
 */
Configuracion* Configuracion::Instance()
{
    if (pinstance == 0)
    {
        static QMutex mutex;
        mutex.lock();
        if (pinstance ==0)
        {
            pinstance = new Configuracion();
        }
        mutex.unlock();
    }
    return pinstance;
}

/**
 * @brief Configuracion::Configuracion
 * @param parent
 */
Configuracion::Configuracion(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Creando obxecto configuración";
    dir = new QDir();
    qDebug() << "\t Dir :"
             << dir->absolutePath() <<"";
    settings = new QSettings(dir->absolutePath()+"/server.ini",
                             QSettings::IniFormat,
                             this);
}

/**
 * @brief Configuracion::getValue
 * @param tag
 * @param lbl
 * @return
 */
QVariant Configuracion::getValue(const QString tag, const QString lbl)
{
    return settings->value(tag+"/"+lbl);
}

/**
 * @brief Configuracion::aboutToQuitApp
 */
void Configuracion::aboutToQuitApp()
{
    qDebug() << "Liberando Configuración.";

}
