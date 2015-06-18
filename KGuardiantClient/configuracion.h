#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QMutex>
#include <QDebug>

class Configuracion : public QObject
{
    Q_OBJECT
public:
    static Configuracion* Instance();
    QVariant getValue(const QString tag,
                     const QString lbl);
protected:
    explicit Configuracion(QObject *parent = 0);

private:

    static Configuracion* pinstance;
    QDir *dir;
    QSettings *settings;
public slots:
    void aboutToQuitApp();
};

#endif // CONFIGURACION_H
