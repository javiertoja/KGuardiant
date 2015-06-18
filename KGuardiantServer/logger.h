#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDir>
#include <QString>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QMutex>
#include "configuracion.h"

class Logger : public QObject
{
    Q_OBJECT
public:

    static Logger* Instance();
    void log(const QString logData);
    void logImage(QImage* logImage);

protected:
    explicit Logger(QObject *parent = 0);

private:
    QDir *logDir;
    QFile *logFile;
    Configuracion* settings;

    static Logger* pinstance;

public slots:
    
};

#endif // LOGGER_H
