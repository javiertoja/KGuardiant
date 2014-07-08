#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QMutex>
#include "constants.h"

class Configuracion : public QObject
{
    Q_OBJECT
public:
    static Configuracion* Instance();
    QString getValueConfig(QString tag,
                              QString lbl);
    void setValueConfig(QString tag,
                        QString lbl,
                        QString value);
    //static void drop();
signals:
    
public slots:
    
protected:
    explicit Configuracion(QObject *parent = 0);

private:
    static Configuracion* pinstance;
    QDir* dir;
    QSettings* config;
};

#endif // CONFIGURACION_H
