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
#include "constants.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger* Instance();

    void log(QString logData);
    void logImage(QImage* logImage);
    static void drop();
signals:
    
public slots:

private:
    QDir* logDir;
    QFile* logFile;

    static Logger* pinstance;
protected:
    explicit Logger(QObject *parent = 0);
};

#endif // LOGGER_H
